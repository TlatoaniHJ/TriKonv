//
// Created by Danny Mittal on 12/15/25.
//

#ifndef TRIKONV_EVALUATION_H
#define TRIKONV_EVALUATION_H

#include <vector>

using ll = long long;
using ull = unsigned long long;

struct Algorithm {
    std::vector<int> (*function)(std::vector<int>, std::vector<int>);
    std::string name;
    int lower_bound;
    int upper_bound;
    int can_swap;
};

#endif //TRIKONV_EVALUATION_H