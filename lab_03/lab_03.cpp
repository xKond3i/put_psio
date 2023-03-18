// PSiO at Poznan University Of Technology
// Laboratory 3
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2003%20-%20Zaawansowane%20kolekcje%2c%20algorithm.html
// Executed by Konrad Ceglarski
// 18/03/2023

// INCLUSIONS
#pragma region INCLUSIONS
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <list>

#include <windows.h> // UTF-8 encoding for Windows
#pragma endregion

using namespace std;

// GLOBALS
#pragma region GLOBALS
int randomInt(int min, int max) {
    static std::default_random_engine e{static_cast<long unsigned int>(time(0))};
    std::uniform_int_distribution<int> d{min, max};
    return d(e);
}
#pragma endregion

// 🛠 Zadanie 1
#pragma region TASK 1
void task_1() {
    cout << "\n\n\n--- TASK 1 ---\n";
    vector<int> vec;
    int n = 10;

    // wylosuj n liczb całkowitych z przedziału <-20; 20> i umieść je w tablicy,
    for (int i = 0; i < n; ++i)
        vec.push_back(randomInt(-20, 20));
    // vec = {10, 1, 2, 3, 10, 4, 5, 10, 10, 6, 7, 10}; // edge case with multiple values

    // z wykorzystaniem zwykłego operator indeksowania wyświetl cała zawartość tablicy na konsoli,
    cout << "{";
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << (i != vec.size() - 1 ? ", " : "");
    cout << "}\n";

    // z wykorzystaniem iteratorów wyświetl cała zawartość tablicy na konsoli,
    cout << "{";
    for (auto it = vec.begin(); it != vec.end(); ++it)
        cout << *it << (it != (vec.end() - 1) ? ", " : "");
    cout << "}\n";

    // z wykorzystaniem iteratorów wyszukaj w tablicy wartości wskazanej przez użytkownika, a następnie ją usuń.
    cout << "Podaj wartosc, ktora mam usunac: ";
    int user_input;
    cin >> user_input;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it == user_input) {
            vec.erase(it);
            --it; // vector is being modified by vec.erase, so the iterator changes
        }
    }

    cout << "{";
    for (auto it = vec.begin(); it != vec.end(); ++it)
        cout << *it << (it != (vec.end() - 1) ? ", " : "");
    cout << "}\n";

    cout << "\n";
}
#pragma endregion

// 🛠 Zadanie 2
#pragma region TASK 2
void task_2() {
    cout << "\n\n\n--- TASK 2 ---\n";
    list<int> l;
    int n = 10;

    // wylosuj n liczb całkowitych z przedziału <-20; 20> i umieść je w tablicy,
    for (int i = 0; i < n; ++i)
        l.push_back(randomInt(-20, 20));
    // vec = {10, 1, 2, 3, 10, 4, 5, 10, 10, 6, 7, 10}; // edge case with multiple values

    // z wykorzystaniem iteratorów wyświetl cała zawartość tablicy na konsoli,
    cout << "[";
    for (auto it = l.begin(); it != l.end(); ++it)
        cout << *it << (next(it) != l.end() ? ", " : "");
    cout << "]\n";

    // z wykorzystaniem iteratorów wyszukaj w tablicy wartości wskazanej przez użytkownika, a następnie ją usuń.
    cout << "Podaj wartosc, ktora mam usunac: ";
    int user_input;
    cin >> user_input;
    for (auto it = l.begin(); it != l.end(); ++it) {
        if (*it == user_input) {
            it = l.erase(it);
            ++it; // list is being modified by l.remove, so the iterator changes
        }
    }

    cout << "[";
    for (auto it = l.begin(); it != l.end(); ++it)
        cout << *it << (next(it) != l.end() ? ", " : "");
    cout << "]\n";

    cout << "\n";
}
#pragma endregion

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "PSiO at Poznan University Of Technology\n";
    cout << "Laboratory 3\n";
    cout << "Executed by Konrad Ceglarski\n";
    cout << "18/03/2023\n";

    task_1(); // 🛠 Zadanie 1
    task_2(); // 🛠 Zadanie 2

    return 0;
}
