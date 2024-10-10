//
// Created by dconsoli on 10-10-24.
//

#ifndef FGGRID_FGTREE_H
#define FGGRID_FGTREE_H

class FgTree {

};

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cstdarg>
#include <optional>

using fg_uint = long unsigned int;
using fg_int = long unsigned int;
using fg_float = float;
using fg_double = double;
using fg_real = float;
using fg_byte = unsigned char;

void fg_print(const std::string& str, std::optional<fg_uint> rank = std::nullopt);

fg_uint tree_nodes_num(fg_uint base, fg_uint level);

std::string h_index_to_str(std::vector<fg_uint> h_index);

std::vector<fg_uint> factorization(fg_uint idx, fg_uint base, fg_uint level);

std::vector<fg_uint> rank_to_h_index(fg_uint rank, fg_uint base, fg_uint max_level) ;

fg_uint h_index_to_rank(std::vector<fg_uint> h_index, fg_uint base, fg_uint max_level);


#endif //FGGRID_FGTREE_H
