#ifndef UTILS_H_
#define UTILS_H_

#include <queue>
#include <utility>

template <class T, class A>
class CompareDist
{
public:
    bool operator()(std::pair<int, double> n1, std::pair<int, double> n2)
    {
        return n1.second > n2.second;
    }
};

#endif
