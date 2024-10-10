#define FG_USE_MPI
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cstdarg>
#include <omp.h>
#include <optional>

#ifdef FG_USE_MPI
#include <mpi.h>
#endif

using fg_uint = long unsigned int;
using fg_int = long unsigned int;
using fg_float = float;
using fg_double = double;
using fg_real = float;
using fg_byte = unsigned char;

void fg_print(const std::string& str, std::optional<fg_uint> rank = std::nullopt)
{
    std::stringstream ss;
    if (rank.has_value())
        ss << "Rank " << rank.value() << " | ";
    ss << str << std::endl;
    std::cout << ss.str();
}

fg_uint tree_nodes_num(fg_uint base, fg_uint level)
{
    return fg_uint(std::pow(base, level) - 1) / (base - 1);
}

std::string h_index_to_str(std::vector<fg_uint> h_index){
     std::stringstream ss;
     for (size_t i=0; i<h_index.size(); ++i) {
         ss << h_index[i];
         if (i != h_index.size() - 1) {
             ss << ".";
         }
     }
    return ss.str();
}

std::vector<fg_uint> factorization(fg_uint idx, fg_uint base, fg_uint level){
    std::vector<fg_uint> h_index(level, 0);
    for(fg_uint i = 0; i < level; ++i)
    {
        h_index[i] = idx % base;
        idx /= base;
    }
    std::reverse(h_index.begin(), h_index.end());
    return h_index;
}

std::vector<fg_uint> rank_to_h_index(fg_uint rank, fg_uint base, fg_uint max_level) {
    std::vector<fg_uint> h_index = {0};
    if (rank > 0)
    {
        fg_uint n_tree_elem = tree_nodes_num(base, max_level - 1);
        fg_uint l1_index = floor(fg_double(rank - 1) / fg_double(n_tree_elem));
        h_index.push_back(l1_index);
        if ((rank - 1) % n_tree_elem != 0) {
            fg_uint index_clean = rank - 1 - n_tree_elem * l1_index;
            fg_uint my_level = floor(std::log(index_clean * (base - 1) + 1) / std::log(base));
            index_clean -= tree_nodes_num(base, my_level);
            std::vector<fg_uint> h_index_clean = factorization(index_clean, base, my_level);
            h_index.insert(h_index.end(), h_index_clean.begin(), h_index_clean.end());
        }
    }
    return h_index;
}

fg_uint h_index_to_rank(std::vector<fg_uint> h_index, fg_uint base, fg_uint max_level) {
    fg_uint rank = 0;
    if (h_index.size() > 1)
    {
        fg_uint n_tree_elem = tree_nodes_num(base, max_level - 1);
        rank += 1 + n_tree_elem * h_index[1];
    }
    if (h_index.size() > 2)
    {
        rank += tree_nodes_num(base, h_index.size() - 2);
        for (fg_uint i = 2; i < h_index.size(); ++i)
        {
            rank += fg_uint(std::pow(base, (max_level-i-1))) * h_index[i];
        }
    }
    return rank;
}

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
            fg_print("Parent h-index is " + h_index_to_str(h_index_parent), rank);
        }
#ifndef FG_USE_MPI
    }
#ifdef FG_VISUALIZE

#endif
#else
    MPI_Finalize();
#endif

    return 0;
}
