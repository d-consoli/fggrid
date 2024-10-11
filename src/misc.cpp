//
// Created by dconsoli on 10-10-24.
//

#include "misc.h"

void fg_print(const std::string& str, std::optional<fg_uint> rank)
{
    std::stringstream ss;
    if (rank.has_value())
        ss << "Rank " << rank.value() << " | ";
    ss << str << std::endl;
    std::cout << ss.str();
}


