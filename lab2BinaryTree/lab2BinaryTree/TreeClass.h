//����, ���������� ���������� ������ BinaryTree
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
//����, �������� ������ ���������� ���������
class Node
{
public:
	int key;

	Node *RightSon;
	Node *LeftSon;

	Node *Parent;

	//��������� �� ��������� ������� ������������������
	Node *NextNode;

	//��������� �� ���������� ������� ������������������
	Node *PrevNode;

	//����� ������������ �������� ���������
	Node* Minimum(Node* TempNode);

	//����� ���������� ��������, ������������ ������� ����
	Node* Next(Node* TempNode);

	//������� ���������� "��������" �������
	unsigned int FindMiddle(int a, int b, vector<Element>& data);

	//���������� ������
	Node* Build(int a, int b, vector<Element>& data);

	//������� ������
	Node *Convolution(int a, int b, vector<Element>& data, Node *Cur, unsigned int Mid);

	//������� ���������� ������� ������ ��������� �������
	Node *BuildInArea(int a, int b, vector<Element>& data);

	//������� ��������� ���������� �������� ������������������
	void SetNextNode(Node* TempNode)
	{
		NextNode = TempNode;
	};

	//������� ��������� ����������� �������� ������������������
	void SetPrevNode(Node* TempNode)
	{
		PrevNode = TempNode;
	};

	//������� ��������� ��������� �� ��������� ������� ������������������
	Node *GetNextNode(void)
	{
		return NextNode;
	};

	//������� ��������� ��������� �� ���������� ������� ������������������
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
	//������ ������
	Node *root;

	//������ ������
	int Height(Node* TempNode);

	//�������������� ��� ������
	char Name; 

	//������ ������������������
	Node *Head;

	BinaryTree(char Ch) : Name(Ch), root(nullptr) {};

	//������� �����-������
	void GenerateSet(void);
	void InputSet(void);
	void TreeOut(void);
	void SetOut(void);

	//������ � �������
	//��������� ���� � ������
	void AddNode(int Key, Node *TempNode); 
	//��������� ������ �� ������� �����
	Node* FindKey(int Key, Node *TempNode);
	//������� ���� � �������� ������ �� ��������� ���������, ���������� ���������
	Node* RemoveNode(int Key, Node* TempNode);

	//�������������� ������������������
	BinaryTree *RestoreSet(Node *Nd, vector<Element>& Set);

	//������� ������ ���������������������
	bool Find(BinaryTree *Source, BinaryTree *Sample, Node *&Begin, Node *&End);

	 //�������� ��� ��������������������
	 BinaryTree MERGE(const BinaryTree left, const BinaryTree right);
	 BinaryTree EXCL(BinaryTree left, BinaryTree right);
	 BinaryTree CHANGE(BinaryTree left, BinaryTree right, unsigned int Pos);
};

#endif
