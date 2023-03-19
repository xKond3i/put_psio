// PSiO Poznan University Of Technology
// Laboratory 1
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2001%20-%20Proste%20algorytmy%2c%20vector.html
// Executed by Konrad Ceglarski
// 01/03/2023

// INCLUSIONS
#pragma region INCLUSIONS
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

#include <windows.h> // UTF-8 encoding for Windows
#pragma endregion

using namespace std;

// 🛠 Zadanie 1: Wypełnianie i wyświetlanie wektora
#pragma region TASK 1
void fill_progressive(vector<int>& vec);
void print_vector(vector<int>& vec);

void task_1() {
    cout << "\n--- TASK 1 ---\n";
    int ans;
    cout << "Podaj długość wektora: ";
    cin >> ans;
    const int n = ans;

    std::vector<int> vec(n);
    fill_progressive(vec);
    print_vector(vec);
    cout << "\n";
}

void fill_progressive(vector<int>& vec) {
    int len = vec.size();
    for (int i = 0; i < len; ++i) vec[i] = i + 1;
}

void print_vector(vector<int>& vec) {
    int len = vec.size();
    cout << "{";
    for (int i = 0; i < len; ++i) {
        cout << vec[i];
        if (i < len - 1) cout << ", ";
    }
    cout << "}";
}
#pragma endregion

// 🛠 Zadanie 2: Min/Max
#pragma region TASK 2
void min_max(vector<double> values, double& min, double& max);

void task_2() {
    cout << "\n\n\n--- TASK 2 ---\n";
    double min;
    double max;
    std::vector<double> values = {-1.0, 100, 3.14, -999.9, 21.37};

    min_max(values, min, max); // wpisze znalezione wartości do zmiennych min i max

    cout << "Min: " << min << "\n";
    cout << "Max: " << max << "\n";
}

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

// 🛠 Zadanie 3: Silnia
#pragma region TASK 3
uint64_t factorial(int n);

void task_3() {
    cout << "\n\n\n--- TASK 3 ---\n";
    int x = 15;
    cout << x << "! = ";

    uint64_t result = factorial(x);
    std::cout << result << std::endl; // wynik: 1307674368000
}

uint64_t factorial(int n) {
    uint64_t result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}
#pragma endregion

// 🛠 Zadanie 4: Silnia rekurencyjna
#pragma region TASK 4
uint64_t factorial_r(int n);

void task_4() {
    cout << "\n\n\n--- TASK 4 ---\n";
    int x = 15;
    cout << x << "! = ";

    uint64_t result = factorial(x);
    std::cout << result << std::endl; // wynik: 1307674368000
}

uint64_t factorial_r(int n) {
    if (n <= 1) return 1;
    return n * factorial_r(n - 1);
}
#pragma endregion

// 🛠 Zadanie 5: Liczby pierwsze
#pragma region TASK 5
bool is_prime(int x);

void task_5() {
    cout << "\n\n\n--- TASK 5 ---\n";
    int prime_or_not_prime = 13;
    if (is_prime(prime_or_not_prime)) {
        std::cout << prime_or_not_prime << " is prime!" << std::endl;
    } else {
        std::cout << prime_or_not_prime << " is not prime!" << std::endl;
    }

    int a, b;
    cout << "Podaj dolny zakres obszaru poszukiwań: "; cin >> a;
    cout << "Podaj górny zakres obszaru poszukiwań: "; cin >> b;
    if (a > b) swap(a, b);
    
    for (int num = a; num <= b; ++num) {
        if (is_prime(num)) cout << num << " ";
    }
    cout << "\n";
}

