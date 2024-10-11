//
// Created by dconsoli on 10-10-24.
//

//#define FG_USE_MPI
#define FG_VISUALIZE
#include "FgTree.h"
#include "FgVisualizer.h"
#include "FgGeometry.h"
#include "FgCell.h"
#include <omp.h>


int main(int argc, char** argv) {
    fg_real radius = 3.5;
    fg_uint n_levels = std::stoi(argv[2]);
    fg_uint base = fg_uint(std::stoi(argv[1]));
    fg_uint n_elem_l1 = std::stoi(argv[3]);
    FgTree fgTree(n_levels, base, n_elem_l1);
    FgMatReal mesh_vert;
    FgMatUint mesh_cells;
    FgGeometry fgGeometry(radius, n_elem_l1);
    fgGeometry.get_l1_mesh(mesh_vert, mesh_cells);

    omp_set_num_threads(int(fgTree.get_n_nodes()));
#pragma omp parallel for
    for (fg_uint rank = 1; rank < fgTree.get_n_nodes(); rank ++) {

    }

#ifdef FG_VISUALIZE

    FgVisualizer fgVisualizer;
    fgVisualizer.generate_polygon(mesh_vert, mesh_cells);
    fgVisualizer.interact();

#endif

    return 0;
}
