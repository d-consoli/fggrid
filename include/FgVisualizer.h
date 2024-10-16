//
// Created by dconsoli on 10-10-24.
//

#ifndef FGGRID_FGVISUALIZER_H
#define FGGRID_FGVISUALIZER_H

#include "misc.h"
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
#include <vtkVertexGlyphFilter.h>
#include <vtkTextActor3D.h>
#include <vtkTextProperty.h>

class FgVisualizer {
protected:
    vtkNew<vtkPolyData> polydata;

public:

    FgVisualizer();

    void generate_polygon(const FgMatReal& pointsMatrix,
                          const FgMatUint& trianglesMatrix);

    void generate_icosahedron();

    void interact(std::optional<fg_real> axis_length = std::nullopt);

};



#endif //FGGRID_FGVISUALIZER_H
