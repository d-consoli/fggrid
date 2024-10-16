//
// Created by dconsoli on 10-10-24.
//

#include "FgVisualizer.h"

FgVisualizer::FgVisualizer() {}

void FgVisualizer::generate_polygon(const FgMatReal& pointsMatrix,
                                    const FgMatUint& trianglesMatrix)
{
    vtkNew<vtkPoints> points;
    // Insert points into vtkPoints
    for (const auto& point : pointsMatrix) {
        if (point.size() == 3) {
            points->InsertNextPoint(point[0], point[1], point[2]);
        }
    }
    this->polydata->SetPoints(points);

    vtkNew<vtkCellArray> triangles;
    vtkNew<vtkFloatArray> cellScalars;  // Create a scalar array for cell data
    cellScalars->SetNumberOfComponents(1);
    cellScalars->SetName("CellScalars");

    // Insert triangles into vtkCellArray
    for (size_t i = 0; i < trianglesMatrix.size(); ++i) {
        vtkNew<vtkTriangle> vtkTriangle;
        for (int j = 0; j < 3; ++j) {
            vtkTriangle->GetPointIds()->SetId(j, trianglesMatrix[i][j]);
        }
        triangles->InsertNextCell(vtkTriangle);
        cellScalars->InsertNextValue(static_cast<fg_float>(i));  // Assign a scalar value to each cell
    }
    this->polydata->SetPolys(triangles);
    this->polydata->GetCellData()->SetScalars(cellScalars);  // Assign scalar data to the cells
}

void FgVisualizer::generate_icosahedron()
{
    vtkNew<vtkPlatonicSolidSource> icosahedronSource;
    icosahedronSource->SetSolidTypeToIcosahedron();
    icosahedronSource->Update();
    auto icosahedron = icosahedronSource->GetOutput();
    this->polydata->ShallowCopy(icosahedron);
}

void FgVisualizer::interact(std::optional<fg_real> axis_length)
{
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(this->polydata);
    fg_iter n = this->polydata->GetNumberOfCells();
    fg_double scale_max = fg_double (n) - 1.;
    mapper->SetScalarRange(0, scale_max);
    mapper->SetColorModeToMapScalars();
    mapper->ScalarVisibilityOn();

    // Create a lookup table to map cell data to colors
    vtkNew<vtkLookupTable> lut;
    lut->SetNumberOfTableValues(n);
    lut->SetTableRange(0.0, scale_max);
    for(int i = 0; i < n; i++)
        lut->SetTableValue(i, 0.1, 0.8, 0.1);
    lut->Build();
    mapper->SetLookupTable(lut);
    mapper->SetScalarRange(0.0, scale_max);
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    vtkNew<vtkNamedColors> colors;
    renderer->SetBackground(colors->GetColor3d("LightGrey").GetData());
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("FGGrid Visualizer");
    renderWindow->SetSize(900, 900);
    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(renderWindow);
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor->SetInteractorStyle(style);

    // Add axes to show orientation
    vtkNew<vtkAxesActor> axes;
    if (axis_length.has_value())
    {
        renderer->AddActor(axes);
        axes->SetTotalLength(axis_length.value(), axis_length.value(), axis_length.value());  // Adjust the size of the axes as needed
    }
    vtkNew<vtkOrientationMarkerWidget> orientationWidget;
    orientationWidget->SetOrientationMarker(axes);
    orientationWidget->SetInteractor(interactor);
    orientationWidget->InteractiveOn();
    orientationWidget->EnabledOn();
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.0);
    interactor->Initialize();
    interactor->Start();
}
