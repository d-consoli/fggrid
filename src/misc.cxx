//
// Created by dconsoli on 11-10-24.
//


#include "misc.h"

template <typename T>
std::string vec_to_str(std::vector<T> vec, std::optional<fg_uint> percision){
    if (percision.has_value())
    {
        std::cout << std::fixed;
        std::cout << std::setprecision(percision.value());
    }
    std::stringstream ss;
    for (size_t i=0; i<vec.size(); ++i) {
        ss << vec[i];
        if (i != vec.size() - 1) {
            ss << " | ";
        }
    }
    return ss.str();
}