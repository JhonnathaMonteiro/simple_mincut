#include <iostream>

#include "dataReader.h"

int main(int argc, char **argv)
{
    dataReader<double> data(argv[1]);
    double **C = data.getMatrix();

    // readInstance(argv[1]);
    std::cout << data.getVertex() << std::endl;

    for (int i = 0; i < data.getVertex(); i++)
    {
        for (int j = 0; j < data.getVertex(); j++)
        {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
}