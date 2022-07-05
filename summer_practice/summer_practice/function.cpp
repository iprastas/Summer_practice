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

void search_solution(vector<string>& solution, int index, vector<int> numberarr, string* words, set<char> alph) { //������� ������� ��������. ������ ������ � ��� ������� ��-�� ������������� ������� �������� �� ���
	string str;
	string tempstr;

	for (int i = 0; i < 10; i++) { //�������� �����
		bool k = 1;//���������, ��� ��� ��� �� ���� ������� ������

		for (int j = 0; j < index; j++) {
			if (i == numberarr[j])
				k = 0;
		}
		if (k){ //���� ��� ������, ����������� �������� � ������ �������� �������, ����� ���� ������ �����
			numberarr[index] = i;
			if (index == numberarr.size() - 1) { //�������, ����� �������� �� �������� �� ������ ���������
				//����� ������ �������� �� ������������ ��������� �������� ����������������
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
			else { //���� ��� ���� ������������� ��������
				search_solution(solution, index + 1, numberarr, words, alph);
			}
		}
	}
}

bool check_solution(vector<int> numberarr, string* words, set<char> alph) { //������� �������� ��������
	int val1 = 0, val2 = 0, val3 = 0, m = 1;//val - �����, ��������������� ������

	for (int i = words[0].size() - 1; i >= 0; i--) { // �������� ����� �� ������� �����
		set <char>::iterator it = alph.begin();

		for (int j = 0; j < alph.size();j++) { //�������� ����� �� ��������
			if (words[0][i] == *it) { //���� ��� �������,
				val1 += m * numberarr[j];
				break;
			}
			it++;
		}
		m *= 10; // ������� � ������ �������
	}

	m = 1;
	for (int i = words[1].size() - 1; i >= 0; i--) { //���������� �����, ���������� �������
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
	for (int i = words[2].size() - 1; i >= 0; i--) { //���������� �����, ���������� �������
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
	if (val3 == val1 + val2)//��������� �� ��������������
		return true;
	return false;
}
