//
// Created by dconsoli on 10-10-24.
//

#include "FgTree.h"

FgTree::FgTree(fg_uint n_levels, fg_uint base, fg_uint n_elem_l1)
        : n_levels(n_levels)
        , base(base)
        , n_elem_l1(n_elem_l1)
{
#ifdef FG_USE_MPI
    int n_nodes_int;
    MPI_Comm_size(MPI_COMM_WORLD, &n_nodes_int);
    this->n_nodes = fg_uint(n_nodes_int);
    bool condition = (this->n_nodes == subtree_nodes_num(this->n_levels - 1) * this->n_elem_l1 + 1);
    assert(condition && "Number of processes is not the expected one from the levels and the base.");
#else
    this->n_nodes = subtree_nodes_num(this->n_levels - 1) * this->n_elem_l1 + 1;
#endif
}

fg_uint FgTree::subtree_nodes_num(fg_uint n_sublevels)
{
    return fg_uint(std::pow(this->base, n_sublevels) - 1) / (this->base - 1);
}

std::vector<fg_uint> FgTree::factorization(fg_uint idx, fg_uint level)
{
    std::vector<fg_uint> h_index(level, 0);
    for(fg_uint i = 0; i < level; ++i)
    {
        h_index[i] = idx % this->base;
        idx /= this->base;
    }
    std::reverse(h_index.begin(), h_index.end());
    return h_index;
}

std::vector<fg_uint> FgTree::rank_to_h_index(fg_uint rank)
{
    std::vector<fg_uint> h_index = {0};
    if (rank > 0)
    {
        fg_uint n_tree_elem = this->subtree_nodes_num(this->n_levels - 1);
        fg_uint l1_index = floor(fg_double(rank - 1) / fg_double(n_tree_elem));
        h_index.push_back(l1_index);
        if ((rank - 1) % n_tree_elem != 0) {
            fg_uint index_clean = rank - 1 - n_tree_elem * l1_index;
            fg_uint my_level = floor(std::log(index_clean * (this->base - 1) + 1) / std::log(this->base));
            index_clean -= this->subtree_nodes_num(my_level);
            std::vector<fg_uint> h_index_clean = factorization(index_clean, my_level);
            h_index.insert(h_index.end(), h_index_clean.begin(), h_index_clean.end());
        }
    }
    return h_index;
}

fg_uint FgTree::h_index_to_rank(std::vector<fg_uint> h_index)
{
    fg_uint rank = 0;
    if (h_index.size() > 1)
    {
        fg_uint n_tree_elem = this->subtree_nodes_num(this->n_levels - 1);
        rank += 1 + n_tree_elem * h_index[1];
    }
    if (h_index.size() > 2)
    {
        rank += this->subtree_nodes_num(h_index.size() - 2);
        for (fg_uint i = 2; i < h_index.size(); ++i)
        {
            rank += fg_uint(std::pow(this->base, (h_index.size()-i-1))) * h_index[i];
        }
    }
    return rank;
}

fg_uint FgTree::get_n_nodes()
{
    return this->n_nodes;
}
