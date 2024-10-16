//
// Created by dconsoli on 11-10-24.
//

#include "FgGeometry.h"

FgGeometry::FgGeometry(fg_real radius, fg_uint n_elem_l1)
        : radius(radius)
        , n_elem_l1(n_elem_l1)
{
    this->generate_l1_mesh();
}

FgMatReal FgGeometry::get_l1_vert()
{
    return this->mesh_vert;
}

FgMatUint FgGeometry::get_l1_cells()
{
    return this->mesh_cells;
}

void FgGeometry::generate_l1_mesh()
{
    bool check_geom_l1 = (this->n_elem_l1 == 20);
    assert(check_geom_l1 && "The geometry with the required number of cells in level 1 is not available.");

    fg_real golden_ratio = (1.+ sqrt(5)) / 2.;
    fg_real scaling = this->radius / std::sqrt(1.+golden_ratio*golden_ratio);
    for (fg_iter i = 0; i < 3; i++)
    {
        FgVecReal v0 = {0., scaling, golden_ratio*scaling};
        FgVecReal v1 = {0., scaling, -golden_ratio*scaling};
        FgVecReal v2 = {0., -scaling, golden_ratio*scaling};
        FgVecReal v3 = {0., -scaling, -golden_ratio*scaling};
        std::rotate(v0.begin(), v0.begin() + i, v0.end());
        std::rotate(v1.begin(), v1.begin() + i, v1.end());
        std::rotate(v2.begin(), v2.begin() + i, v2.end());
        std::rotate(v3.begin(), v3.begin() + i, v3.end());
        this->mesh_vert.insert(this->mesh_vert.end(), {v0, v1, v2, v3});
    }

    this->mesh_cells = {
            {0, 2, 8}, {0, 2, 9}, {0, 4, 6}, {0, 4, 8}, {0, 6, 9},
            {1, 3, 10}, {1, 3, 11}, {1, 4, 10}, {1, 4, 6}, {1, 6, 11},
            {5, 2, 7}, {5, 2, 8}, {5, 3, 7}, {5, 3, 10}, {5, 8, 10},
            {2, 7, 9}, {3, 11, 7}, {4, 8, 10}, {6, 9, 11}, {11, 7, 9}
    };
}


FgMatUint FgGeometry::get_l1_neighbors()
{
    FgMatReal centroids;
    for (auto & mesh_cell : mesh_cells)
    {
        FgMatReal verts_cell;
        for(fg_iter i : mesh_cell)
            verts_cell.push_back(mesh_vert[i]);
        FgVecReal centroid = this->compute_centroid(verts_cell);
        centroids.push_back(centroid);
    }

    FgMatUint l1_neighbors;
    for (auto & centroid1 : centroids)
    {
        FgVecReal distances;
        for (auto & centroid2 : centroids)
        {
            fg_real dist = this->points_distance(centroid1, centroid2);
            distances.push_back(dist);
        }
        FgVecUint indices(distances.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(),
                  [&distances](fg_uint i1, fg_uint i2) { return distances[i1] < distances[i2]; });
        FgVecUint neighbors;
        for (int i = 1; i <= mesh_cells[0].size(); i++)
            neighbors.push_back(indices[i]);
        l1_neighbors.push_back(neighbors);
    }

}