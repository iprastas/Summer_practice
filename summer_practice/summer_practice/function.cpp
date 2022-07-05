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

void search_solution(vector<string>& solution, int index, vector<int> numberarr, string* words, set<char> alph) { //функция подбора значений. строки входят в эту функцию из-за невозможности вынести проверку из нее
	string str;
	string tempstr;

	for (int i = 0; i < 10; i++) { //выбираем цифру
		bool k = 1;//проверяем, что она еще не была выбрана раньше

		for (int j = 0; j < index; j++) {
			if (i == numberarr[j])
				k = 0;
		}
		if (k){ //если все хорошо, присваиваем значение и заново вызываем функцию, иначе ищем другую цифру
			numberarr[index] = i;
			if (index == numberarr.size() - 1) { //смотрим, чтобы значения не выходили за предел имеющихся
				//иначе делаем проверку на соответствие выбранных значений действительности
				if (check_solution(numberarr, words, alph)) {

					set <char>::iterator it = alph.begin();
					for (int j = 0; j < numberarr.size(); j++) {
						tempstr = *it;
						it++;
						str += tempstr + " = " + to_string(numberarr[j]) + "; ";

						//cout<<str<< "*"<<solution[0]<<"*";
					}
					solution.push_back(str);
				}
			}
			else { //если еще есть незаполненные значения
				search_solution(solution, index + 1, numberarr, words, alph);
			}
		}
	}
}

bool check_solution(vector<int> numberarr, string* words, set<char> alph) { //функция проверки значений
	int val1 = 0, val2 = 0, val3 = 0, m = 1;//val - числа, соответствующие словам

	for (int i = words[0].size() - 1; i >= 0; i--) { // выбираем букву из первого слова
		set <char>::iterator it = alph.begin();

		for (int j = 0; j < alph.size();j++) { //выбираем букву из алфавита
			if (words[0][i] == *it) { //если они совпали,
				val1 += m * numberarr[j];
				break;
			}
			it++;
		}
		m *= 10; // переход к новому разряду
	}

	m = 1;
	for (int i = words[1].size() - 1; i >= 0; i--) { //составляем число, аналогично первому
		set <char>::iterator it = alph.begin();

		for (int j = 0; j < alph.size(); j++) {
			if (words[1][i] == *it) {
				val2 += m * numberarr[j];
				break;
			}
			it++;
		}
		m *= 10;
	}

	m = 1;
	for (int i = words[2].size() - 1; i >= 0; i--) { //составляем число, аналогично первому
		set <char>::iterator it = alph.begin();

		for (int j = 0; j < alph.size(); j++) {
			if (words[2][i] == *it) {
				val3 += m * numberarr[j];
				break;
			}
			it++;
		}
		m *= 10;
	}
	if (val3 == val1 + val2)//проверяем на справедливость
		return true;
	return false;
}
