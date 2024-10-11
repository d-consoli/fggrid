//
// Created by dconsoli on 10-10-24.
//

//#define FG_USE_MPI
#define FG_VISUALIZE
#include "FgTree.h"
#include "FgVisualizer.h"
#include "FgGeometry.h"

#include <omp.h>

#ifdef FG_USE_MPI
#include <mpi.h>
#endif

int main(int argc, char** argv) {
#ifdef FG_USE_MPI
    MPI_Init(&argc, &argv);
    int rank_int;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_int);
    auto rank = fg_uint(rank_int);
#endif

    fg_real radius = 3.5;
    fg_uint n_levels = std::stoi(argv[2]);
    fg_uint base = fg_uint(std::stoi(argv[1]));
    fg_uint n_elem_l1 = std::stoi(argv[3]);
    FgTree fgTree(n_levels, base, n_elem_l1);
    FgMatReal mesh_vert;
    FgMatUint mesh_cells;

#ifndef FG_USE_MPI
    omp_set_num_threads(int(fgTree.get_n_nodes()));
#pragma omp parallel for
    for (fg_uint rank = 0; rank < fgTree.get_n_nodes(); rank ++) {
#endif
        std::vector<fg_uint> h_index = fgTree.rank_to_h_index(rank);
        if (h_index.size() == 1)
        {
            FgGeometry fgGeometry(radius, n_elem_l1);
            fgGeometry.get_l1_mesh(mesh_vert, mesh_cells);
        } else
        {
            std::vector<fg_uint> h_index_parent(h_index.begin(), h_index.end() - 1);
            fg_uint parent_rank = fgTree.h_index_to_rank(h_index_parent);
        }
#ifndef FG_USE_MPI
    }
#endif
#ifdef FG_VISUALIZE

    vtkNew<vtkPolyData> polydata;
    generate_polygon(polydata, mesh_vert, mesh_cells);
    visualize_polydata(polydata, 3.0);

#else
    MPI_Finalize();
#endif

    return 0;
}
