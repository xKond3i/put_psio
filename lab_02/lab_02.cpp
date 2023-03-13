// PSiO Poznan University Of Technology
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2002%20-%20Algorytmy.html
// Executed by Konrad Ceglarski
// 12/03/2023

#include <iostream>
#include <string>
#include <algorithm>
// #include <cctype>
#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
#include <limits>

#include <windows.h> // UTF-8 encoding for Windows

using namespace std;

// operator `<<` overload for ostream and vector -> helps dispalying vector in terminal
template <typename T>
ostream& operator << (ostream& os, vector<T> vec) {
    os << "{";
    for (int i = 0; i < vec.size(); ++i) os << vec[i] << (i != vec.size() - 1 ? ", " : "");
    os << "}\n";
    return os;
}

// 🛠 Zadanie 1: Palindrom
#pragma region Zadanie 1
bool is_palindrome(string word) {
    //// could use string::erase method combined with remove_if to get rid of spaces
    // word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());
    //// could use transform with lambda expression -> [captures](params){body}
    // transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); });
    //// could use std::reverse function too
    // reverse(reversed.begin(), reversed.end());

    // but we'll use more basic implementation of code above - just to show, that I'm familiar with how it works:
    // 1) let's get rid of the spaces:
    string spaceless_word = "";
    size_t space_pos;
    size_t previous_pos = 0;

    do {
        space_pos = word.find(' ', previous_pos);
        spaceless_word += word.substr(previous_pos, space_pos - previous_pos);
        previous_pos = space_pos + 1;
    } while (space_pos != string::npos);

    // 2) compare lowercase chars, but just half - as comparing pairs the other half is just mirrored pairs
    int word_len = spaceless_word.length();
    for (int i = 0; i <= word_len / 2; ++i) {
        if (tolower(spaceless_word[i]) != tolower(spaceless_word[word_len - i - 1])) return false;
    }

    return true;
}
#pragma endregion

// 🛠 Zadanie 2: Znalezienie wszystkich wystąpień znaku
#pragma region Zadanie 2
vector<size_t> find_all(string input, char search) {
    vector<size_t> ans;
    size_t pos = 0;

    while ((pos = input.find(search, pos + 1)) != string::npos) {
        ans.push_back(pos);
    }

    return ans;
}
#pragma endregion

// 🛠 Zadanie 3: Szukanie najdłuższego wyrazu
#pragma region Zadanie 3
string find_longest_word(string input) {
    string longest;
    string word;
    size_t space_pos;
    size_t previous_pos = 0;

    do {
        space_pos = input.find(' ', previous_pos);
        word = input.substr(previous_pos, space_pos - previous_pos);
        if (word.length() > longest.length()) longest = word;
        previous_pos = space_pos + 1;
    } while (space_pos != string::npos);

    return longest;
}
#pragma endregion

// 🛠 Zadanie 4: Podział napisów
#pragma region Zadanie 4
vector<string> split(string input, char sep=' ') {
    vector<string> ans;

    size_t sep_pos;
    size_t previous_pos = 0;
    do {
        sep_pos = input.find(' ', previous_pos);
        ans.push_back(input.substr(previous_pos, sep_pos - previous_pos));
        previous_pos = sep_pos + 1;
    } while (sep_pos != string::npos);

    return ans;
}
#pragma endregion

// 🛠 Zadanie 5: Znajdź i zamień
#pragma region Zadanie 5
string find_and_replace(string input, string search, string replace) {
    string ans;
    size_t search_pos;
    size_t previous_pos = 0;

    do {
        search_pos = input.find(search, previous_pos);
        ans += input.substr(previous_pos, search_pos - previous_pos);
        if (search_pos != string::npos) ans += replace;
        previous_pos = search_pos + search.length();
    } while (search_pos != string::npos);

    return ans;
}
#pragma endregion

// 🛠 Zadanie 6: Sortowanie bąbelkowe
#pragma region Zadanie 6
vector<double> bubble_sort(vector<double> nums) {
    // variables names as they are on the diagram
    vector<double> a = nums; // sorted vector
    int rozmiar = a.size();
    bool swap_made;

    // i am terrible at reading block diagrams <- i've done it a bit diffrently i guess
    do { // `rozmiar--` loop
        swap_made = false;
        for (int i = 0; i < rozmiar - 1; ++i) { // `i++` loop
            if (a[i] > a[i+1]) {
                swap(a[i], a[i+1]);
                swap_made = true;
            }
        }
        --rozmiar;
    } while (swap_made);

    return a;
}
#pragma endregion

