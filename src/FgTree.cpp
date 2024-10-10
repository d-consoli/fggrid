//
// Created by dconsoli on 10-10-24.
//

#include "../include/FgTree.h"


void fg_print(const std::string& str, std::optional<fg_uint> rank)
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
            rank += fg_uint(std::pow(base, (h_index.size()-i-1))) * h_index[i];
        }
    }
    return rank;
}
