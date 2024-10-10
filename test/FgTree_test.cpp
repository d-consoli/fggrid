#include "../include/FgTree.h"
#include <omp.h>

int main(int argc, char** argv) {
#ifdef FG_USE_MPI
    MPI_Init(&argc, &argv);
    int rank_int;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_int);
    auto rank = fg_uint(rank_int);
#endif

    fg_uint n_levels = std::stoi(argv[2]);
    fg_uint base = fg_uint(std::stoi(argv[1]));
    fg_uint n_elem_l1 = std::stoi(argv[3]);
    FgTree fgTree(n_levels, base, n_elem_l1);

#ifndef FG_USE_MPI
    omp_set_num_threads(int(fgTree.get_n_nodes()));
#pragma omp parallel for
    for (fg_uint rank = 0; rank < fgTree.get_n_nodes(); rank ++) {
#endif
    std::vector<fg_uint> h_index = fgTree.rank_to_h_index(rank);
    fg_print("My h-index is " + fgTree.h_index_to_str(h_index), rank);
    fg_print("Check rank " + std::to_string(fgTree.h_index_to_rank(h_index)), rank);
    if (h_index.size() > 1)
    {
        std::vector<fg_uint> h_index_parent(h_index.begin(), h_index.end() - 1);
        fg_uint parent_rank = fgTree.h_index_to_rank(h_index_parent);
        fg_print("Parent rank " + std::to_string(parent_rank), rank);
        fg_print("Parent h-index is " + fgTree.h_index_to_str(h_index_parent), rank);
    }

#ifndef FG_USE_MPI
    }
#else
    MPI_Finalize();
#endif

    return 0;
}
