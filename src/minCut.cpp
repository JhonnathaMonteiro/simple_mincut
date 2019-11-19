#include "minCut.h"

Cut minCut(double **C, int a, int dim)
{
    Cut bestCut;
    vector_of_pairs stList;
    double inf = INFINITE;
    bestCut.setCost(inf);
    std::vector<int> V;
    for (int col = 0; col < dim; ++col)
    {
        if (col == a)
        {
            continue;
        }
        V.push_back(col);
    }

    std::vector<std::vector<double>> C_init(dim, std::vector<double>(dim));
    for (size_t i = 0; i < dim; i++)
    {
        for (size_t j = i; j < dim; j++)
        {
            C_init[i][j] = C_init[j][i] = C[i][j];
        }
    }

    Cut cut_of_phase;
    for (int i = 0; i < dim - 1; ++i)
    {
        cut_of_phase = minCutPhase(C, a, dim, V, stList);
        if (cut_of_phase.getCost() < bestCut.getCost())
        {
            bestCut = cut_of_phase;
        }
    }

    bestCut.setW(C_init);
    bestCut.findEdges();

    return bestCut;
}