//
// Created by dconsoli on 10-10-24.
//

#include "FgCell.h"

#include <utility>

FgCell::FgCell(std::vector<FgVertex> vertices)
        : vertices(std::move(vertices))
{
}

fg_real FgCell::get_area()
{

}
