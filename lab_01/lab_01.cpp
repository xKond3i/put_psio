// PSiO Poznan University Of Technology
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2001%20-%20Proste%20algorytmy%2c%20vector.html
// Executed by Konrad Ceglarski
// 01/03/2023

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

#include <windows.h> // UTF-8 encoding for Windows

using namespace std;

int ask_for_number(string q) {
    string ans;
    int ans_int = 0;
    bool flag = true;
    do {
        cout << q;
        cin >> ans;
        try {
            ans_int = stoi(ans);
            flag = false;
        } catch(...) {
            // Example doesn't need specific error handling
        }
    } while (flag);
    return ans_int;
}

// 🛠 Zadanie 1: wypełnianie i wyświetlanie wektora
#pragma region Zadanie 1
void fill_progressive(vector<int>& vec) {
    int len = vec.size();
    for (int i = 0; i < len; ++i) vec[i] = i + 1;
}

void print_vector(vector<int>& vec) {
    int len = vec.size();
    for (int i = 0; i < len; ++i) {
        cout << vec[i];
        if (i < len - 1) cout << ", ";
    }
    cout << "\n";
}
#pragma endregion

// 🛠 Zadanie 2: min/max
#pragma region Zadanie 2
void min_max(vector<double> values, double& min, double& max) {
    double temp_min = numeric_limits<double>::infinity();
    double temp_max = numeric_limits<double>::infinity() * (-1);
    for (const double val : values) {
        if (val < temp_min) temp_min = val;
        if (val > temp_max) temp_max = val;
    }
    min = temp_min;
    max = temp_max;
}
#pragma endregion

// 🛠 Zadanie 3: silnia
#pragma region Zadanie 3
uint64_t factorial(int n) {
    uint64_t result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}
#pragma endregion

// 🛠 Zadanie 4: silnia rekurencyjna
#pragma region Zadanie 4
uint64_t factorial_r(int n) {
    if (n <= 1) return 1;
    return n * factorial_r(n - 1);
}
#pragma endregion

// 🛠 Zadanie 5: liczby pierwsze
#pragma region Zadanie 5
bool is_prime(int x) {
    if (x <= 1) return false;
    int range_max = x / 2 + 1; // the other half of dividers will be mirrored i.e. 36 / 2 = 18 and 32 / 18 = 2
    for (int i = 2; i < range_max; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}
#pragma endregion

// 🛠 Zadanie 6: wzór na π
#pragma region Zadanie 6
double pi_leibniz(double precision) {
    double pi_approx = 1;
    double div = 3;
    double next = 1;
    int it = 0;
    while (next > precision) {
        next = (1 / div);
        if (it % 2 == 0) pi_approx -= next;
        else pi_approx += next;
        div += 2;
        ++it;
    }
    return pi_approx * 4;
}
#pragma endregion

// 🛠 Zadanie 7: rysowanie kwadratu
#pragma region Zadanie 7
//// TBC
#pragma endregion

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 🛠 Zadanie 1: wypełnianie i wyświetlanie wektora
    cout << "Zadanie 1: wypełnianie i wyświetlanie wektora\n";
    #pragma region Zadanie 1
    string ans;
    int ans_int = 0;
    bool flag = true;
    do {
        cout << "Podaj liczbę od 1 do 10: ";
        cin >> ans;
        try {
            ans_int = stoi(ans);
            if (ans_int < 1 || ans_int > 10) throw "out of range";
            flag = false;
        } catch(...) {
            // Example doesn't need specific error handling
        }
    } while (flag);
    const int n = ans_int;

    std::vector<int> vec(n);
    fill_progressive(vec);
    print_vector(vec);
    #pragma endregion

    // 🛠 Zadanie 2: min/max
    cout << "\nZadanie 2: min/max\n";
    #pragma region Zadanie 2
    double min;
    double max;
    std::vector<double> values = {-1.0, 100, 3.14, -999.9, 21.37};

    min_max(values, min, max); // wpisze znalezione wartości do zmiennych min i max

    cout << "Min: " << min << "\n";
    cout << "Max: " << max << "\n";
    #pragma endregion

    // 🛠 Zadanie 3: silnia
    cout << "\nZadanie 3: silnia\n";
    #pragma region Zadanie 3
    int x = 15;
    cout << x << "! = ";

    uint64_t result = factorial(x);
    std::cout << result << std::endl; // wynik: 1307674368000
    #pragma endregion

    // 🛠 Zadanie 4: silnia rekurencyjna
    cout << "\nZadanie 4: silnia rekurencyjna\n";
    #pragma region Zadanie 4
    x = 15;
    cout << x << "! = ";

    result = factorial(x);
    std::cout << result << std::endl; // wynik: 1307674368000
    #pragma endregion

    // 🛠 Zadanie 5: liczby pierwsze
    cout << "\nZadanie 5: liczby pierwsze\n";
    #pragma region Zadanie 5
    int prime_or_not_prime = 13;
    if (is_prime(prime_or_not_prime)) {
        std::cout << prime_or_not_prime << " is prime!" << std::endl;
    } else {
        std::cout << prime_or_not_prime << " is not prime!" << std::endl;
    }

    int a = ask_for_number("Podaj dolny zakres obszaru poszukiwań: ");
    int b = ask_for_number("Podaj górny zakres obszaru poszukiwań: ");
    if (a > b) swap(a, b);
    
    for (int num = a; num <= b; ++num) {
        if (is_prime(num)) cout << num << " ";
    }
    cout << "\n";
    #pragma endregion

    // 🛠 Zadanie 6: wzór na π
    cout << "\nZadanie 6: wzór na π\n";
    #pragma region Zadanie 6
    double stop_at = 0.001;
    double pi_approx = pi_leibniz(stop_at);

    std::cout << pi_approx << std::endl;
    std::cout << "error: " << pi_approx - M_PI << std::endl;
    #pragma endregion

    // 🛠 Zadanie 7: rysowanie kwadratu
    cout << "\nZadanie 7: rysowanie kwadratu\n";
    #pragma region Zadanie 7
    //// TBC
    #pragma endregion

    return 0;
}
