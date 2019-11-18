

#include "minCut.h"

cut minCut(double **C, int a, int dim)
{
    cut bestCut;
    bestCut.value = INFINITE;
    std::vector<int> V;
    for (int col = 0; col < dim; ++col)
    {
        if (col == a)
        {
            continue;
        }
        V.push_back(col);
    }

    for (int i = 0; i < dim - 1; ++i)
    {
        cut cut_of_phase = minCutPhase(C, a, dim, V);
        bestCut = cut_of_phase.value < bestCut.value ? cut_of_phase : bestCut;
    }

    return bestCut;
}