// PSiO at Poznan University Of Technology
// Laboratory Template
// Source: None
// Executed by Konrad Ceglarski
// 14/03/2023

#include <iostream>

#include <windows.h> // UTF-8 encoding for Windows

using namespace std;

#pragma region TASK 1
void task_1() {
    cout << "\n\n\n--- TASK 1 ---\n";
    
}
#pragma endregion

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "PSiO at Poznan University Of Technology\n";
    cout << "Laboratory Template\n";
    cout << "Executed by Konrad Ceglarski\n";
    cout << "14/03/2023\n";

    task_1();

    return 0;
}