// PSiO at Poznan University Of Technology
// Laboratory 06
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2006%20-%20Klasy%20-%20rozszerzenie.html
// Executed by Konrad Ceglarski
// 04/04/2023

// INCLUSIONS
#pragma region INCLUSIONS
#include <iostream>
#include <vector>
#include <random>
#include <time.h>

#include "histogram.h"
#include "complex.h"
#include "cstm_impl_vec.h"
#include "matrix.h"

#include <windows.h> // UTF-8 encoding for Windows
#pragma endregion

using namespace std;

#pragma region TASK 1
void task_1() {
    cout << "\n--- TASK 1 ---\n";
    
    Histogram<int> histogram_int;
    Histogram<float> histogram_float;
    Histogram<std::string> histogram_of_names;

    std::cout << "Adding records to created `Histogram` objects...\n";
    histogram_int.emplace(5);
    histogram_float.emplace(12.3f);

    histogram_of_names.emplace("John");
    histogram_of_names.emplace("John");
    histogram_of_names.emplace("John");
    histogram_of_names.emplace("Maria");
    histogram_of_names.emplace("Maria");
    histogram_of_names << "Konrad";

    std::string fname = "histogram.txt";
    std::cout << "\nSaving to \"" << fname << "\" file...\n";
    std::ofstream file(fname);
    file << histogram_of_names; // zapis histogramu do pliku (identycznie jak dla wyświetlenia go na konsoli)
    file.close();

    std::cout << "\nForwarding to `std::cout`...\n";
    std::cout << histogram_of_names;
    std::cout << "\nPrinting...\n";
    histogram_of_names.print();

    auto leastFrequent = histogram_of_names.min();
    cout << "Least Frequent: " << leastFrequent.first << " (" << leastFrequent.second << " times)\n";
    
    auto mostFrequent = histogram_of_names.max();
    cout << "Most Frequent: " << mostFrequent.first << " (" << mostFrequent.second << " times)\n";

    auto range = histogram_of_names.range();
    cout << "Range: <" << range.first << "; " << range.second << ">\n";

    cout << "\nFile \"wyniki.csv\" contents:\n";
    Histogram<string> wyniki_csv;
    wyniki_csv.from_csv("resources\\wyniki.csv");
    wyniki_csv.print();

    cout << "\nFile \"license.txt\" contents:\n";
    Histogram<string> license;
    license.from_csv("resources\\license.txt", ' ', 0);
    license.print(10);
}
#pragma endregion

#pragma region TASK 2
void task_2() {
    cout << "\n\n\n--- TASK 2 ---\n";
    
    ComplexNumber<int> contructorless;
    ComplexNumber<float> a(2, 1);
    ComplexNumber<float> b(1, 2);

    cout << "contructorless = " << contructorless << "\n";
    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n\n";
    cout << "a + 1 = " << (a + 1) << "\n";
    cout << "a + b = " << (a + b) << "\n";
    cout << "a - 1 = " << (a - 1) << "\n";
    cout << "a - b = " << (a - b) << "\n\n";
    cout << "a * 2 = " << (a * 2) << "\n";
    cout << "a * b = " << (a * b) << "\n";
    cout << "a / 2 = " << (a / 2) << "\n";
    cout << "a / b = " << (a / b) << "\n";
}
#pragma endregion

#pragma region TASK 3
void task_3() {
    cout << "\n\n\n--- TASK 3 ---\n";
    
    vector<int> numbers_a = {1, 2, 3};
    vector<ComplexNumber<int>> numbers_b = {ComplexNumber<int>(2, 1), ComplexNumber<int>(1, 2)};

    CIVector<int> vec_a(numbers_a);
    CIVector<ComplexNumber<int>> vec_b(numbers_b);
    ComplexNumber<int> c(1, 1);

    cout << "vec_a = " << vec_a << "\n";
    cout << "vec_b = " << vec_b << "\n";
    cout << "c = " << c << "\n\n";
    cout << "vec_a + 2 = " << (vec_a + 2) << "\n";
    cout << "vec_b + 2 = " << (vec_b + 2) << "\n";
    cout << "vec_b + c = " << (vec_b + c) << "\n\n";
    cout << "vec_a - 2 = " << (vec_a - 2) << "\n";
    cout << "vec_b - 2 = " << (vec_b - 2) << "\n";
    cout << "vec_b - c = " << (vec_b - c) << "\n\n";
    cout << "vec_a * 2 = " << (vec_a * 2) << "\n";
    cout << "vec_b * 2 = " << (vec_b * 2) << "\n";
    cout << "vec_b * c = " << (vec_b * c) << "\n";
}
#pragma endregion

#pragma region TASK 4
void task_4() {
    cout << "\n\n\n--- TASK 4 ---\n";

    Matrix<double> M_a(3, 3);
    Matrix<double> M_b({{1, 0, 0},
                        {0, 1, 0},
                        {0, 0, 1}});
    Matrix<double> M_c;

    cout << "matrix M_a:\n" << M_a << "\n";
    cout << "matrix M_b:\n" << M_b << "\n";

    Matrix<int> M_x = Matrix<int>::eye(3, 3); // metoda statyczna, zwraca macierz jednostkową
    std::cout << "matrix::eye(3, 3):\n" << M_x << "\n";

    static std::default_random_engine e(time(0));
    std::uniform_int_distribution<int> distribution(10, 99);
    Matrix<int> M_y = Matrix<int>::fill(3, 3, [&distribution](){ return distribution(e); }); // metoda statyczna, zwraca macierz o wymiarze 3x3, wypełnioną wartościami generowanymi przez funkcję będącą trzecim argumentem
    std::cout << "matrix::fill(3, 3, func):\n" << M_y << "\n";

    cin >> M_c; // pobiera dane od użytkownika (zarówno jej wymiar jak i wartości poszczególnych elementów)

    cout << "\ncreated matrix:\n" << M_c << "\n";

    Matrix<double> M_z = 5 * M_a * M_c * 5 + 1; // operacje arytmetyczne na macierzach - zdefiniuj wszystkie niezbędne operatory
    cout << "matrix M_z = 5 * M_a * M_c * 5 + 1:\n" << M_z;
}
#pragma endregion

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "PSiO at Poznan University Of Technology\n";
    cout << "Laboratory 06\n";
    cout << "Executed by Konrad Ceglarski\n";
    cout << "04/04/2023\n";

    task_1();
    task_2();
    task_3();
    task_4();

    return 0;
}
