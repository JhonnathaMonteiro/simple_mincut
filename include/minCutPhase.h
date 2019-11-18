#ifndef MIN_CUT_PHASE_H_
#define MIN_CUT_PHASE_H_

#include <vector>
#include <algorithm> // erase
#include "fibonacciHeap.h"

typedef struct Cut
{
    std::vector<std::pair<int, int>> edges;
    double value;
} cut;

cut minCutPhase(double **, int, int, std::vector<int> &);

#endif // MIN_CUT_PHASE_H_