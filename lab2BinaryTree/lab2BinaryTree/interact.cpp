
#include <conio.h>
#include <iostream>
#include "TreeClass.h"

using namespace std;

void Hello()
{
	setlocale(LC_ALL, "Russian");
	cout << "���������, ����������� �������� ������� (MERGE), ���������� (EXCL)\n";
	cout << "� ������ (CHANGE) ��� ������������������ � ���.\n";
	cout << "������� 1\n";
	cout << "������ �.�., ������ �.�.\n" ;
};
void Menu()
{
		unsigned short Ch = 5;

	while(Ch)
	{
		label:
		BinaryTree A('A'), B('B'), F('F');

		cout << "����:" << std::endl;
		cout << "1 - ������������� ������;" << std::endl;
		cout << "2 - ������ ������;" << std::endl;
		cout << "0 - �����." << std::endl << std::endl;
		cout << ">> ";
		cin >> Ch;

		if(cin.fail() && Ch)
		{
			cin.clear();
			cin.sync();
			cout << "������! �������� �������� ���������." << endl << endl;
			continue;
		};

		switch(Ch)
		{
		case 1:
			A.GenerateSet();
			B.GenerateSet();
			break;
		case 2:
			A.InputSet();
			B.InputSet();
			break;
		default:
			if (Ch)
			{
				cout << "������! �������� �������� ���������." << endl << endl;
				cin.clear();
				cin.sync();
				Ch = 0;
			};
			break;
		};

		if(Ch)
		{
			//������� ������� �������
			cout << "�������� �������:" << endl;
			A.TreeOut();
			B.TreeOut();

			//������� ������������������
			cout << "�������� ������������������:" << endl;
			A.SetOut();
			B.SetOut();

			//������� � ������� ��������
			Ch = 5;

			while (Ch)
			{
				BinaryTree TempTree('F');
				F.Name = 'F';

				cout << endl << "�������� ��������:" << endl;
				cout << "1 - MERGE;" << endl;
				cout << "2 - EXCL;" << endl;
				cout << "3 - CHANGE;" << endl;
				cout << "0 - �����." << endl << endl;

				cin >> Ch;

				switch (Ch)
				{
				case 1:
					cout << "������� ������� MERGE." << endl;
					F = F.MERGE(A, B);
					break;
				case 2:
					cout << "������� ������� EXCL." << endl;
					F = F.EXCL(A, B);
					break;
				case 3:
					unsigned int Pos;
					cout << "������� ������� CHANGE." << endl;
					cout << "����� �������, � ������� ����� ����������� ������: ";
					cin >> Pos;

					if (cin.fail())
					{
						cout << "������! �������� �������� ���������." << endl << endl;
						cin.clear();
						cin.sync();
						break;
					}
					else
						F = F.CHANGE(A, B, Pos);
					break;
				default:
					if (Ch)
					{
						cout << "������! �������� �������� ���������." << endl << endl;
						cin.clear();
						cin.sync();
						Ch = 0;
					};
					break;
				};

				if (Ch)
				{
					F.TreeOut();
					F.SetOut();
				};
				cout << endl;

				//��� � ����� ������ ����
				goto label;
			};
		};
	};
	return;
};
