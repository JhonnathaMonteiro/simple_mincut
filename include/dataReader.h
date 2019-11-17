#ifndef DATA_PMCC_H_
#define DATA_PMCC_H_

#include <set>     // std::set
#include <utility> // std::pair std::make_pair
#include <vector>  // std::vector
#include <fstream> // std::fstream

template <class T>
class dataReader
{
private:
   int const vertex;
   int const labels;
   int const default_value = -1;
   T **matrix;

public:
   dataReader(char *file_path);
   ~dataReader();

   int getVertex() { return vertex; }
   int getLabels() { return labels; }
   T **getMatrix() { return matrix; }
};

template <class T>
dataReader<T>::dataReader(char *file_path)
{
   std::ifstream file(file_path);
   file >> vertex >> labels;

   matrix = new T *[vertex];
   for (int i = 0; i < vertex; ++i)
   {
      matrix[i] = new double[vertex];
   }

   for (int i = 0; i < vertex; ++i)
   {
      matrix[i][i] = default_value;
   }

   for (int row = 0; row < vertex - 1; ++row)
   {
      for (int col = row + 1; col < vertex; ++col)
      {
         file >> matrix[row][col];
         matrix[col][row] = matrix[row][col];
      }
   }
}

template <class T>
dataReader<T>::~dataReader()
{
   for (int i = 0; i < vertex; i++)
   {
      delete[] matrix[i];
   }
   delete[] matrix;
}

#endif
