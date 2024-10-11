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

    inline fg_real points_distance(FgVecReal p1, FgVecReal p2)
    {
        fg_real dist = 0;
        for (fg_iter k = 0; k < p1.size(); k++)
            dist += (p1[k] - p2[k]) * (p1[k] - p2[k]);
        return std::sqrt(dist);
    }

    inline FgVecReal compute_centroid(FgMatReal points)
    {
        FgVecReal cetroid;
        for (fg_iter k = 0; k < points[0].size(); k++) {
            fg_real sum = 0;
            for (fg_iter i = 0; i < points.size(); i++)
                sum += points[i][k];
            cetroid.push_back(sum/points[0].size());
        }
        return cetroid;
    }

};

#endif //FGGRID_FGGEOMETRY_H
