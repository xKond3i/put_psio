#pragma once

#include <vector>
#include <iostream>

template <typename T>
class CIVector { // stands for Custom Implementation of Vector
    std::vector<T> values_;

public:
    CIVector(const std::vector<T> & data = std::vector<T>()) {
        for (const auto & val : data) {
            values_.push_back(val);
        }
    };

    friend std::ostream & operator << (std::ostream & str, const CIVector & vec) {
        str << "[";
        int size = vec.values_.size();
        for (int i = 0; i < size; ++i) {
            str << vec.values_[i] << (i < (size - 1) ? ", " : "");
        }
        str << "]";
        return str;
    }

    CIVector operator + (const T & num) {
        CIVector<T> result(values_);
        for (int i = 0; i < values_.size(); ++i) { result.values_[i] = values_[i] + num; }
        return result;
    }
    CIVector operator + (const CIVector & other) {
        // could add error handling (stdexcept needed) -> e.g. vectors have to be the same size
        CIVector<T> result(values_);
        for (int i = 0; i < values_.size(); ++i) { result.values_[i] = values_[i] + other.values_[i]; }
        return result;
    }
    // could add += support

    CIVector operator - (const T & num) {
        CIVector<T> result(values_);
        for (int i = 0; i < values_.size(); ++i) { result.values_[i] = values_[i] - num; }
        return result;
    }
    CIVector operator - (const CIVector & other) {
        // could add error handling (stdexcept needed) -> e.g. vectors have to be the same size
        CIVector<T> result(values_);
        for (int i = 0; i < values_.size(); ++i) { result.values_[i] = values_[i] - other.values_[i]; }
        return result;
    }
    // could add -= support

    CIVector operator * (const T & num) {
        CIVector<T> result(values_);
        for (int i = 0; i < values_.size(); ++i) { result.values_[i] = values_[i] * num; }
        return result;
    }
};
