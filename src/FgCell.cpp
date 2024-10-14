//
// Created by dconsoli on 10-10-24.
//

#include "FgCell.h"

#include <utility>

FgCell::FgCell(std::vector<FgVertex> vertices, FgMatUint neighbors)
        : vertices(std::move(vertices))
        , neighbors(std::move(neighbors))
{
}

fg_real FgCell::get_area()
{

}
