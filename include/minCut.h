#ifndef MIN_CUT_H_
#define MIN_CUT_H_

#include <limits>
#include "minCutPhase.h"
#include "cut.h"

#define INFINITE std::numeric_limits<double>::infinity();

Cut minCut(double **, int, int);

#endif // MIN_CUT_H_