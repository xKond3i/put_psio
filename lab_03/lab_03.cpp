// PSiO at Poznan University Of Technology
// Laboratory 03
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
#include <algorithm>
#include <fstream>
#include <sstream>

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

// ######### COMMON VECTOR AND LIST ######### //
int n = 10;
vector<int> vec;
list<int> l;

// ######### COMMON BASKET ######### //
enum class TypRosliny { Owoc, Warzywo };

struct Roslina {
    TypRosliny typ;
    std::string nazwa;
};

using Koszyk = std::vector<Roslina>;

Koszyk koszyk;

void globals() {
    for (int i = 0; i < n; ++i) ::vec.push_back(randomInt(-20, 20));
    // ::vec = {10, 1, 2, 3, 10, 4, 5, 10, 10, 6, 7, 10}; // edge case with multiple values
    for (int i = 0; i < n; ++i) ::l.push_back(randomInt(-20, 20));
    // ::l = {10, 1, 2, 3, 10, 4, 5, 10, 10, 6, 7, 10}; // edge case with multiple values
}

// operator `<<` overload for ostream and vector -> helps dispalying vector in terminal
template <typename T>
ostream& operator << (ostream& os, vector<T> vec) {
    os << "{";
    for (int i = 0; i < vec.size(); ++i) os << vec[i] << (i != vec.size() - 1 ? ", " : "");
    os << "}";
    return os;
}

// operator `<<` overload for ostream and list -> helps dispalying list in terminal
template <typename T>
ostream& operator << (ostream& os, list<T> l) {
    cout << "[";
    for (auto it = l.begin(); it != l.end(); ++it) cout << *it << (next(it) != l.end() ? ", " : "");
    cout << "]";
    return os;
}
#pragma endregion

// 🛠 Zadanie 1
#pragma region TASK 1
void task_1() {
    cout << "\n--- TASK 1 ---\n";
    // wylosuj n liczb całkowitych z przedziału <-20; 20> i umieść je w tablicy,
    // -> IN MAIN/GLOBALS
    vector<int> vec = ::vec; // copy of global vector

    // z wykorzystaniem zwykłego operator indeksowania wyświetl cała zawartość tablicy na konsoli,
    cout << "Wektor: " << "{";
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << (i != vec.size() - 1 ? ", " : "");
    cout << "}\n";

    // z wykorzystaniem iteratorów wyświetl cała zawartość tablicy na konsoli,
    cout << "Wektor: " << "{";
    for (auto it = vec.begin(); it != vec.end(); ++it)
        cout << *it << (next(it) != vec.end() ? ", " : "");
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

    cout << "Wektor: " << vec << "\n";
}
#pragma endregion

// 🛠 Zadanie 2
#pragma region TASK 2
void task_2() {
    cout << "\n\n\n--- TASK 2 ---\n";
    // wylosuj n liczb całkowitych z przedziału <-20; 20> i umieść je w tablicy,
    // -> IN MAIN/GLOBALS
    list<int> l = ::l;// copy of global list

    // z wykorzystaniem iteratorów wyświetl cała zawartość tablicy na konsoli,
    cout << "Lista: " << "[";
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
            ++it; // list is being modified by l.erase, so the iterator changes
        }
    }

    cout << "Lista: " << l << "\n";
}
#pragma endregion

// 🛠 Zadanie 3
#pragma region TASK 3
void task_3() {
    cout << "\n\n\n--- TASK 3 ---\n";
    // ######### VECTOR ######### //
    vector<int> vec = ::vec; // copy of global vector
    cout << "Wektor: " << vec << "\n";

    cout << "Podaj wartosc, ktora mam usunac: ";
    int user_input;
    cin >> user_input;
    vector<int>::iterator found = find(vec.begin(), vec.end(), user_input);
    while (found != vec.end()) {
        vec.erase(found);
        found = find(found, vec.end(), user_input);
    }

    cout << "Wektor: " << vec << "\n";

    // ######### LIST ######### //
    list<int> l = ::l; // copy of global list
    cout << "\nLista: " << l << "\n";

    cout << "Podaj wartosc, ktora mam usunac: ";
    cin >> user_input;
    list<int>::iterator l_found = find(l.begin(), l.end(), user_input);
    while (l_found != l.end()) {
        l_found = l.erase(l_found);
        l_found = find(l_found, l.end(), user_input);
    }

    cout << "Lista: " << l << "\n";
}
#pragma endregion

