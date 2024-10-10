//
// Created by dconsoli on 10-10-24.
//

#ifndef FGGRID_FGCELL_H
#define FGGRID_FGCELL_H

#include "misc.h"

class FgCell {
protected :
    FgMatUint vert_id_3d;
    FgMatUint vert_id_proj;
    FgMatReal vert_coord_3d;
    FgMatReal vert_coord_proj;
public :

    FgCell(FgMatUint vert_id_3d, FgMatReal vert_coord_3d);
    void convertProjTo3D(FgVecReal in_vert);
    void convert3DToProj(FgVecReal in_vert);

};


#endif //FGGRID_FGCELL_H
