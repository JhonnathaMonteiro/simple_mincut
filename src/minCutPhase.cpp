#include <iostream>

#include "minCutPhase.h"

void _contractEdges(int v1, int v2, double **C, int dim, cut &cut_of_phase)
{
    cut_of_phase.value = 0;
    for (int i = 0; i < dim; ++i)
    {
        if (C[v2][i] > 0)
        {
            std::pair<int, int> edge = std::make_pair(v2, i);
            cut_of_phase.edges.push_back(edge);
            cut_of_phase.value += C[v2][i];
            C[v1][i] = C[i][v1] += C[v2][i];
            C[v2][i] = C[i][v2] = 0;
        }
    }
    C[v1][v2] = C[v2][v1] = 0;
}

cut minCutPhase(double **C,
                int a,
                int dim,
                std::vector<int> &V)
{

    int s, t;
    std::vector<int> A, Vcopy;
    A.push_back(a);

    // construindo a fibonacci heap
    FibonacciHeap<double> fbHeap;
    for (auto &vi : V)
    {
        fbHeap.insert(vi, -C[a][vi]); // -C para ExtractMin -> ExtractMax
        Vcopy.push_back(vi);
    }

    while (!fbHeap.isEmpty())
    {

        a = fbHeap.extractMin();
        A.push_back(a);
        Vcopy.erase(std::remove(Vcopy.begin(), Vcopy.end(), a), Vcopy.end());

        // Update fbHeap
        for (auto &col : Vcopy)
        {
            if (C[a][col] > 0)
            {
                node<double> *n = fbHeap.find(col);
                fbHeap.decreaseKey(n, -C[a][col] + n->getValue());
            }
        }
    }

    // srink s-t
    cut cut_of_phase;
    s = *(A.rbegin() + 1);
    t = *(A.rbegin());
    V.erase(std::remove(V.begin(), V.end(), a), V.end());
    _contractEdges(s, t, C, dim, cut_of_phase);

    return cut_of_phase;
}