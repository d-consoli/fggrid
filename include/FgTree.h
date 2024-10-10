//
// Created by dconsoli on 10-10-24.
//

#ifndef FGGRID_FGTREE_H
#define FGGRID_FGTREE_H

#include "misc.h"


class FgTree {

};



void fg_print(const std::string& str, std::optional<fg_uint> rank = std::nullopt);

fg_uint tree_nodes_num(fg_uint base, fg_uint level);

std::string h_index_to_str(std::vector<fg_uint> h_index);

std::vector<fg_uint> factorization(fg_uint idx, fg_uint base, fg_uint level);

std::vector<fg_uint> rank_to_h_index(fg_uint rank, fg_uint base, fg_uint max_level) ;

fg_uint h_index_to_rank(std::vector<fg_uint> h_index, fg_uint base, fg_uint max_level);


#endif //FGGRID_FGTREE_H
