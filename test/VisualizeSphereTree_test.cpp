//
// Created by dconsoli on 10-10-24.
//

//#define FG_USE_MPI
#define FG_VISUALIZE
#include "../include/FgTree.h"
#include "../include/FgVisualizer.h"

#include <omp.h>

#ifdef FG_USE_MPI
#include <mpi.h>
#endif

std::string vec_to_str(std::vector<fg_real> h_index){
    std::stringstream ss;
    for (size_t i=0; i<h_index.size(); ++i) {
        ss << h_index[i];
        if (i != h_index.size() - 1) {
            ss << " . ";
        }
    }
    return ss.str();
}

int main(int argc, char** argv) {
#ifdef FG_USE_MPI
    MPI_Init(&argc, &argv);
    int rank_int;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_int);
    auto rank = fg_uint(rank_int);
    int n_proc_int;
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc_int);
    auto n_proc = fg_uint(n_proc_int);
#endif

    fg_uint base = fg_uint(std::stoi(argv[1]));
    fg_uint max_level = std::stoi(argv[2]);
    fg_uint n_elem_l1 = std::stoi(argv[3]);

#ifdef FG_USE_MPI
    bool condition = (n_proc == tree_nodes_num(base, max_level - 1) * n_elem_l1 + 1);
    assert(condition && "Number of processes is not the expected one from the levels and the base.");
#else
    fg_uint n_proc = fg_uint (std::pow(base,max_level - 1) - 1) / (base - 1) * n_elem_l1 + 1;
    omp_set_num_threads(int(n_proc));
#pragma omp parallel for
    for (fg_uint rank = 0; rank < n_proc; rank ++) {
#endif
        std::vector<fg_uint> h_index = rank_to_h_index(rank, base, max_level);
        bool check_rank = (rank == h_index_to_rank(h_index, base, max_level));
        assert(check_rank && "Rank form h-index not matching the correct one.");
//        if (rank > 0 && rank <= n_elem_l1)
//        {
//
//        }


#ifndef FG_USE_MPI
    }
#ifdef FG_VISUALIZE
    vtkNew<vtkPolyData> polydata;
    fg_real golden_ratio = (1.+ sqrt(5)) / 2.;
    FgMatReal mesh_vert;
    for (fg_iter i = 0; i < 3; i++)
    {
        FgVecReal v0 = {0., 1., golden_ratio};
        FgVecReal v1 = {0., 1., -golden_ratio};
        FgVecReal v2 = {0., -1., golden_ratio};
        FgVecReal v3 = {0., -1., -golden_ratio};
        std::rotate(v0.begin(), v0.begin() + i, v0.end());
        std::rotate(v1.begin(), v1.begin() + i, v1.end());
        std::rotate(v2.begin(), v2.begin() + i, v2.end());
        std::rotate(v3.begin(), v3.begin() + i, v3.end());
        mesh_vert.insert(mesh_vert.end(), {v0, v1, v2, v3});
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    for (fg_iter i = 0; i < mesh_vert.size(); i++)
    {
//        fg_print("ID " + std::to_string(i) + ": " + vec_to_str(mesh_vert[i]));
        std::cout << i << ": ";
        for (fg_iter j = 0; j < mesh_vert.size(); j++)
        {
            fg_real dist = 0;
            for (fg_iter k = 0; k < 3; k++)
            {
                dist += (mesh_vert[i][k] - mesh_vert[j][k]) * (mesh_vert[i][k] - mesh_vert[j][k]);
            }
            dist = std::sqrt(dist);
            if (dist > 1. && dist < 3.)
                std::cout << j << " ";
        }
        std::cout << endl;

    }


    FgMatUint mesh_cells = {
            {0, 2, 8}, {0, 2, 9}, {0, 4, 6}, {0, 4, 8}, {0, 6, 9},
            {1, 3, 10}, {1, 3, 11}, {1, 4, 10}, {1, 4, 6}, {1, 6, 11},
            {5, 2, 7}, {5, 2, 8}, {5, 3, 7}, {5, 3, 10}, {5, 8, 10},
            {2, 7, 9}, {3, 11, 7}, {4, 8, 10}, {6, 9, 11}, {11, 7, 9}
    };

    generate_polygon(polydata, mesh_vert, mesh_cells);
    visualize_polydata(polydata, 2.0);

#endif
#else
    MPI_Finalize();
#endif

    return 0;
}