// 🛠 Zadanie 7: Przeszukiwanie binarne
#pragma region Zadanie 7
int binary_search(vector<double> collection, double search) {
    /*
    1) Sprawdź wartość środkową w kolekcji. Jeśli jest:
    * poszukiwaną wartością: koniec algorytmu
    * większa od poszukiwanej wartości: poszukiwany element znajduje się w pierwszej połowie kolekcji
    * mniejsza od poszukiwanej wartości: poszukiwany element znajduje się w drugiej połowie kolekcji
    2) Twój nowy zbiór to wybrana połowa.
    3) Wróć do kroku 1 z nowym zbiorem wejściowym, aż do znalezienia poszukiwanego elementu lub wyczerpania możliwości.
    */
    int searching_bound_min = 0;
    int searching_bound_max = collection.size() - 1;
    int shot;
    while (searching_bound_min != searching_bound_max) {
        shot = (searching_bound_min + searching_bound_max) / 2;
        // cout << shot << " <" << searching_bound_min << "; " << searching_bound_max << ">\n";
        if ((searching_bound_min + searching_bound_max) % 2 == 1) if (collection[shot-1] == search) return shot - 1; // if middle consists 2 numbers (set is even)
        if (collection[shot] == search) return shot;
        else if (collection[shot] < search) searching_bound_min = shot + 1;
        else if (collection[shot] > search) searching_bound_max = shot - 1;
    }
    return -1;
}
#pragma endregion

// 🛠 Zadanie 8: Kursy walut
#pragma region Zadanie 8
struct Exchange_rate
{
    std::string date;
    double usd;
    double eur;
    std::string table_id;
};

vector<Exchange_rate> sort_usd(vector<Exchange_rate> rates) {
    // variables names as they are on the diagram
    vector<Exchange_rate> a = rates; // sorted vector
    int rozmiar = a.size();
    bool swap_made;

    // i am terrible at reading block diagrams <- i've done it a bit diffrently i guess
    do { // `rozmiar--` loop
        swap_made = false;
        for (int i = 0; i < rozmiar - 1; ++i) { // `i++` loop
            if (a[i].usd > a[i+1].usd) {
                swap(a[i], a[i+1]);
                swap_made = true;
            }
        }
        --rozmiar;
    } while (swap_made);

    return a;
}

vector<Exchange_rate> sort_eur(vector<Exchange_rate> rates) {
    // variables names as they are on the diagram
    vector<Exchange_rate> a = rates; // sorted vector
    int rozmiar = a.size();
    bool swap_made;

    // i am terrible at reading block diagrams <- i've done it a bit diffrently i guess
    do { // `rozmiar--` loop
        swap_made = false;
        for (int i = 0; i < rozmiar - 1; ++i) { // `i++` loop
            if (a[i].eur > a[i+1].eur) {
                swap(a[i], a[i+1]);
                swap_made = true;
            }
        }
        --rozmiar;
    } while (swap_made);

    return a;
}


#pragma endregion

// 🛠 Zadanie 9: Temperatury
#pragma region Zadanie 9
struct WeatherData {
    // i just need temperature, no need for all of the data...
    string date;
    string time;
    double temp;
};

double get_temp_min(vector<WeatherData> data) {
    double ans = numeric_limits<double>::infinity();
    for (auto record : data) {
        if (record.temp < ans) ans = record.temp;
    }
    return ans;
}

double get_temp_max(vector<WeatherData> data) {
    double ans = numeric_limits<double>::infinity() * (-1);
    for (auto record : data) {
        if (record.temp > ans) ans = record.temp;
    }
    return ans;
}

