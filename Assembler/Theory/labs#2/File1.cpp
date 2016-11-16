#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <Math.h>
#include <Windows.h>

using namespace std;

double Summa(double &x, int &n, double &e)
{ // ������� ������� ����� ���� � n-�� ������ ������ -(x^n)/n
	double an, ann; // an - n-�� ������� ����, ann - n+1 - ������� ����
	double s = x; // �� ����� ��������� ������� ��� ���������� ����� ����
	int no = 1; // ������� ���-�� ����������� ��������
	an = x;
	ann = an;
	while (true) {
		ann = an * no * x / (no + 1);
		s = s + ann;
		if (abs(ann) < e) { // ��������� ���������� �� ������ ��������
			break; // ���� �� �� ������� �� �����
		}
		an = ann;
		++no;
		if (no > n) {
			cout << "���������� ������������ ����� ��������" << endl;
			break;
		}
	}
	// ��������� ����� ���� (x^n)/n ������ -(x^n)/n
	return -s; // ��� ������� ������ ������ ��������� -s
}

int _tmain(int argc, _TCHAR* argv[]) {
	SetConsoleCP(1251);
	// ���������� ��� ����������� ����������� �������� ������ � �������
	SetConsoleOutputCP(1251);
	double x = -2, e;
	// �=-2 ���������� ��� ������ ������ �����, �.�. -2 �� ������ � ���������� [-1, 1)
	int n = -1;
	// n=-1 ���������� ��� ������ ������ �����, �.�. ���-�� �������� �� ����� ���� �������������
	char st[10];
	// ���� ��������� ��������� �������, ������ �����������, ��� ���� ������������, ����� ��� �����
	do {
		cout << "������� ������� �" << endl;
		cin >> st;
		// ���� � ������ ������ ����� �����, � ����� ����� � ������ �������
		// �� � ����� ��������� ���� �����, ������� ����� ������ � ������ ������
		if (('A' < st[0] && st[0] < 'z') || ('�' < st[0] && '�' > st[0]))
		{ // ��������� ��� ���� ������������, ����� ��� �����
			system("cls"); // ���������� ��� ��������� ������ � �������
			cout << "������� �����, � �� �����" << endl;
		}
		else {
			x = atof(st);
			if ((x < 1) && (x >= -1))
			{ // ��������� ������ �� ��������� �������� � �������� -1<=x<1
				break;
			}
			else {
				system("cls");
				cout << "�������� � ������ ���� �����: -1<=X<1" << endl;
			}
		}
	}
	while ((x >= 1) || (x < -1));
	do {
		cout << "������� ������� N" << endl;
		cin >> st;
		if ('A' < *st && *st < 'z')
		{ // ��������� ��� ���� ������������, ����� ��� �����
			cout << "������� �����, � �� �����" << endl;
		}
		else {
			n = atoi(st);
			// ���� ������ ������� �����, �� ����� ���������� ������ ����� �����
			if (n < 0)
			{ // �������� �� ���, ��� �� ����� �������� ���� ������������
				cout << "����� N ������ ���� �������������." << endl;
			}
		}
	}
	while (n < 0);
	cout << "������� ������� E" << endl;
	do {
		cin >> st;
		if ('A' < *st && *st < 'z') {
			cout << "������� �����, � �� �����" << endl;
		}
		else {
			e = atof(st);
			if (e < 0) { // �������� �� ��, ��� �� �������� ���� �������������
				cout << "����� � ������ ���� �������������." << endl;
			}
		}
	}
	while (e < 0);
	double s = Summa(x, n, e);
	double l = log(1 - x);
	cout << "�������� ������� ln(1-x) ����������� � ������� ���� �����: " <<
		s << endl;
	cout << "�������� ������� ln(1-x) ����������� ��� ������ ���������� ������ ������������\n��������� �����: "
		<< l << endl;
	cout << "����������� �����: " << abs(l - s) << endl;
	char c;
	cout << "������� ����� ������ � ������� Enter" << endl;
	cin >> c;
	return 0;
}
