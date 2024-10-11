//
// Created by dconsoli on 11-10-24.
//

#ifndef FGGRID_FGGEOMETRY_H
#define FGGRID_FGGEOMETRY_H

#include "misc.h"

class FgGeometry {

protected :

    fg_real radius;
    fg_uint n_elem_l1;

public :

    FgGeometry(fg_real radius, fg_uint n_elem_l1);
    void get_l1_mesh(FgMatReal &mesh_vert, FgMatUint &mesh_cells);

};

#endif //FGGRID_FGGEOMETRY_H