// 🛠 Zadanie 4
#pragma region TASK 4
void task_4() {
    cout << "\n\n\n--- TASK 4 ---\n";
    // ######### VECTOR ######### //
    vector<int> vec = ::vec; // copy of global vector
    cout << "Wektor: " << vec << "\n";
    cout << "Wektor min (min_element): " << *min_element(vec.begin(), vec.end()) << "\n";
    cout << "Wektor max (max_element): " << *max_element(vec.begin(), vec.end()) << "\n";
    const auto [v_min, v_max] = minmax_element(vec.begin(), vec.end());
    cout << "Wektor min (minmax_element.first): " << *v_min << "\n";
    cout << "Wektor max (minmax_element.second): " << *v_max << "\n";

    // ######### LIST ######### //
    list<int> l = ::l; // copy of global list
    cout << "\nLista: " << l << "\n";
    cout << "Lista min (min_element): " << *min_element(l.begin(), l.end()) << "\n";
    cout << "Lista max (max_element): " << *max_element(l.begin(), l.end()) << "\n";
    const auto [l_min, l_max] = minmax_element(l.begin(), l.end());
    cout << "Lista min (minmax_element.first): " << *l_min << "\n";
    cout << "Lista max (minmax_element.second): " << *l_max << "\n";
}
#pragma endregion

// 🛠 Zadanie 5
#pragma region TASK 5
void task_5() {
    cout << "\n\n\n--- TASK 5 ---\n";
    // ######### VECTOR ######### //
    vector<int> vec = ::vec; // copy of global vector
    cout << "Wektor: " << vec << "\n";
    sort(vec.begin(), vec.end(), [](auto a, auto b){return a > b;});
    cout << "Wektor posortowany malejąco: " << vec << "\n";
    sort(vec.begin(), vec.end(), [](auto a, auto b){return a < b;});
    cout << "Wektor posortowany rosnąco: " << vec << "\n";
    sort(vec.begin(), vec.end(), [](auto a, auto b){return abs(a) > abs(b);});
    cout << "Wektor posortowany malejąco względem wartości bezwzględnych: " << vec << "\n";

    // ######### LIST ######### //
    list<int> l = ::l; // copy of global list
    cout << "\nLista: " << l << "\n";
    l.sort([](auto a, auto b){return a > b;});
    cout << "Lista posortowana malejąco: " << l << "\n";
    l.sort([](auto a, auto b){return a < b;});
    cout << "Lista posortowana rosnąco: " << l << "\n";
    l.sort([](auto a, auto b){return abs(a) > abs(b);});
    cout << "Lista posortowana malejąco względem wartości bezwzględnych: " << l << "\n";
}
#pragma endregion

// 🛠 Zadanie 6
#pragma region TASK 6
void task_6() {
    cout << "\n\n\n--- TASK 6 ---\n";
    // ######### VECTOR ######### //
    vector<int> vec = ::vec; // copy of global vector
    cout << "Wektor: " << vec << "\n";
    vector<int> v_unique;
    sort(vec.begin(), vec.end(), [](auto a, auto b){return a < b;});
    for (const auto v : vec) {
        if (find(v_unique.begin(), v_unique.end(), v) != v_unique.end()) continue;
        v_unique.push_back(v);
        cout << "Liczba: " << v << " - Ilość: " << count(vec.begin(), vec.end(), v) << "\n";
    }

    // ######### LIST ######### //
    list<int> l = ::l; // copy of global list
    cout << "\nLista: " << l << "\n";
    list<int> l_unique;
    l.sort([](auto a, auto b){return a < b;});
    for (const auto v : l) {
        if (find(l_unique.begin(), l_unique.end(), v) != l_unique.end()) continue;
        l_unique.push_back(v);
        cout << "Liczba: " << v << " - Ilośc: " << count(l.begin(), l.end(), v) << "\n";
    }
}
#pragma endregion