bool is_prime(int x) {
    if (x <= 1) return false;

    // Zastanów się jak można przyspieszyć przeszukiwanie zakresu - czy jakieś liczby można łatwo pominąć?
    // -> basically every even number except of 2 is not a prime.
    if (x == 2) return true;
    if (x % 2 == 0) return false;

    // 1) there won't be any integer dividers greater than half of a number,
    //    because 2 is the smallest integer divider - `(x / 2)` will be the greatest divider
    // 2) dividers come in pairs (i.e. 36 / 2 = 18, so we get pair of (2, 18)),
    //    moreover dividers greater than `sqrt(x)` will be paired with ones found before crossing `sqrt(x)`
    //    and that's why we can shrink our looking area to range of `<2; sqrt(x)>`
    int range_max = sqrt(x);

    for (int i = 3; i <= range_max; ++i) {
        if (x % i == 0) return false;
    }

    return true;
}
#pragma endregion

// 🛠 Zadanie 6: Wzór na π
#pragma region TASK 6
double pi_leibniz(double precision);

void task_6() {
    cout << "\n\n\n--- TASK 6 ---\n";
    double stop_at = 0.001;
    double pi_approx = pi_leibniz(stop_at);

    std::cout << pi_approx << std::endl;
    std::cout << "error: " << pi_approx - M_PI << std::endl;
}

double pi_leibniz(double precision) {
    double pi_approx = 1;
    double div = 1;
    double next = 1;
    int i = 1;
    while (next > precision) {
        div = i * 2 + 1;                // odd number formula
        next = 1 / div;                 // next sequence term
        pi_approx += pow(-1, i) * next; // +- another odd inverse number
        ++i;
    }
    return pi_approx * 4;
}
#pragma endregion

// 🛠 Zadanie 7: Rysowanie kwadratu
#pragma region TASK 7
void draw_square(int dim, bool left_diagonal = false, bool right_diagonal = false);

void task_7() {
    cout << "\n\n\n--- TASK 7 ---\n";
    draw_square(4);
    draw_square(6, true, false);
    draw_square(7, true, true);
}

void draw_square(int dim, bool left_diagonal, bool right_diagonal) {
    for (int x = 1; x <= dim; ++x) {
        for (int y = 1; y <= dim; ++y) {
            if      (x == 1 || x == dim)                 cout << "#"; // horizontal borders
            else if (y == 1 || y == dim)                 cout << "#"; // vertical borders
            else if (x == y && left_diagonal)            cout << "#"; // left diagonal
            else if (dim - x == y - 1 && right_diagonal) cout << "#"; // right diagonal
            else cout << " ";
        }
        cout << "\n";
    }
}
#pragma endregion

// 🛠 Zadanie 8: NWD - algorytm Euklidesa
#pragma region TASK 8
int gcd(int a, int b);

void task_8() {
    cout << "\n\n\n--- TASK 8 ---\n";
    int p = 36;
    int q = 24;
    int nwd = gcd(p, q);
    cout << "NWD(" << p << ", " << q << ") = " << nwd << "\n";
}

int gcd(int a, int b) {
    /*
    1. oblicz c jako resztę z dzielenia a przez b
    2. zastąp a liczbą b, następnie b liczbą c
    3. jeżeli wartość b wynosi 0, to a jest szukaną wartością NWD, w przeciwnym wypadku przejdź do kroku 1
    */
    int c;
    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}
#pragma endregion

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "PSiO at Poznan University Of Technology\n";
    cout << "Laboratory 1\n";
    cout << "Executed by Konrad Ceglarski\n";
    cout << "01/03/2023\n";

    task_1(); // 🛠 Zadanie 1: Wypełnianie i wyświetlanie wektora
    task_2(); // 🛠 Zadanie 2: Min/Max
    task_3(); // 🛠 Zadanie 3: Silnia
    task_4(); // 🛠 Zadanie 4: Silnia rekurencyjna
    task_5(); // 🛠 Zadanie 5: Liczby pierwsze
    task_6(); // 🛠 Zadanie 6: Wzór na π
    task_7(); // 🛠 Zadanie 7: Rysowanie kwadratu
    task_8(); // 🛠 Zadanie 8: NWD - algorytm Euklidesa

    return 0;
}