vector<WeatherData> sort_by_temp(vector<WeatherData> data) {
    // variables names as they are on the diagram
    vector<WeatherData> a = data; // sorted vector
    int rozmiar = a.size();
    bool swap_made;

    // i am terrible at reading block diagrams <- i've done it a bit diffrently i guess
    do { // `rozmiar--` loop
        swap_made = false;
        for (int i = 0; i < rozmiar - 1; ++i) { // `i++` loop
            if (a[i].temp > a[i+1].temp) {
                swap(a[i], a[i+1]);
                swap_made = true;
            }
        }
        --rozmiar;
    } while (swap_made);

    return a;
}
#pragma endregion

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 🛠 Zadanie 1: Palindrom
    cout << "Zadanie 1: Palindrom\n";
    #pragma region Zadanie 1
    std::string word = "racecar";
    if (is_palindrome(word)) {
        std::cout << "To palindrom!" << std::endl;
    } else {
        std::cout << "Nope" << std::endl;
    }

    std::string sentence = "Never odd or even";
    cout << is_palindrome(sentence) << "\n"; // true
    #pragma endregion

    // 🛠 Zadanie 2: Znalezienie wszystkich wystąpień znaku
    cout << "\nZadanie 2: Znalezienie wszystkich wystąpień znaku\n";
    #pragma region Zadanie 2
    std::string input = "Ala ma kota";

    std::vector<size_t> pos = find_all(input, 'a'); // wynik: {2, 5, 10}
    cout << pos;
    #pragma endregion

    // 🛠 Zadanie 3: Szukanie najdłuższego wyrazu
    cout << "\nZadanie 3: Szukanie najdłuższego wyrazu\n";
    #pragma region Zadanie 3
    input = "Ala ma kota kot jezdzi na Roombie";

    std::string longest = find_longest_word(input); // "Roombie"
    cout << longest << "\n";
    #pragma endregion

    // 🛠 Zadanie 4: Podział napisów
    cout << "\nZadanie 4: Podział napisów\n";
    #pragma region Zadanie 4
    sentence = "Ala ma kota";
    std::vector<std::string> words = split(sentence); // wynik: {"Ala", "ma", "kota"}

    std::string csv = "Mount Everest,8848,1953";
    std::vector<std::string> data = split(csv, ','); // wynik: {"Mount Everest", "8848", "1953"}

    cout << words << data;
    #pragma endregion

    // 🛠 Zadanie 5: Znajdź i zamień
    cout << "\nZadanie 5: Znajdź i zamień\n";
    #pragma region Zadanie 5
    input = "Ala ma kota, kot zjadl Ale!";
    std::string output = find_and_replace(input, "kot", "hefalump");

    cout << output << "\n";
    // wynik: "Ala ma hefalumpa, hefalump zjadl Ale!"
    #pragma endregion

    // 🛠 Zadanie 6: Sortowanie bąbelkowe
    cout << "\nZadanie 6: Sortowanie bąbelkowe\n";
    #pragma region Zadanie 6
    srand(time(NULL));
    vector<double> nums(10);
    for (int i = 0; i < 10; ++i) nums[i] = rand() % 100; //// fill vector with random numbers

    cout << "Przed sortowaniem: " << nums;
    cout << "Po sortowaniu:     " << bubble_sort(nums);
    #pragma endregion

    // 🛠 Zadanie 7: Przeszukiwanie binarne
    cout << "\nZadanie 7: Przeszukiwanie binarne\n";
    #pragma region Zadanie 7
    vector<vector<double>> collections = {{1, 2, 5, 8, 9, 11, 15}, {1, 2, 3, 4, 5, 6}, {1, 4, 5, 8}, {1, 5, 6, 8}, {1, 2, 3, 4, 6, 7, 8, 9, 5}};
    double search = 5;
    for (auto collection : collections) {
        double found = binary_search(collection, search);
        cout << "Zbiór: " << collection;
        if (found != -1) cout << "Posiada element `" << search << "` na pozycji " << found << ".\n";
        else             cout << "Nie posiada elementu `" << search << "`!\n";
    }
    #pragma endregion

    // 🛠 Zadanie 8: Kursy walut
    cout << "\nZadanie 8: Kursy walut\n";
    #pragma region Zadanie 8
    // Wczytaj plik kursy_usd_eur.csv zgodnie z wytycznymi z wprowadzenia
    std::fstream file("kursy_usd_eur.csv", std::fstream::in);
    std::vector<Exchange_rate> rates;
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // wczytuje pierwszą linię z nagłówkiem i ją ignoruje
        while (std::getline(file, line)) {//wczytuje kolejne linie aż do końca pliku
            std::stringstream str(line);//tworzy strumień, którego źródłem jest wczytana linia

            Exchange_rate er;
            std::getline(str, er.date, ','); //wczytuje date (pierwszy element wiersza)
            std::string double_str;
            std::getline(str, double_str, ',');  // wczytuje kurs USD (jako tekst)
            er.usd = std::stod(double_str);      //zamiana na string->double
            std::getline(str, double_str, ',');  // wczytuje kurs EUR (jako tekst)
            er.eur = std::stod(double_str);      //zamiana na string->double
            std::getline(str, er.table_id, ','); // wczytuje ostatnią kolumnę z numerem tabeli NBP
            rates.emplace_back(er); //dodaje element do kolekcji
        }
    }
    // Posortuj plik względem kursu USD modyfikując algorytm sortowania bąbelkowego - twórz w tym celu 2 funkcje sort_usd(rates) oraz sort_eur(rates) sortująca wektor z danymi kursów wg kursu USD i EUR.
    std::vector<Exchange_rate> sorted_by_usd = sort_usd(rates);
    std::vector<Exchange_rate> sorted_by_eur = sort_eur(rates);
    size_t rates_len = rates.size();
    // Wyświetl 10 dni (datę oraz wartość), w których kurs USD był najwyższy
    cout << "Wyświetl 10 dni (datę oraz wartość), w których kurs USD był najwyższy:\n";
    for (int i = 0; i < 10; ++i) {
        auto rate = sorted_by_usd[rates_len - 1 - i];
        cout << (i + 1) << ". " << rate.date << " " << rate.usd << "\n";
    }
    // Wyświetl 10 dni (datę oraz wartość), w których kurs EUR był najniższy
    cout << "Wyświetl 10 dni (datę oraz wartość), w których kurs EUR był najniższy:\n";
    for (int i = 0; i < 10; ++i) {
        auto rate = sorted_by_eur[i];
        cout << (i + 1) << ". " << rate.date << " " << rate.eur << "\n";
    }
    // Użyj przeszukiwania binarnego żeby sprawdzić, w którym dniu kurs USD wynosił 3.9011PLN
    search = 3.9011;
    int found = -1;
    int searching_bound_min = 0;
    int searching_bound_max = rates.size() - 1;
    int shot;
    while (searching_bound_min != searching_bound_max && found == -1) {
        shot = (searching_bound_min + searching_bound_max) / 2;
        if ((searching_bound_min + searching_bound_max) % 2 == 1) if (sorted_by_usd[shot-1].usd == search) found = shot - 1; // if middle consists 2 numbers (set is even)
        if (sorted_by_usd[shot].usd == search) found = shot;
        else if (sorted_by_usd[shot].usd < search) searching_bound_min = shot + 1;
        else if (sorted_by_usd[shot].usd > search) searching_bound_max = shot - 1;
    }
    cout << "Kurs USD wynosił 3.9011PLN w dniu: " << sorted_by_usd[found].date << "\n";
    #pragma endregion

    // 🛠 Zadanie 9: Temperatury
    cout << "\nZadanie 9: Temperatury\n";
    #pragma region Zadanie 9
    vector<WeatherData> weather_data;
    fstream f("temp02-2020.csv", fstream::in);
    if (f.is_open()) {
        string line;
        char delimiter = ',';
        getline(f, line); // igrone header line
        while (getline(f, line)) {
            stringstream ss(line);
            
            WeatherData wd;

            string temp;
            getline(ss, wd.date, delimiter);
            getline(ss, wd.time, delimiter);
            getline(ss, temp, delimiter); // skip
            getline(ss, temp, delimiter); // skip
            getline(ss, temp, delimiter); // skip
            getline(ss, temp, delimiter);
            wd.temp = stod(temp); // converting to double
            // no need for more...

            weather_data.emplace_back(wd);
        }
    }

    cout << "Minimalna temperatura: "  << (get_temp_min(weather_data)) << " stopni Celsjusza\n";
    cout << "Maksymalna temperatura: " << (get_temp_max(weather_data)) << " stopni Celsjusza\n";

    vector<WeatherData> weather_data_sorted = sort_by_temp(weather_data);
    size_t wd_len = weather_data.size();
    double mean = 0;
    if (wd_len % 2 == 0) mean = (weather_data_sorted[wd_len / 2].temp + weather_data_sorted[wd_len / 2 - 1].temp) / 2;
    else                 mean = weather_data_sorted[wd_len / 2].temp;
    cout << "Mediana temperatur: " << mean << " stopni Celsjusza\n";
    #pragma endregion

    return 0;
}
