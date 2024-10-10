//#define FG_USE_MPI
#include "../include/FgTree.h"

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
    int n_proc_int;
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc_int);
    auto n_proc = fg_uint(n_proc_int);
#endif

    fg_uint base = fg_uint(std::stoi(argv[1]));
    fg_uint max_level = std::stoi(argv[2]);
    fg_uint n_elem_l1 = std::stoi(argv[3]);

#ifdef FG_USE_MPI
    bool condition = (n_proc == tree_nodes_num(base, max_level - 1) * n_elem_l1 + 1);
    assert(condition && "Number of processes is not the expected one from the levels and the base.");
#else
    fg_uint n_proc = fg_uint (std::pow(base,max_level - 1) - 1) / (base - 1) * n_elem_l1 + 1;
    omp_set_num_threads(int(n_proc));
#pragma omp parallel for
    for (fg_uint rank = 0; rank < n_proc; rank ++) {
#endif
    std::vector<fg_uint> h_index = rank_to_h_index(rank, base, max_level);
    fg_print("My h-index is " + h_index_to_str(h_index), rank);
    fg_print("Check rank " + std::to_string(h_index_to_rank(h_index, base, max_level)), rank);
    if (h_index.size() > 1)
    {
        std::vector<fg_uint> h_index_parent(h_index.begin(), h_index.end() - 1);
        fg_uint parent_rank = h_index_to_rank(h_index_parent, base, max_level);
        fg_print("Parent rank " + std::to_string(parent_rank), rank);
        fg_print("Parent h-index is " + h_index_to_str(h_index_parent), rank);
    }
#ifndef FG_USE_MPI
    }
#else
    MPI_Finalize();
#endif

    return 0;
}
