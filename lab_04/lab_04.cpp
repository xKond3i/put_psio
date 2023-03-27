// PSiO at Poznan University Of Technology
// Laboratory 04
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2004%20-%20Pliki%2c%20wyra%C5%BCenia%20regularne.html
// Executed by Konrad Ceglarski
// 20/03/2023

// INCLUSIONS
#pragma region INCLUSIONS
#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

#include <windows.h> // UTF-8 encoding for Windows
#pragma endregion

using namespace std;

// 🛠🔥Zadanie 🛠🔥
#pragma region TASK
void task() {
    cout << "\n--- TASK 1 ---\n";
    regex exp("((PO)|(PZ))[A-Z0-9]{5}");
    string testing_cases[] = {"PO12345", "DW54321", "PZABC12", "POOOOOO", "DWBETTER"};
    for (auto str : testing_cases)
        cout << "Tablica \"" << str << "\" " << (regex_match(str, exp) ? "" : "NIE ") << "jest z Poznania.\n";
    // phone number regex: (?:(?:\+\d{2})|(?:00\d{2}))?\s?(?:\d[-\s]?){9}
}
#pragma endregion

// Zadanie końcowe 🛠🔥
#pragma region TASK FINAL
void task_final() {
    cout << "\n\n\n--- TASK FINAL ---\n";
    map<string, int> words; // pair of word and it's occurance count

    ifstream fi("resources\\license.txt", ios::in); // open file
    if (!fi.is_open()) return; // handle an error occured while opening the file

    string word;
    regex wordRE("\\w+");
    // while end of file not reached execute the task
    while (fi >> word) {
        transform(word.begin(), word.end(), word.begin(), [](auto c){return tolower(c);});
        smatch match;
        if (!regex_match(word, match, wordRE)) continue; // word not accepted, skip
        word = match[0].str();
        words[word] += 1;
    }

    fi.close();

    // copy `words` map to a `data` vector and sort the data
    vector<pair<string, int>> data(words.size());
    copy(words.begin(), words.end(), data.begin());
    sort(data.begin(), data.end(), [](const auto & a, const auto & b){return a.second > b.second;});

    ofstream fo("output.txt", ios::out); // open file
    if (!fo.is_open()) return; // handle an error occured while opening the file
    // present the results and save to file
    for (const auto & p : data) {
        const auto & [word, count] = p;
        cout << word << ": " << count << "\n";
        fo << word << ": " << count << "\n";
    }

    fo.close();
}
#pragma endregion

// Zadanie domowe 🏠🔥
#pragma region HOMEWORK
void homework() {
    cout << "\n\n\n--- HOMEWORK ---\n";
    vector<string> data;
    string files[] = {"numery_telefonow_google.html", "wypozyczalnie_tel_biblioteki_google.html", "wypozyczalnie_tel_biblioteki_google2.html", "wypozyczalnie_tel_biblioteki_google3.html"};
    // open html files in the `resources` directory
    for (const auto & fname : files) {
        // open file
        string path = "resources\\" + fname;
        ifstream f(path, ios::in);
        cout << "Loading file \"" << fname << "\"...\n";
        if (!f.is_open()) continue; // handle an error occured while opening the file

        // get data from file
        stringstream data_stream;
        data_stream << f.rdbuf();
        data.push_back(data_stream.str());
        cout << "File loaded successfully!\n";
        
        f.close();
    }
}
#pragma endregion

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "PSiO at Poznan University Of Technology\n";
    cout << "Laboratory 04\n";
    cout << "Executed by Konrad Ceglarski\n";
    cout << "20/03/2023\n";

    task_final(); // Zadanie końcowe 🛠🔥
    
    homework(); // Zadanie domowe 🏠🔥

    return 0;
}
