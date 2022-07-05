#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include "function.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    unsigned int start_time;

    vector<string> solution; //вектор всех решений

    ifstream fin("чудо строки.txt");
    if (!fin.is_open()) {
        throw 1;
    }

    /*for (int num_example = 0; num_example < 3; num_example++)*/
    while (!fin.eof()) {
        start_time = clock();

        try {
            std::string words[] = { "", "", "" };

            string str;
            for (int i = 0; i < 3; i++) {
                fin >> str;
                words[i] = str;
            }

            cout << "Дан ребус: " << words[0] << " + " << words[1] << " = " << words[2] << endl;

            set<char> alph;
            for (int i = 0; i < 3; i++) {
                alph.insert(words[i].begin(), words[i].end()); //множество уникальных букв
            }

            if (alph.size() > 10) throw 1; //обработки исключений
            int max_word = words[0].length() > words[1].length() ? words[0].length() : words[1].length();
            if (words[2].length() < words[0].length() || words[2].length() < words[1].length()) throw 2;
            if (words[2].length() - max_word > 1) throw 3;

            vector<int> num(alph.size(), -1); //алфавит цифр

            search_solution(solution, 0, num, words, alph);

            unsigned int end_time = clock(); //время до вывода в консоль (чтобы считалось время только поиска решений)
            cout << "\nВремя только поиска решений: " << (end_time - start_time) / 1000. << endl;

            cout << "Все решения ребуса:" << endl;
            for (int i = 0; i < solution.size(); i++)
                cout << solution[i] << endl;

            solution.clear();
        }
        catch (int err) {
            cout << "Ошибка.";
            if (err == 1) {
                cout << "Различных букв больше 10. Невозможно зашифровать однозначно.\n";
            }
            if (err == 2) {
                cout << "Слово в ответе короче слов 1 и/или 2 . Нет решений.\n";
            }
            if (err == 3) {
                cout << "Слово в ответе больше самого длинного слова на > 2. Нет решений.\n";
            }
            if (err == 4) {
                cout << "Решений нет." << endl;
            }
        }

        cout << "-------------------------------\n" << endl;
    }
    fin.close();
}