//
// Created by dconsoli on 10-10-24.
//

#ifndef FGGRID_FGTREE_H
#define FGGRID_FGTREE_H

#include "misc.h"

class FgTree {

protected :

    fg_uint n_levels;
    fg_uint base;
    fg_uint n_elem_l1;
    fg_uint n_nodes;

    std::vector<fg_uint> factorization(fg_uint idx, fg_uint level);

public :

    FgTree(fg_uint n_levels, fg_uint base, fg_uint n_elem_l1);
    fg_uint subtree_nodes_num(fg_uint level);
    std::string h_index_to_str(std::vector<fg_uint> h_index);
    std::vector<fg_uint> rank_to_h_index(fg_uint rank);
    fg_uint h_index_to_rank(std::vector<fg_uint> h_index);
    fg_uint get_n_nodes();

};

#endif //FGGRID_FGTREE_H
