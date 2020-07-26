
#include <conio.h>
#include <iostream>
#include "TreeClass.h"

using namespace std;

void Hello()
{
	setlocale(LC_ALL, "Russian");
	cout << "Программа, реализующая операции слияния (MERGE), исключения (EXCL)\n";
	cout << "и замены (CHANGE) для последовательности в ДДП.\n";
	cout << "Вариант 1\n";
	cout << "Козлов Д.В., Марчук Л.Б.\n" ;
};
void Menu()
{
		unsigned short Ch = 5;

	while(Ch)
	{
		label:
		BinaryTree A('A'), B('B'), F('F');

		cout << "Меню:" << std::endl;
		cout << "1 - Сгенерировать данные;" << std::endl;
		cout << "2 - Ввести данные;" << std::endl;
		cout << "0 - Выход." << std::endl << std::endl;
		cout << ">> ";
		cin >> Ch;

		if(cin.fail() && Ch)
		{
			cin.clear();
			cin.sync();
			cout << "Ошибка! Неверное значение параметра." << endl << endl;
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
				cout << "Ошибка! Неверное значение параметра." << endl << endl;
				cin.clear();
				cin.sync();
				Ch = 0;
			};
			break;
		};

		if(Ch)
		{
			//Выводим сначала деревья
			cout << "Введённые деревья:" << endl;
			A.TreeOut();
			B.TreeOut();

			//Выводим последовательности
			cout << "Введённые последовательности:" << endl;
			A.SetOut();
			B.SetOut();

			//Подменю с выбором операций
			Ch = 5;

			while (Ch)
			{
				BinaryTree TempTree('F');
				F.Name = 'F';

				cout << endl << "Выберите операцию:" << endl;
				cout << "1 - MERGE;" << endl;
				cout << "2 - EXCL;" << endl;
				cout << "3 - CHANGE;" << endl;
				cout << "0 - Выход." << endl << endl;

				cin >> Ch;

				switch (Ch)
				{
				case 1:
					cout << "Выбрана функция MERGE." << endl;
					F = F.MERGE(A, B);
					break;
				case 2:
					cout << "Выбрана функция EXCL." << endl;
					F = F.EXCL(A, B);
					break;
				case 3:
					unsigned int Pos;
					cout << "Выбрана функция CHANGE." << endl;
					cout << "Номер позиции, с которой нужно производить замену: ";
					cin >> Pos;

					if (cin.fail())
					{
						cout << "Ошибка! Неверное значение параметра." << endl << endl;
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
						cout << "Ошибка! Неверное значение параметра." << endl << endl;
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

				//Идём в самое начало меню
				goto label;
			};
		};
	};
	return;
};