// 🛠 Zadanie 7
#pragma region TASK 7
// Koszyk & TypRosliny in GLOBALS
void task_7() {
    cout << "\n\n\n--- TASK 7 ---\n";
    Roslina truskawka = {.typ=TypRosliny::Owoc, .nazwa="Truskawka"};
    Roslina borowka = {.typ=TypRosliny::Owoc, .nazwa="Borówka"};
    Roslina zieminak = {.typ=TypRosliny::Warzywo, .nazwa="Zieminak"};
    ::koszyk.push_back(truskawka); cout << "+ Dodano truskawkę\n";
    ::koszyk.emplace_back(zieminak); cout << "+ Dodano zieminaka\n";
    ::koszyk.insert(koszyk.begin(), borowka); cout << "+ Dodano borówkę\n";
}
#pragma endregion

// 🛠 Zadanie 8
#pragma region TASK 8
string getPlantTypeString(TypRosliny type) {
    switch (type) {
        case TypRosliny::Owoc:
            return "Owoc";
        case TypRosliny::Warzywo:
            return "Warzywo";
        default:
            return "?";
    }
}

std::ostream& operator<<(std::ostream &out, const Roslina &roslina) {
    out << roslina.nazwa << " (" << getPlantTypeString(roslina.typ) << ")";
    return out;
}
std::ostream& operator<<(std::ostream &out, const Koszyk &koszyk) {
    out << "{";
    for (int i = 0; i < koszyk.size(); ++i) out << koszyk[i] << (i != koszyk.size() - 1 ? ", " : "");
    out << "}";
    return out;
}

void task_8() {
    cout << "\n\n\n--- TASK 8 ---\n";
    cout << "Koszyk: " << ::koszyk << "\n";
}
#pragma endregion

// 🛠 Zadanie 9
#pragma region TASK 9
bool czy_jest_gruszka(const Koszyk &koszyk)  {
    return find_if(koszyk.begin(), koszyk.end(), [](const auto& roslina){return roslina.nazwa == "Gruszka";}) != koszyk.end();
}

void task_9() {
    cout << "\n\n\n--- TASK 9 ---\n";
    cout << "Koszyk: " << ::koszyk << "\n";
    cout << "Gruszki w koszyku? " << (czy_jest_gruszka(::koszyk) ? "TAK" : "NIE") << "\n";
    Roslina gruszka = {.typ=TypRosliny::Owoc , .nazwa="Gruszka"};
    ::koszyk.push_back(gruszka); cout << "+ Dodano gruszkę\n";
    cout << "Gruszki w koszyku? " << (czy_jest_gruszka(::koszyk) ? "TAK" : "NIE") << "\n";
}
#pragma endregion

