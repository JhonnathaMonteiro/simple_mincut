#include <iostream>

#include "dataReader.h"
#include "minCutPhase.h"
#include "minCut.h"
#include "fibonacciHeap.h"

int main(int argc, char **argv)
{

    dataReader<double> data(argv[1]);
    double **C = data.getMatrix();

    int dim = data.getVertex();
    int a = 1;

    Cut min_cut = minCut(C, a, dim);
}
