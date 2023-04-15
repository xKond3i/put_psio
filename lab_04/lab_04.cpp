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

    int results_count = 26;
    cout << "Pierwsze " << results_count << " najczesciej wystepujacych wyrazow:\n";

    string fname = "words.txt";
    ofstream fo(fname, ios::out); // open file
    if (!fo.is_open()) return; // handle an error occured while opening the file
    // present the results and save to file
    for (auto it = data.begin(); it < data.end(); ++it) {
        const auto & [word, count] = *it;
        int pos = it - data.begin();
        if (pos < 26) cout << " " << (pos+1) << ". " << word << ": " << count << "\n";
        else if (pos == 26) cout << "and " << (data.end() - it) << " more...\n";
        fo << word << ": " << count << "\n";
    }

    cout << "Kompletna lista zapisana do pliku \"" << fname << "\"!\n";

    fo.close();
}
#pragma endregion

// Zadanie domowe 🏠🔥
#pragma region HOMEWORK
void update_book(string, map<string, vector<string>> &);

void homework() {
    cout << "\n\n\n--- HOMEWORK ---\n";
    string files[] = {"numery_telefonow_google.html", "wypozyczalnie_tel_biblioteki_google.html", "wypozyczalnie_tel_biblioteki_google2.html", "wypozyczalnie_tel_biblioteki_google3.html"};
    map<string, vector<string>> phone_book; // <hyperlink: vector of phone numbers>
    // open html files in the `resources` directory
    for (const auto & fname : files) {
        // open file
        string path = "resources\\" + fname;
        ifstream f(path, ios::in);
        cout << "Ladowanie pliku \"" << fname << "\"...\n";
        if (!f.is_open()) continue; // handle an error occured while opening the file

        // get data from file
        stringstream data_stream;
        data_stream << f.rdbuf();
        cout << "Plik wczytano poprawnie!\n";

        cout << "Znaleziono:\n";
        update_book(data_stream.str(), phone_book);
        
        f.close();
    }

    string fname = "phone_book.csv";
    ofstream fo(fname, ios::out); // open file
    if (!fo.is_open()) return; // handle an error occured while opening the file
    for (const auto & pair : phone_book) {
        auto key = pair.first;
        auto phone_numbers = pair.second;
        vector<string> unique_numbers;
        unique_copy(phone_numbers.begin(), phone_numbers.end(), back_inserter(unique_numbers));
        phone_book[key] = unique_numbers;

        // SAVE TO FILE
        fo << key;
        for (auto phone : unique_numbers) fo << "," << phone;
        fo << "\n";
    }
    fo.close();
    cout << "Kompletna lista zapisana do pliku \"" << fname << "\"!\n";
}

pair<string, string> get_anchor_tag(string search_record) {
    regex aTagHrefRE("<a[^>]*href=\"(.+?)\"[^>]*>.+?</a>");
    smatch match;
    regex_search(search_record, match, aTagHrefRE);
    return pair<string, string> (match[0], match[1]); // <whole anchor tag, just a hyperlink>
}

string href_trim(string hyperlink) {
    regex webAddressRE("(https?|ftp)://([^/\r\n]+)(/[^\r\n]*)?");
    smatch match;
    regex_match(hyperlink, match, webAddressRE);
    return match[2];
}

vector<string> get_phone_numbers(string search_record, bool normalized=true) {
    vector<string> res;
    // phone regex: mateches all three types from task 5 and 6
    // regex phoneRE("(?:\\(0\\d{2}\\)\\s?\\d{7})|(?:00\\d{11})|(?:(?:(?:\\+\\d{2}\\s?)|(?:00\\d{2}\\s?))?\\d(?:\\d[-\\s]?){7}\\d)"); // inside other words
    // regex phoneRE("(?<=\\s|^)((?:\\(0\\d{2}\\)\\s?\\d{7})|(?:00\\d{11})|(?:(?:(?:\\+\\d{2}\\s?)|(?:00\\d{2}\\s?))?\\d(?:\\d[-\\s]?){7}\\d))(?=\\s|$)"); // outside other words <- better, but lookbehind isn't supported
    regex phoneRE("(?:\\s|^)((?:\\(0\\d{2}\\)\\s?\\d{7})|(?:00\\d{11})|(?:(?:(?:\\+\\d{2}\\s?)|(?:00\\d{2}\\s?))?\\d(?:\\d[-\\s]?){7}\\d))(?=\\s|$)"); // outside other words modified
    smatch phone_match;
    string::const_iterator search_begin(search_record.cbegin());
    while (regex_search(search_begin, search_record.cend(), phone_match, phoneRE)) {
        search_begin = phone_match.suffix().first;
        string phone_number = phone_match[1]; // <- if `inside other words` regex is used then it has to be 0
        if (normalized) {
            phone_number.erase(remove(phone_number.begin(), phone_number.end(), '('), phone_number.end());
            phone_number.erase(remove(phone_number.begin(), phone_number.end(), ')'), phone_number.end());
            phone_number.erase(remove(phone_number.begin(), phone_number.end(), '-'), phone_number.end());
            phone_number.erase(remove(phone_number.begin(), phone_number.end(), ' '), phone_number.end());
        }
        res.push_back(phone_number);
    }
    return res;
}

// process data
void update_book(string data, map<string, vector<string>> & phone_book) {
    // search results are encapsulated in `<!--m-->...<!--n-->` comments
    // get result records
    regex searchRecordRE("<!--m-->.+?<!--n-->");
    smatch search_record_match;
    string::const_iterator search_begin(data.cbegin());
    while (regex_search(search_begin, data.cend(), search_record_match, searchRecordRE)) {
        search_begin = search_record_match.suffix().first;
        string search_record = search_record_match[0];

        // HYPERLINK
        auto [anchor, hyperlink] = get_anchor_tag(search_record);
        string href_trimmed = href_trim(hyperlink);
        cout << " > " << href_trimmed;

        // PHONE NUMBERS
        auto phone_numbers = get_phone_numbers(search_record);
        phone_book[href_trimmed].insert(phone_book[href_trimmed].end(), phone_numbers.begin(), phone_numbers.end()); // add new phones to the key
        for (auto it = phone_numbers.begin(); it < phone_numbers.end(); ++it) cout << (it == phone_numbers.begin() ? " (" : "") << *it << (it != phone_numbers.end()-1 ? ", " : ")");
        cout << "\n";
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
