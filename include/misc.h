//
// Created by dconsoli on 10-10-24.
//

#ifndef FGGRID_MISC_H
#define FGGRID_MISC_H

//#define FG_USE_MPI
#ifdef FG_USE_MPI
#include <mpi.h>
#endif

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cstdarg>
#include <optional>
#include <string_view>
#include <iomanip>

using fg_uint = long unsigned int;
using fg_int = long unsigned int;
using fg_float = float;
using fg_double = double;
using fg_real = float;
using fg_byte = unsigned char;
using fg_iter = long;

using FgMatUint = std::vector<std::vector<fg_uint>>;
using FgMatReal = std::vector<std::vector<fg_real>>;
using FgVecUint = std::vector<fg_uint>;
using FgVecReal = std::vector<fg_real>;

void fg_print(const std::string& str, std::optional<fg_uint> rank = std::nullopt);
template <typename T> std::string vec_to_str(std::vector<T> vec, std::optional<fg_uint> percision = std::nullopt);
inline fg_real points_distance(FgVecReal p1, FgVecReal p2)
{
    fg_real dist = 0;
    for (fg_iter k = 0; k < p1.size(); k++)
        dist += (p1[k] - p2[k]) * (p1[k] - p2[k]);
    return std::sqrt(dist);
}

#include "../src/misc.cxx"

#endif //FGGRID_MISC_H
