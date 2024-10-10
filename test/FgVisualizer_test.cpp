//
// Created by dconsoli on 10-10-24.
//

#include <vtkPolyData.h>
#include "../include/FgVisualizer.h"

int main(int argc, char** argv)
{
    vtkNew<vtkPolyData> polydata;
    generate_icosahedron(polydata);
//
//    std::vector<std::vector<double>> pointsMatrix = {
//            {1.0, 0.0, 0.0}, // Point 0
//            {0.0, 1.0, 0.0}, // Point 1
//            {0.0, 0.0, 1.0}, // Point 2
//            {0.0, 0.0, 0.0} // Point 3
//    };
//
//    // Define triangle indices for the tetrahedron
//    std::vector<std::vector<int>> trianglesMatrix = {
//            {0, 1, 3}, // Triangle 1
//            {0, 2, 3}, // Triangle 2
//            {1, 2, 3}, // Triangle 3
//            {0, 1, 2}  // Triangle 4
//    };

//    generate_polygon(polydata, pointsMatrix, trianglesMatrix);


    visualize_polydata(polydata, 2.0);

    return 0;
}