// 🛠 Zadanie 10
#pragma region TASK 10
bool czy_same_owoce(const Koszyk &koszyk) {
    return !koszyk.empty() && std::all_of(koszyk.begin(), koszyk.end(),
        [](const Roslina &roslina){ return roslina.typ == TypRosliny::Owoc; }
    );
}
bool czy_same_warzywa(const Koszyk &koszyk) {
    return !koszyk.empty() && std::all_of(koszyk.begin(), koszyk.end(),
        [](const Roslina &roslina){ return roslina.typ == TypRosliny::Warzywo; }
    );
}
bool czy_conajmniej_owoc(const Koszyk &koszyk) {
    return !koszyk.empty() && std::any_of(koszyk.begin(), koszyk.end(),
        [](const Roslina &roslina){ return roslina.typ == TypRosliny::Owoc; }
    );
}
bool czy_conajmniej_warzywo(const Koszyk &koszyk) {
    return !koszyk.empty() && std::any_of(koszyk.begin(), koszyk.end(),
        [](const Roslina &roslina){ return roslina.typ == TypRosliny::Warzywo; }
    );
}
bool czy_brak_owocow(const Koszyk &koszyk) {
    return koszyk.empty() || std::none_of(koszyk.begin(), koszyk.end(),
        [](const Roslina &roslina){ return roslina.typ == TypRosliny::Owoc; }
    );
}
bool czy_brak_warzyw(const Koszyk &koszyk) {
    return koszyk.empty() || std::none_of(koszyk.begin(), koszyk.end(),
        [](const Roslina &roslina){ return roslina.typ == TypRosliny::Warzywo; }
    );
}

void task_10() {
    cout << "\n\n\n--- TASK 10 ---\n";
    Koszyk koszyk = ::koszyk; // global copy
    cout << "Koszyk: " << koszyk << "\n";
    cout << "Czy same owoce? " << (czy_same_owoce(koszyk) ? "TAK" : "NIE") << "\n";
    cout << "Czy same warzywa? " << (czy_same_warzywa(koszyk) ? "TAK" : "NIE") << "\n";
    cout << "Czy conajmniej jeden owoc? " << (czy_conajmniej_owoc(koszyk) ? "TAK" : "NIE") << "\n";
    cout << "Czy conajmniej jedeno warzywo? " << (czy_conajmniej_warzywo(koszyk) ? "TAK" : "NIE") << "\n";
    cout << "Czy brak owoców? " << (czy_brak_owocow(koszyk) ? "TAK" : "NIE") << "\n";
    cout << "Czy brak warzyw? " << (czy_brak_warzyw(koszyk) ? "TAK" : "NIE") << "\n";
}
#pragma endregion

// 🛠 Zadanie 11
#pragma region TASK 11
int zlicz_rosliny_na_litere_m(const Koszyk &koszyk) {
    return std::count_if(koszyk.begin(), koszyk.end(),
        [](const Roslina &roslina) { return roslina.nazwa[0] == 'M'
                                         || roslina.nazwa[0] == 'm'; }
    );
}

int zlicz_owoce(const Koszyk &koszyk) {
    return count_if(koszyk.begin(), koszyk.end(), [](const Roslina &roslina){return roslina.typ == TypRosliny::Owoc;});
}

int zlicz_warzywa(const Koszyk &koszyk) {
    return count_if(koszyk.begin(), koszyk.end(), [](const Roslina &roslina){return roslina.typ == TypRosliny::Warzywo;});
}

void task_11() {
    cout << "\n\n\n--- TASK 11 ---\n";
    Koszyk koszyk = ::koszyk; // global copy
    cout << "Koszyk: " << koszyk << "\n";
    cout << "Ilość owoców: " << zlicz_owoce(koszyk) << "\n";
    cout << "Ilość warzyw: " << zlicz_warzywa(koszyk) << "\n";
}
#pragma endregion

// 🛠 Zadanie 12
#pragma region TASK 12
void usun_zaczynajace_sie_od(char letter, Koszyk &koszyk) {
    const auto it = remove_if(koszyk.begin(), koszyk.end(),
                              [letter](const auto& roslina)
                              {return roslina.nazwa[0] == toupper(letter) || roslina.nazwa[0] == tolower(letter);});
    koszyk.erase(it, koszyk.end());
}

