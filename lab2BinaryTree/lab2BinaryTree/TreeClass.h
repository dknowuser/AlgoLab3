//Файл, содержащий объявление класса BinaryTree
#ifndef TREE
#define TREE

struct Element
{
	int Value;
	int Order;
	bool Used;
};

#include<vector>
using namespace std;
//Узел, содержит список эелементов множества
class Node
{
public:
	int key;

	Node *RightSon;
	Node *LeftSon;

	Node *Parent;

	//Указатель на следующий элемент последовательности
	Node *NextNode;

	//Указатель на предыдущий элемент последовательности
	Node *PrevNode;

	//Поиск минимального элемента поддерева
	Node* Minimum(Node* TempNode);

	//Поиск следующего элемента, относительно данного узла
	Node* Next(Node* TempNode);

	//Функция вычисления "середины" отрезка
	unsigned int FindMiddle(int a, int b, vector<Element>& data);

	//Построение дерева
	Node* Build(int a, int b, vector<Element>& data);

	//Функция свёртки
	Node *Convolution(int a, int b, vector<Element>& data, Node *Cur, unsigned int Mid);

	//Функция добавления сыновей внутри заданного отрезка
	Node *BuildInArea(int a, int b, vector<Element>& data);

	//Функция установки следующего элемента последовательности
	void SetNextNode(Node* TempNode)
	{
		NextNode = TempNode;
	};

	//Функция установки предыдущего элемента последовательности
	void SetPrevNode(Node* TempNode)
	{
		PrevNode = TempNode;
	};

	//Функция получения указателя на следующий элемент последовательности
	Node *GetNextNode(void)
	{
		return NextNode;
	};

	//Функция получения указателя на предыдущий элемент последовательности
	Node *GetPrevNode(void)
	{
		return PrevNode;
	}

	friend class BinaryTree;

	Node(int i) :key(i), Parent(nullptr), RightSon(nullptr), LeftSon(nullptr), NextNode(nullptr), PrevNode(nullptr) {};
};

class BinaryTree
{
public:
	//Корень дерева
	Node *root;

	//Высота дерева
	int Height(Node* TempNode);

	//Односимвольное имя дерева
	char Name; 

	//Начало последовательности
	Node *Head;

	BinaryTree(char Ch) : Name(Ch), root(nullptr) {};

	//Функции ввода-вывода
	void GenerateSet(void);
	void InputSet(void);
	void TreeOut(void);
	void SetOut(void);

	//Работа с деревом
	//Добавляет узел к дереву
	void AddNode(int Key, Node *TempNode); 
	//Проверяет дерево на наличие ключа
	Node* FindKey(int Key, Node *TempNode);
	//Удаляет узел с заданным ключем из заданного поддерева, возвращает поддерево
	Node* RemoveNode(int Key, Node* TempNode);

	//Восстановление последовательности
	BinaryTree *RestoreSet(Node *Nd, vector<Element>& Set);

	//Функция поиска подпоследовательности
	bool Find(BinaryTree *Source, BinaryTree *Sample, Node *&Begin, Node *&End);

	 //Операции над последовательностями
	 BinaryTree MERGE(const BinaryTree left, const BinaryTree right);
	 BinaryTree EXCL(BinaryTree left, BinaryTree right);
	 BinaryTree CHANGE(BinaryTree left, BinaryTree right, unsigned int Pos);
};

#endif
