template <typename T>
Histogram<T>::Histogram(const std::vector<T> &data) {
    for (const T value : data) ++bins_[value];
}

template <typename T>
void Histogram<T>::emplace(const T& v) {
    ++bins_[v];
}

template <typename T>
void Histogram<T>::emplace(const std::vector<T> &data) {
    for (const T value : data) ++bins_[value];
}

template <typename T>
void Histogram<T>::clear() {
    bins_.clear();
}

template <typename T>
bool Histogram<T>::from_csv(const std::string &filename, char delim, int column_idx) {
    std::ifstream file(filename, std::ios::in); // open file
    if (!file.is_open()) return false; // handle an error occured while opening the file

    std::string line;
    while (std::getline(file, line)) { // get file line by line
        std::stringstream ss(line);
        std::string column_val;
        int column_id = 0;
        T value;
        while (std::getline(ss, column_val, delim)) { // get line column by column (separated by delimeter)
            if (column_id != column_idx) {
                ++column_id;
                continue;
            }
            std::stringstream ss_val(column_val);
            ss_val >> value;
            break;
        }
        ++bins_[value];
    }

    file.close();
    return true; // loaded successfully
}

template <typename T>
std::pair<T, int> Histogram<T>::min() const {
    return *std::min_element(bins_.begin(), bins_.end(),
        [](const auto & a, const auto & b) { return a.second < b.second; }
    );
}

template <typename T>
std::pair<T, int> Histogram<T>::max() const {
    return *std::max_element(bins_.begin(), bins_.end(),
        [](const auto & a, const auto & b) { return a.second < b.second; }
    );
}

template <typename T>
std::pair<int, int> Histogram<T>::range() const {
    return std::make_pair(min().second, max().second);
}

template <typename T>
std::vector<T> Histogram<T>::unique_bins() const {
    BinsVector unique;
    copy_if(bins_.begin(), bins_.end(), std::back_inserter(unique), [](auto pair){return pair.second == 1;});
    return unique;
}

template <typename T>
Histogram<T> Histogram<T>::generate(int min, int max, int count) {
    Histogram<T> h;
    for (int i = 0; i < count; i++) h.emplace(rand() * (max - min) + min);
    return h;
}

template <typename T>
Histogram<T> Histogram<T>::generate(int count, int (*func_ptr)())
{
    Histogram<T> h;
    for (int i = 0; i < count; i++) h.emplace(func_ptr());
    return h;
}

template <typename T>
void Histogram<T>::print(const int num_of_records) {
    for (auto it = bins_.begin(); it != bins_.end(); ++it) {
        const auto & [record, count] = *it;
        int pos = std::distance(bins_.begin(), it);
        if (pos == num_of_records) {
            std::cout << "and " << (bins_.size() - pos) << " more...\n";
            break;
        }
        std::cout << (pos+1) << ". " << record << ": " << count << "\n";
    }
}
