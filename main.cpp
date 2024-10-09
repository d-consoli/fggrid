#include <iostream>
#include <mpi.h>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <sstream>

void debug(int rank, char *format ...)
{
    va_list args;
    va_start(args, format);
    printf("Rank %d | ", rank);
    vprintf(format, args);
    va_end(args);
}

#include <vector>
#include <algorithm>

std::vector<int> factorization(int idx, int base, int level){
    std::vector<int> h_index(level, 0);
    for(int i = 0; i < level; ++i)
    {
        h_index[i] = idx % base;
        idx /= base;
    }
    std::reverse(h_index.begin(), h_index.end());
    return h_index;
}

std::vector<int> rank_to_h_index(int rank, int base, int max_level, int n_elem_l1) {
    std::vector<int> h_index = {0};
    if (rank > 0)
    {
        int n_tree_elem = (std::pow(base,max_level - 1) - 1) / (base - 1);
        int l1_index = floor((rank - 1) / n_tree_elem);
        h_index.push_back(l1_index);
        if ((rank - 1) % n_tree_elem != 0) {
            int index_clean = rank - 1 - n_tree_elem * l1_index;
            int my_level = floor(std::log(index_clean * (base - 1) + 1) / std::log(base));
            index_clean -= (std::pow(base, my_level) - 1) / (base - 1);
            std::vector<int> h_index_clean = factorization(index_clean, base, my_level);
            h_index.insert(h_index.end(), h_index_clean.begin(), h_index_clean.end());
        }
    }
    return h_index;
}


int h_index_to_rank(std::vector<int> h_index, int base, int max_level) {
    int rank = 0;
    if (h_index.size() > 1)
    {
        int n_tree_elem = (std::pow(base,max_level - 1) - 1) / (base - 1);
        rank += 1 + n_tree_elem * h_index[1];
    }
    if (h_index.size() > 2)
    {
        rank += (std::pow(base, (h_index.size() - 2)) - 1) / (base - 1);
        for (int i = 2; i < h_index.size(); ++i)
        {
            rank += std::pow(base, (max_level-i-1)) * h_index[i];
        }
    }
    return rank;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
    int base = std::stoi(argv[1]);
    int max_level = std::stoi(argv[2]);
    int n_elem_l1 = std::stoi(argv[3]);

    bool condition = (n_proc == (std::pow(base,max_level - 1) - 1) / (base - 1) * n_elem_l1 + 1);
    assert(condition && "Number of processes is not the expected one from the levels and the base.");

    std::vector<int> h_index = rank_to_h_index(rank, base, max_level, n_elem_l1);
    std::stringstream ss;
    for (size_t i=0; i<h_index.size(); ++i) {
        ss << h_index[i];
        if (i != h_index.size() - 1) {
            ss << ".";
        }
    }
    ss << "\n";
    std::string str = ss.str();
    char* cstr = &str[0];
    debug(rank, cstr);
    int check_rank = h_index_to_rank(h_index, base, max_level);
    debug(rank, "Check rank %d \n", check_rank);

    MPI_Finalize();
    return 0;
}