void task_12() {
    cout << "\n\n\n--- TASK 12 ---\n";
    Koszyk koszyk = ::koszyk; // global copy
    koszyk.push_back((Roslina){.typ=TypRosliny::Owoc, .nazwa="Brzoskwinia"}); cout << "+ Dodano brzoskwinię\n";
    koszyk.push_back((Roslina){.typ=TypRosliny::Warzywo, .nazwa="Brokuł"}); cout << "+ Dodano brokuła\n";
    cout << "Koszyk: " << koszyk << "\n";
    usun_zaczynajace_sie_od('B', koszyk);
    cout << "- Usunieto owoce i warzywa na litere \"B\"\n";
    cout << "Koszyk: " << koszyk << "\n";
}
#pragma endregion

// 🛠 Zadanie 13
#pragma region TASK 13
bool operator<(const Roslina &r1, const Roslina &r2) { return r1.typ < r2.typ || r1.nazwa < r2.nazwa; } // sort by type first, if the same - then by name
bool operator>(const Roslina &r1, const Roslina &r2) { return r1.typ > r2.typ || r1.nazwa > r2.nazwa; } // sort by type first, if the same - then by name

void task_13() {
    cout << "\n\n\n--- TASK 13 ---\n";
    cout << "+ Dodano operatory porównawnania dla `Roslina`\n";
}
#pragma endregion

// 🛠 Zadanie 14
#pragma region TASK 14
void task_14() {
    cout << "\n\n\n--- TASK 14 ---\n";
    Koszyk koszyk_Malgosi = ::koszyk;
    Koszyk koszyk_Marty = {(Roslina){TypRosliny::Owoc, "Jagoda"}, (Roslina){TypRosliny::Warzywo, "Zieminak"}, (Roslina){TypRosliny::Owoc, "Truskawka"}};
    sort(koszyk_Malgosi.begin(), koszyk_Malgosi.end(), [](const auto & r1, const auto & r2){return r1 < r2;});
    sort(koszyk_Marty.begin(), koszyk_Marty.end(), [](const auto & r1, const auto & r2){return r1 < r2;});
    cout << "Koszyk Małgosi: " << koszyk_Malgosi << "\n";
    cout << "Koszyk Marty: " << koszyk_Marty << "\n";

    Koszyk koszyk_wspolne;
    std::set_intersection(koszyk_Malgosi.begin(), koszyk_Malgosi.end(),
                          koszyk_Marty.begin(), koszyk_Marty.end(),
                          std::back_inserter(koszyk_wspolne));
    Koszyk koszyk_roznic;
    // first everything that's present in `koszyk Malgosi`, but not in the `koszyk Marty`
    std::set_difference(koszyk_Malgosi.begin(), koszyk_Malgosi.end(),
                        koszyk_Marty.begin(), koszyk_Marty.end(),
                        std::back_inserter(koszyk_roznic));
    // then everything that's present in `koszyk Marty`, but not in the `koszyk Malgosi`
    std::set_difference(koszyk_Marty.begin(), koszyk_Marty.end(),
                        koszyk_Malgosi.begin(), koszyk_Malgosi.end(),
                        std::back_inserter(koszyk_roznic));

    std::cout << "Wspólne dla koszyków owoce i warzywa: " << koszyk_wspolne << std::endl;
    std::cout << "Różniące koszyki owoce i warzywa: " << koszyk_roznic << std::endl;
}
#pragma endregion

// 🛠 Zadanie 15
#pragma region TASK 15
void task_15() {
    cout << "\n\n\n--- TASK 15 ---\n";
    Koszyk koszyk_Malgosi = ::koszyk;
    Koszyk koszyk_Marty = {(Roslina){TypRosliny::Owoc, "Jagoda"}, (Roslina){TypRosliny::Warzywo, "Zieminak"}, (Roslina){TypRosliny::Owoc, "Truskawka"}};
    sort(koszyk_Malgosi.begin(), koszyk_Malgosi.end(), [](const auto & r1, const auto & r2){return r1 < r2;});
    sort(koszyk_Marty.begin(), koszyk_Marty.end(), [](const auto & r1, const auto & r2){return r1 < r2;});
    cout << "Koszyk Małgosi: " << koszyk_Malgosi << "\n";
    cout << "Koszyk Marty: " << koszyk_Marty << "\n";
    Koszyk wspolny;
    set_union(koszyk_Malgosi.begin(), koszyk_Malgosi.end(),
              koszyk_Marty.begin(), koszyk_Marty.end(),
              back_inserter(wspolny));
    cout << "Zawartośc koszyków w jednym: " << wspolny << "\n";
}
#pragma endregion

