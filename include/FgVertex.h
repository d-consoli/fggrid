//
// Created by dconsoli on 11-10-24.
//

#ifndef FGGRID_FGVERTEX_H
#define FGGRID_FGVERTEX_H

#include "misc.h"

/* Vertices are identified from the couple of cells ID (rank)
 * sharing the same edge at half of which the vertex is generated
 * and are ordered from smaller to bigger */

class FgVertex {
protected:
    FgVecUint vert_id;
    FgVecReal coord;

public:
    FgVertex(fg_uint id_p1, fg_uint id_p2, FgVecReal coord);
};


#endif //FGGRID_FGVERTEX_H
