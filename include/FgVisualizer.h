//
// Created by dconsoli on 10-10-24.
//

#ifndef FGGRID_FGVISUALIZER_H
#define FGGRID_FGVISUALIZER_H

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

class FgVisualizer {

};

void generate_polygon(vtkPolyData *polydata,
                      const std::vector<std::vector<double>>& pointsMatrix,
                      const std::vector<std::vector<int>>& trianglesMatrix);

void generate_icosahedron(vtkPolyData* polydata);

void visualize_polydata(vtkPolyData* polydata, float axis_lengh);




#endif //FGGRID_FGVISUALIZER_H
