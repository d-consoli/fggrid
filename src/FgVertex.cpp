//
// Created by dconsoli on 11-10-24.
//

#include "FgVertex.h"

FgVertex::FgVertex(fg_uint id_p1, fg_uint id_p2, FgVecReal coord)
    : coord(coord),
      vert_id{std::min(id_p1, id_p2), std::max(id_p1, id_p2)}
{}
