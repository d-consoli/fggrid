//
// Created by dconsoli on 10-10-24.
//

//#define FG_USE_MPI
//#define FG_VISUALIZE
#include "FgTree.h"
#include "FgVisualizer.h"
#include "FgGeometry.h"
#include "FgCell.h"


int main(int argc, char** argv) {
    fg_real radius = 3.5;
    fg_uint n_levels = std::stoi(argv[2]);
    fg_uint base = fg_uint(std::stoi(argv[1]));
    fg_uint n_elem_l1 = std::stoi(argv[3]);
    FgTree fgTree(n_levels, base, n_elem_l1);


//    omp_set_num_threads(int(mesh_cells.size()));

    FgGeometry fgGeometry(radius, n_elem_l1);
    FgMatUint l1_neighbors = fgGeometry.get_l1_neighbors();



#ifdef FG_VISUALIZE

    FgVisualizer fgVisualizer;
    fgVisualizer.generate_polygon(mesh_vert, mesh_cells);
    fgVisualizer.interact();

#endif

    return 0;
}
