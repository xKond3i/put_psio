#pragma once

#include <vector>
#include <iostream>

template <typename T>
class CIVector { // stands for Custom Implementation of Vector
    std::vector<T> values;

public:
    CIVector(const std::vector<T> &data = std::vector<T>());
};
