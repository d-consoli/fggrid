#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkCellData.h>
#include <vtkCellArray.h>
#include <vtkTriangle.h>
#include <vtkPlatonicSolidSource.h>
#include <vtkTransform.h>
#include <vtkLookupTable.h>
#include <vtkOutlineFilter.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkFloatArray.h>
#include <vector>

void generate_polygon(vtkPolyData *polydata,
                      const std::vector<std::vector<double>>& pointsMatrix,
                      const std::vector<std::vector<int>>& trianglesMatrix)
{
    vtkNew<vtkPoints> points;
    // Insert points into vtkPoints
    for (const auto& point : pointsMatrix) {
        if (point.size() == 3) {
            points->InsertNextPoint(point[0], point[1], point[2]);
        }
    }
    polydata->SetPoints(points);

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
        cellScalars->InsertNextValue(static_cast<float>(i));  // Assign a scalar value to each cell
    }
    polydata->SetPolys(triangles);
    polydata->GetCellData()->SetScalars(cellScalars);  // Assign scalar data to the cells
}

void generate_icosahedron(vtkPolyData* polydata)
{
    vtkNew<vtkPlatonicSolidSource> icosahedronSource;
    icosahedronSource->SetSolidTypeToIcosahedron();
    icosahedronSource->Update();
    auto icosahedron = icosahedronSource->GetOutput();
    polydata->ShallowCopy(icosahedron);
}

void visualize_polydata(vtkPolyData* polydata, float axis_lengh)
{
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(polydata);
    mapper->SetScalarRange(0, polydata->GetNumberOfCells() - 1);
    mapper->SetColorModeToMapScalars();
    mapper->ScalarVisibilityOn();

    // Create a lookup table to map cell data to colors
    vtkNew<vtkLookupTable> lut;
    int n = polydata->GetNumberOfCells();
    std::cout << "Number of cells in the polydata: " << n << std::endl;
    lut->SetNumberOfTableValues(n);
    lut->SetTableRange(0.0, n-1);
    for(int i = 0; i < n; i++)
        lut->SetTableValue(i, 0.1, 0.8, 0.1);
    lut->Build();
    mapper->SetLookupTable(lut);
    mapper->SetScalarRange(0.0, n);
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
    if (axis_lengh > 0.)
    {
        renderer->AddActor(axes);
        axes->SetTotalLength(axis_lengh, axis_lengh, axis_lengh);  // Adjust the size of the axes as needed
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

int main(int argc, char** argv)
{
    vtkNew<vtkPolyData> polydata;
//    generate_icosahedron(polydata);

    std::vector<std::vector<double>> pointsMatrix = {
            {1.0, 0.0, 0.0}, // Point 0
            {0.0, 1.0, 0.0}, // Point 1
            {0.0, 0.0, 1.0}, // Point 2
            {0.0, 0.0, 0.0} // Point 3
    };

    // Define triangle indices for the tetrahedron
    std::vector<std::vector<int>> trianglesMatrix = {
            {0, 1, 3}, // Triangle 1
            {0, 2, 3}, // Triangle 2
            {1, 2, 3}, // Triangle 3
            {0, 1, 2}  // Triangle 4
    };

    generate_polygon(polydata, pointsMatrix, trianglesMatrix);


    visualize_polydata(polydata, 2.0);

    return 0;
}

