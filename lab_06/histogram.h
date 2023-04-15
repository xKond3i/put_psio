#pragma once

class Histogram
{
    std::map<int, int> bins_;

    using BinsVector = std::vector<std::pair<int, int>>;

public:
    Histogram(const std::vector<int> &data = std::vector<int>());
    void emplace(int v);
    void emplace(const std::vector<int> &data);

    void clear();
    bool from_csv(const std::string &filename, char delim = ',', int column_idx = 4);
    std::pair<int, int> max() const;
    std::pair<int, int> range() const;
    std::vector<int> unique_bins() const;
    BinsVector unique_items() const;

    Histogram& operator<<(int v);
    static Histogram generate(int min, int max, int count);// tworzy histogram zawierający wartości losowe, gdzie kolejne argumenty oznaczają wartość minimalną, maksymalną, liczbę elementów
    int operator[](int v) const; // zwraca częstość dla binu w indeksie
    operator BinsVector(); // operator konwersji na typ `BinsVector` (`std::vector<std::pair<int, int>>`)

    friend std::istream &operator>>(std::istream &str, Histogram &hist);
    friend std::ostream &operator<<(std::ostream &str, const Histogram &hist);
};
