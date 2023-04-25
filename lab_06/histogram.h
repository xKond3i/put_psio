#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

// fragment klasy Histogram z poprzednich przykładów
template <typename T>
class Histogram
{
    std::map<T, int> bins_;

    using BinsVector = std::vector<std::pair<T, int>>;

public:
    // CONSTRUCTORS
    Histogram(const std::vector<T> &data = std::vector<T>());

    // PRINT
    void print(const int num_of_records = -1);

    // MODIFY DATA
    void emplace(const T& v);
    void emplace(const std::vector<T> &data);
    void clear();

    // LOAD DATA FROM FILES
    bool from_csv(const std::string &filename, char delim = ',', int column_idx = 4); // some sort of `header_included` option could be added, but the instruction doesn't mention it

    // CONSTANT DATA
    std::pair<T, int> min() const;
    std::pair<T, int> max() const;
    std::pair<int, int> range() const;
    std::vector<T> unique_bins() const;

    // STATIC METHODS
    static Histogram generate(int min, int max, int count);
    static Histogram generate(int count, int (*func_ptr)());

    // OPERATORS
    Histogram& operator<< (T v) {
        this -> emplace(v);
        return *this;
    }

    int operator[] (T v) const {
        return bins_.find(v);
    }

    operator BinsVector(); // operator konwersji na typ `BinsVector` (`std::vector<std::pair<int, int>>`)

    friend std::istream &operator>> (std::istream &str, Histogram &hist) {
        T val;
        while (str >> val) hist.emplace(val);
        return str;
    }

    friend std::ostream &operator<< (std::ostream &str, const Histogram &hist) {
        for (const auto & record : hist.bins_) str << record.first << ": " << record.second << "\n";
        return str;
    }
};

#include "histogram.tpp"