// 🛠 Zadanie 16
#pragma region TASK 16
struct Exchange_rate
{
    std::string date;
    double usd;
    double eur;
    std::string table_id;
};

struct ErPred {
    bool operator() (const Exchange_rate & er, const double & search) const { return search > er.usd; } // more (search in <mid:upper_bound>)
    bool operator() (const double & search, const Exchange_rate & er) const { return search < er.usd; } // less (search in <lower_bound:mid>)
};

void task_16() {
    cout << "\n\n\n--- TASK 16 ---\n";
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
    std::vector<Exchange_rate> sorted_by_usd = rates;
    std::vector<Exchange_rate> sorted_by_eur = rates;
    sort(sorted_by_usd.begin(), sorted_by_usd.end(), [](const auto & er1, const auto & er2){return er1.usd < er2.usd;});
    sort(sorted_by_eur.begin(), sorted_by_eur.end(), [](const auto & er1, const auto & er2){return er1.eur < er2.eur;});
    size_t rates_len = rates.size();

    // Wyświetl 10 dni (datę oraz wartość), w których kurs USD był najwyższy
    cout << "Wyświetl 10 dni (datę oraz wartość), w których kurs USD był najwyższy:\n";
    for (int i = 0; i < 10; ++i) {
        auto rate = sorted_by_usd[rates_len - 1 - i];
        cout << (i + 1) << ". " << rate.date << " " << rate.usd << "\n";
    }

    // Wyświetl 10 dni (datę oraz wartość), w których kurs EUR był najniższy
    cout << "\nWyświetl 10 dni (datę oraz wartość), w których kurs EUR był najniższy:\n";
    for (int i = 0; i < 10; ++i) {
        auto rate = sorted_by_eur[i];
        cout << (i + 1) << ". " << rate.date << " " << rate.eur << "\n";
    }

    // Użyj przeszukiwania binarnego żeby sprawdzić, w którym dniu kurs USD wynosił 3.9011PLN
    double search = 3.9011;
    const auto result = equal_range(sorted_by_usd.begin(), sorted_by_usd.end(), search, ErPred());
    const auto found = result.first - sorted_by_usd.begin();
    cout << "\nKurs USD wynosił 3.9011PLN w dniu: " << sorted_by_usd[found].date << "\n";
}
#pragma endregion

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "PSiO at Poznan University Of Technology\n";
    cout << "Laboratory 03\n";
    cout << "Executed by Konrad Ceglarski\n";
    cout << "18/03/2023\n";

    globals();

    task_1();  // 🛠 Zadanie 1
    task_2();  // 🛠 Zadanie 2
    task_3();  // 🛠 Zadanie 3
    task_4();  // 🛠 Zadanie 4
    task_5();  // 🛠 Zadanie 5
    task_6();  // 🛠 Zadanie 6
    task_7();  // 🛠 Zadanie 7
    task_8();  // 🛠 Zadanie 8
    task_9();  // 🛠 Zadanie 9
    task_10(); // 🛠 Zadanie 10
    task_11(); // 🛠 Zadanie 11
    task_12(); // 🛠 Zadanie 12
    task_13(); // 🛠 Zadanie 13
    task_14(); // 🛠 Zadanie 14
    task_15(); // 🛠 Zadanie 15
    task_16(); // 🛠 Zadanie 16

    return 0;
}
