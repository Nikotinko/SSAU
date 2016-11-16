// Labs3.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "windows.h"
#include "iostream"
#include "fstream"

using namespace std;

bool resault(int a, int b, int &c) {//������� ������� ��������� (a+c/b-28)/(4*a*b+1)
	bool f=false; // ������ ������������� � ������������
	int m = c; //��������� ���������� ��������� ����� ������� �� ������� � ��������� c
	__asm{
		mov eax, m; //eax = c 
		cdq;  // ��������
		idiv b; //eax = c/b
		mov edx, eax; //��������� ������� edx ���������� ���� ����� ���������� ��������� c/b
		sar edx, 31;
		mov ecx, a;	//ecx = a, ����� �� ���� ������������ ����������� 2 ��������
		sar ecx, 31; // ecx ������� �� �������� ����� �����, ����� ���������� �������� 
		add eax, a; //���������� ������� �����
		adc edx, ecx; //���������� ������� ����� <edx:eax> =  a + c / b
		xor ecx, ecx; //� �������� ecx ����� "�������" ����� ����� 28
		sub eax, 28; // �������� ������� ����� �����
		sbb edx, ecx; //<edx:eax> =  a + c / b - 28 
		push edx;
		push eax; //���������� ��������� ��������� a + c / b - 28
		mov eax, a; //eax = a
		imul b;// <edx:eax> = a * b //�������� ������������
		jno metka1;
		inc f; //���� ���� ������������ ��������� �� ��� ������� � ������������� ����, ���� �� ���� �� ���������� ��� �������
	metka1: 
		sal eax, 2; //eax = 4*a*b
		jno metka2;
		inc f; //���� ���� ������������ ��������� �� ��� ������� � ������������� ����, ���� �� ���� �� ���������� ��� �������
	metka2:
		inc eax; // eax = 4*a*b+1
		//��� �� ����� ������������, �.�. 4*a*b ��� ����� ������ �����
		//� ����������� ��������� ����� ��� ���� int 2147483647 - ��������, ���� �� ���� ������������ ������ ����������� ���������
		//�����, ������� ����� �������� 2147483646, �� �������� ����������
		mov ecx, eax; // ecx = eax
		pop eax; //��������� � �������
		pop edx; //��������� ��������� ������ ������ �� �����
		idiv ecx; // eax = ( a + c / b - 28 ) / ( 4 * a * b + 1 )
		mov m, eax;
	}
	c = m;
	return f;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	int a, b, c, a1;
	ofstream fout;
	ifstream fin;
	fout.open("C:\\Users\\vlad\\Desktop\\�����.txt");
	fin.open("C:\\Users\\vlad\\Desktop\\�������.txt");
	cout << "������� �31" << endl;
	cout << "��������� ������������� ������� ���������� �������������� ��������� �� ���������� ����������." << endl;
	cout << "���������: (a + b / c - 28) / (4 * b * a + 1)" << endl;
	cout << "��� ��������� ������� 32 ������ ����� �����." << endl;
	cout << "����� �������� � ��������� ����� <�������.txt>, ������� ��������� �� ���. �����." << endl;
	cout << "����� ������������ � ��������� ���� <�����.txt>, ������� ��������� �� ���. �����" << endl;
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> a >> b >> c;
			a1 = c;
			while (!b) {
				cout << " �������� ������� �� ����, ������� ����� �������� ��� ����������" << endl;
				cin >> b;
			}
			if (!resault(a, b, c)) {	
				fout << c << endl;
			}
			else{
				fout << "������������" << endl;
			}
			//cout << ((a + c / b - 28) / (4 * a * b + 1)) << endl;
		}
	}
	else {
		cout << "������ �������� �����" << endl;
	}
	system("pause");
	return 0;
}
