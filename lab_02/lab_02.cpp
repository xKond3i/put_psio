// PSiO Poznan University Of Technology
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2002%20-%20Algorytmy.html
// Executed by Konrad Ceglarski
// 12/03/2023

#include <iostream>
#include <string>
// #include <algorithm>
// #include <cctype>
#include <vector>
#include <time.h>

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

// 🛠 Zadanie 1: palindrom
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

// 🛠 Zadanie 2: znalezienie wszystkich wystąpień znaku
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

// 🛠 Zadanie 3: szukanie najdłuższego wyrazu
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

// 🛠 Zadanie 4: podział napisów
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

// 🛠 Zadanie 5: znajdź i zamień
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

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 🛠 Zadanie 1: palindrom
    cout << "Zadanie 1: palindrom\n";
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

    // 🛠 Zadanie 2: znalezienie wszystkich wystąpień znaku
    cout << "\nZadanie 2: znalezienie wszystkich wystąpień znaku\n";
    #pragma region Zadanie 2
    std::string input = "Ala ma kota";

    std::vector<size_t> pos = find_all(input, 'a'); // wynik: {2, 5, 10}
    cout << pos;
    #pragma endregion

    // 🛠 Zadanie 3: szukanie najdłuższego wyrazu
    cout << "\nZadanie 3: szukanie najdłuższego wyrazu\n";
    #pragma region Zadanie 3
    input = "Ala ma kota kot jezdzi na Roombie";

    std::string longest = find_longest_word(input); // "Roombie"
    cout << longest << "\n";
    #pragma endregion

    // 🛠 Zadanie 4: podział napisów
    cout << "\nZadanie 4: podział napisów\n";
    #pragma region Zadanie 4
    sentence = "Ala ma kota";
    std::vector<std::string> words = split(sentence); // wynik: {"Ala", "ma", "kota"}

    std::string csv = "Mount Everest,8848,1953";
    std::vector<std::string> data = split(csv, ','); // wynik: {"Mount Everest", "8848", "1953"}

    cout << words << data;
    #pragma endregion

    // 🛠 Zadanie 5: znajdź i zamień
    cout << "\nZadanie 5: znajdź i zamień\n";
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

    return 0;
}
