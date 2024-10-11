//
// Created by dconsoli on 11-10-24.
//

#include "FgGeometry.h"

int main(int argc, char** argv)
{
    fg_real radius = 1.;
    fg_uint n_elem_l1 = 20;
    FgMatReal mesh_vert;
    FgMatUint mesh_cells;
    FgGeometry fgGeometry(radius, n_elem_l1);
    fgGeometry.get_l1_mesh(mesh_vert, mesh_cells);
    FgMatReal verts_cell_0;
    for (fg_iter i = 0; i < mesh_cells[0].size(); i++)
    {
        verts_cell_0.push_back(mesh_vert[mesh_cells[0][i]]);
        std::cout << "Vertex " << i << ": " << vec_to_str(verts_cell_0[i]) << std::endl;
    }
    FgVecReal centroid = fgGeometry.compute_centroid(verts_cell_0);

    // Expect all distances 0.607062
    for (fg_iter i = 0; i < mesh_cells[0].size(); i++)
    {
        std::cout << "Distance centroid to v " << i << ": " << fgGeometry.points_distance(centroid, verts_cell_0[i]) << std::endl;
    }

    return 0;
}

