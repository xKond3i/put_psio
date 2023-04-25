// PSiO at Poznan University Of Technology
// Laboratory 06
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2006%20-%20Klasy%20-%20rozszerzenie.html
// Executed by Konrad Ceglarski
// 04/04/2023

// INCLUSIONS
#pragma region INCLUSIONS
#include <iostream>

#include "histogram.h"
#include "complex.h"

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
    
    ComplexNumber<int> plain;
    ComplexNumber<float> a(2, 1);
    ComplexNumber<float> b(1, 2);

    cout << "plain = " << plain << "\n";
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

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "PSiO at Poznan University Of Technology\n";
    cout << "Laboratory 06\n";
    cout << "Executed by Konrad Ceglarski\n";
    cout << "04/04/2023\n";

    task_1();
    task_2();

    return 0;
}
