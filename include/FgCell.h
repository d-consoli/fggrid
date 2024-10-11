//
// Created by dconsoli on 10-10-24.
//

#ifndef FGGRID_FGCELL_H
#define FGGRID_FGCELL_H

#include "misc.h"
#include "FgVertex.h"

class FgCell {
protected:
    std::vector<FgVertex> vertices;

public:

    FgCell(std::vector<FgVertex> vertices);
    fg_real get_area();
//    void convertProjTo3D(FgVecReal in_vert);
//    void convert3DToProj(FgVecReal in_vert);

};


#endif //FGGRID_FGCELL_H
