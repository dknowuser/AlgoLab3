#include <iostream>
#include <deque>
#include <iomanip>
#include "TreeClass.h"
#include <vector>
#include <algorithm>

using namespace std;

void Sort(vector<Element>& In);

//����� ������������ �������� ���������
Node* Node::Minimum(Node* TempNode)
{
	while (TempNode->LeftSon)
		TempNode = TempNode->LeftSon;

	return TempNode;
};

//����� ���������� ��������, ������������ ������� ����, ���� ���������� NULL, �� ���� �������� ���������
Node* Node::Next(Node* TempNode)
{
	//���� ������ ������ ���� � ������� �������
	if (TempNode->RightSon)
		return TempNode->Minimum(TempNode->RightSon);
	
	Node* y = TempNode->Parent;
	while ((y != NULL) && (TempNode == y->RightSon))
	{
		//���� ��� ������ ��� �����
		TempNode = y;
		y = y->Parent;
	}
	return y;
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//����� ����
Node* BinaryTree::FindKey(int Key, Node *TempNode)//� �������� ���������� ��������� TempNode ������ ������� root ������� ������(���������)
{
	if(TempNode == NULL)
		return NULL;
	if(Key == TempNode->key)
		return TempNode;
	if(Key > TempNode->key)
		return FindKey(Key,TempNode->RightSon);
	if(Key < TempNode->key)
		return FindKey(Key,TempNode->LeftSon);
};

//���������� ����
void BinaryTree::AddNode(int Key, Node *TempNode)//� �������� ���������� ��������� TempNode ������ ������� root ������� ������(���������)
{
	if(this->root == NULL){//���� ������ ����
		this->root = new Node(Key);
		this->root->LeftSon = NULL;
		this->root->RightSon = NULL;
		this->root->Parent = NULL;
		return;
	}
	if(Key == TempNode->key){ //���� ���� ��� ������������
		return;
	}

	if(Key > TempNode->key){//���� ���� ������
		if(TempNode->RightSon == NULL){
			TempNode->RightSon = new Node(Key);
			TempNode->RightSon->LeftSon = NULL;
			TempNode->RightSon->RightSon = NULL;
			TempNode->RightSon->Parent = TempNode;
			return;
		}
		else
			this->AddNode(Key, TempNode->RightSon); //���������� ����� ������
	}

	 if(Key < TempNode->key){//���� ���� ������
		if(TempNode->LeftSon == NULL){
			TempNode->LeftSon = new Node(Key);
			TempNode->LeftSon->LeftSon = NULL;
			TempNode->LeftSon->RightSon = NULL;
			TempNode->LeftSon->Parent = TempNode;
			return;
		}
		else
			this->AddNode(Key, TempNode->LeftSon); //���������� ����� �����
	}
	return;
};

//�������� ����
Node* BinaryTree::RemoveNode(int Key, Node* TempNode)
{
	if(TempNode == NULL)
		return NULL;
	if( Key < TempNode->key)
		TempNode->LeftSon = RemoveNode(Key, TempNode->LeftSon);
	else if (Key > TempNode->key)
		TempNode->RightSon = RemoveNode (Key, TempNode->RightSon);
	else if((TempNode->LeftSon != NULL) && (TempNode->RightSon != NULL)){
		TempNode->key = TempNode->Minimum(TempNode->RightSon)->key;
		TempNode->RightSon = RemoveNode(Key, TempNode->RightSon);
	}
	else {
		if (TempNode->LeftSon != NULL)
			TempNode = TempNode->LeftSon;
		else
			TempNode = TempNode->RightSon;
	}
	return TempNode;
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//������
BinaryTree BinaryTree::CHANGE(BinaryTree left, BinaryTree right, unsigned int Pos)
{
	if (!left.root)
		return NULL;

	if (!right.root)
		return left;

	unsigned int Order = 0;

	//���� �������� �������
	Node *Temp = left.Head;
	Node *Add = right.Head;
	Node *Tail = nullptr;

	while (Temp && (Order != Pos))
	{
		Order++;
		Temp = Temp->GetNextNode();
	};

	if ((Order != Pos) || !Temp)
	{
		cout << "������! �������� ������� ��������� ������ ������������������." << endl;
		return NULL;
	};

	//���� ����������� � ����� ������������������ "�����"
	Node *Keep = Temp;
	while (Add && Temp)
	{
		Add = Add->GetNextNode();
		Temp = Temp->GetNextNode();
	};
	if (Temp)
		Tail = Temp;

	Add = right.Head;
	Temp = Keep;

	if (!Pos)
		left.Head = right.Head;
	else
	{
		if (Temp)
			Temp->GetPrevNode()->SetNextNode(Add);
		if(Add)
			Add->SetPrevNode(Temp->GetPrevNode());
	};

	//������� �� ����� ������������������ � ��������� "�����"
	if (Add)
	{
		while (Add->GetNextNode())
			Add = Add->GetNextNode();

		Add->SetNextNode(Tail);
	};

	//��������������� ������������������
	Temp = left.Head;
	vector<Element> data;
	Order = 0;

	while (Temp)
	{
		Element El;
		El.Value = Temp->key;
		El.Used = false;
		El.Order = Order;
		data.push_back(El);

		Order++;
		Temp = Temp->GetNextNode();
	};

	if (data.size())
	{
		Sort(data);
		this->root = this->root->Build(0, data.size() - 1, data);
		RestoreSet(this->root, data);
		data.clear();
		return *this;
	}
	else
		return NULL;
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//�������
BinaryTree BinaryTree::MERGE(const BinaryTree left, const BinaryTree right)
{
	if (!left.root)
		return right;

	if (!right.root)
		return left;

	//������� ��� ������ ������������, �������� ������������������
	vector<Element> data;
	unsigned int Order = 0;
	Node *Temp1 = left.root->Minimum(left.root);
	Node *Temp2 = right.root->Minimum(right.root);

	while (Temp1 || Temp2)
	{
		while (((Temp1 && Temp2) && (Temp1->key <= Temp2->key)) || (Temp1 && !Temp2))
		{
			Element El;
			El.Used = false;
			El.Value = Temp1->key;
			El.Order = Order;

			data.push_back(El);
			Temp1 = Temp1->Next(Temp1);
			Order++;
		};

		while ((Temp1 && Temp2) && ((Temp2->key <= Temp1->key)) || (Temp2 && !Temp1))
		{
			Element El;
			El.Used = false;
			El.Value = Temp2->key;
			El.Order = Order;

			data.push_back(El);
			Temp2 = Temp2->Next(Temp2);
			Order++;
		};
	};

	if (data.size())
	{
		this->root = this->root->Build(0, data.size() - 1, data);
		RestoreSet(this->root, data);
		data.clear();
		return *this;
	}
	else
		return NULL;
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//������� ������ ���������������������
bool BinaryTree::Find(BinaryTree *Source, BinaryTree *Sample, Node *&Begin, Node *&End)
{
	//Begin = Source->Head;

	while (Begin)
	{
		//���� ������ ������ ������� ������������������
		if (Begin->key == Sample->Head->key)
		{
			//��������� ��� ������������������
			bool Find = true;
			Node *Temp1 = Begin->GetNextNode();
			Node *Temp2 = Sample->Head->GetNextNode();
			End = Begin;

			while (Temp1 && Temp2)
			{
				Find *= (Temp1->key == Temp2->key);
				if(Find)
					End = Temp1;

				Temp1 = Temp1->GetNextNode();
				Temp2 = Temp2->GetNextNode();
			};

			if (!Temp1 && Temp2)
				Find = false;

			if (Find)
			{
				return true;
			};
		};

		Begin = Begin->GetNextNode();
	};
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//����������
BinaryTree BinaryTree::EXCL(BinaryTree left, BinaryTree right)
{
	if (!left.root)
		return NULL;
	if (!right.root)
		return left;

	Node *Begin = left.Head;
	Node *End = nullptr;
	vector<Element> data;
	unsigned int Order = 0;

	//���� ������� ��������� ���������
	while (left.Head && Find(&left, &right, Begin, End))
	{
		Node *Temp = Begin;

		while (Temp && (Temp != End))
		{
			if (Temp->GetPrevNode())
				Temp->GetPrevNode()->SetNextNode(Temp->GetNextNode());

			if (Temp->GetNextNode())
				Temp->GetNextNode()->SetPrevNode(Temp->GetPrevNode());

			if (!Temp->GetPrevNode())
				left.Head = Temp->GetNextNode();

			Temp = Temp->GetNextNode();
		};

		if (Temp == End)
		{
			//������� ���� �����
			if (Temp->GetPrevNode())
				Temp->GetPrevNode()->SetNextNode(Temp->GetNextNode());

			if (Temp->GetNextNode())
				Temp->GetNextNode()->SetPrevNode(Temp->GetPrevNode());

			if (!Temp->GetPrevNode())
				left.Head = Temp->GetNextNode();
		};
		Begin = left.Head;
	};

	//��������������� ������������������
	Node *Restore = left.Head;

	while (Restore)
	{
		Element El;
		El.Value = Restore->key;
		El.Used = false;
		El.Order = Order;
		data.push_back(El);

		Order++;
		Restore = Restore->GetNextNode();
	};

	if (data.size())
	{
		Sort(data);
		this->root = this->root->Build(0, data.size() - 1, data);
		RestoreSet(this->root, data);
		data.clear();
		return *this;
	}
	else
		return NULL;
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//��������������� ������������������
BinaryTree *BinaryTree::RestoreSet(Node *Nd, vector<Element>& Set)
{
	unsigned int Cur = 0;

	//���� ������ ������������������ c ������� ������
	Node *Temp1 = Nd->Minimum(Nd);
	if (Temp1)
	{

		while ((Set[Cur].Order) && (Cur < Set.size()))
			Cur++;

		while (Temp1 && (Temp1->key != Set[Cur].Value))
			Temp1 = Temp1->Next(Temp1);

		Head = Temp1;

		//��������������� ������������������
		//�������� �� ���� ������� ������������������
		for (unsigned int i = 1; i < Set.size(); i++)
		{
			//���� ���� � ����� �������
			Cur = 0;
			while ((Set[Cur].Order != i) && (Cur < Set.size()))
				Cur++;

			Node *Temp2 = Nd->Minimum(Nd);
			while (Temp2 && ((Temp2->key != Set[Cur].Value) || Temp2->GetPrevNode() || (Temp2 == Head)))
				Temp2 = Temp2->Next(Temp2);

			if (Temp2)
				Temp2->SetPrevNode(Temp1);

			if (Temp1)
			{
				Temp1->SetNextNode(Temp2);
				Temp1 = Temp2;
			};
		};

		return this;
	}
	else
		return NULL;
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

void FindEdges(int& c, int& d, vector<Element> data)
{
	int Old = c;
	while ((data.size() > 1) && c && (data[c].Value == data[c - 1].Value))
		c--;

	Old = d;
	while ((data.size() > 1) && (d < data.size() - 1) && (data[d].Value == data[d + 1].Value))
		d++;
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//������� ���������� ������� ������ ��������� �������
Node *Node::BuildInArea(int a, int b, vector<Element>& data)
{
	if (b < a) return NULL;
	int c = (a + b) / 2;
	if (data[c].Used)
		return NULL;

	data[c].Used = true;
	Node *s = new Node(data[c].Value);
	s->LeftSon = BuildInArea(a, c - 1, data);
	if (s->LeftSon != NULL)
		s->LeftSon->Parent = s;
	s->RightSon = BuildInArea(c + 1, b, data);
	if (s->RightSon != NULL)
		s->RightSon->Parent = s;
	return s;
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//������� ���������� "��������" �������
unsigned int Node::FindMiddle(int a, int b, vector<Element>& data)
{
	vector<Element> Temp;

	//������ ������� ������������������ �������� � Temp,
	//����� ��� ������� �������� ���������, ������� �� �� � ������
	for (unsigned int i = a; i <= b; i++)
	{
		if (Temp.empty())
			Temp.push_back(data[i]);
		else
		{
			bool Find = false;
			for (int j = 0; j < Temp.size(); j++)
				Find += (data[i].Value == Temp[j].Value);

			if(!Find)
				Temp.push_back(data[i]);
		};
	};	

	//�������� ����� �������� � ���-�� ��� ���������� - 
	//����� ����� �������� �������� � ���-�� � ������������
	unsigned int Number = Temp.size() / 2;
	unsigned int c = 0;
	unsigned int d = data.size() - 1;
	for (; (c < data.size() && (data[c].Value < Temp[Number].Value)); c++);
	for (; d && (data[d].Value > Temp[Number].Value); d--);

	//���� ����� ����� ��������
	return ((d + c) / 2);
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//������� ������
Node *Node::Convolution(int a, int b, vector<Element>& data, Node *Cur, unsigned int Mid)
{
	//��������� ������� ��� ���������� ������� �����-������ (��������� ���� ��� ���������� ������� ��� �������)
	int Middle;

	if ((b - a) % 2)
	{
		//����������� �������� �������� ������� � �������� ����������� �������, ���� ����� ������� ������
		if (Mid >= b)
			Middle = b;
		else
			if (Mid <= a)
				Middle = a;
			else
				Middle = (a + b) / 2;
	}
	else
		Middle = (a + b) / 2;

	data[Middle].Used = true;

	if (a != Middle)
	{
		//������� ����� �����
		Cur->LeftSon = BuildInArea(a, Middle - 1, data);
		if (Cur->LeftSon != NULL)
			Cur->LeftSon->Parent = Cur;
	};

	if ((data.size() > b) && (b != Middle))
	{
		//������� ������ �����
		Cur->RightSon = BuildInArea(Middle + 1, b, data);
		if (Cur->RightSon != NULL)
			Cur->RightSon->Parent = Cur;
	};

	return Cur;
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------


//���������� ������ �� �������
Node* Node::Build(int a, int b, vector<Element>& data)
{
	//��������� ������ �� ������� ���������� �����
	if (b < a) 
		return NULL;

	//int c = (a + b) / 2;'
	if (!data.size())
		return NULL;

	int c = FindMiddle(a, b, data);

	if (data[c].Used)
		return NULL;

	int d = c;
	FindEdges(c, d, data);

	if (c < a)
		c = a;
	if (d > b)
		d = b;

	int Middle = (c + d) / 2;
	data[Middle].Used = true;
	Node *s = new Node(data[Middle].Value);

	if (c != d)
		s = Convolution(c, d, data, s, Middle);

	//������� ��������� ����� �������
	//����� �����
	if (c && (data[c - 1].Value != data[c].Value))
	{
		//���� ������ ������ ����
		Node *Temp = s;
		while (Temp->LeftSon)
			Temp = Temp->LeftSon;

		Temp->LeftSon = Build(a, c - 1, data);
		if (Temp->LeftSon != NULL)
			Temp->LeftSon->Parent = Temp;
	};

	//������ �����
	if ((data.size() > 1) && (d < data.size() - 1) && (data[d].Value != data[d + 1].Value))
	{
		//���� ������ ������� ����
		Node *Temp = s;
		while (Temp->RightSon)
			Temp = Temp->RightSon;

		Temp->RightSon = Build(d + 1, b, data);
		if (Temp->RightSon != NULL)
			Temp->RightSon->Parent = Temp;
	};

	return s;
};

//�������� �� ������� �������� � �������
bool FindEl(vector<int> data, int el){

	if(data.size() <= 0)
		return false;

	for (int i = 0; i < data.size(); i++)
		if(el == data[i]) return true;
	return false;
};

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//��������� ������
void BinaryTree::GenerateSet(void)
{
	vector<Element> data;
	int Size = rand() % 15 + 1;
	Element Temp;

	for (int i = 0; i < Size; i++)
	{
		Temp.Value = rand() % 10 + 1;
		Temp.Order = i;
		Temp.Used = false;
		data.insert(data.begin(), Temp);
	}
	Sort(data);

	this->root = this->root->Build(0, Size - 1, data); 
	RestoreSet(this->root, data);
	data.clear();
	return;
};

//������� ���������� �������
void Sort(vector<Element>& In)
{
	bool Sorted = false;

	while (!Sorted)
	{
		Sorted = true;

		for (unsigned int i = 0; i < In.size() - 1; i++)
		{
			if (In[i].Value > In[i + 1].Value)
			{
				Sorted = false;

				Element Temp = In[i];
				In[i] = In[i + 1];
				In[i + 1] = Temp;
			};
		};
	};
}

//���� � �������
void BinaryTree::InputSet(void)
{
	cout << "���������� ������ �������: " << this->Name << endl;

	short Size = 0;
	Element Temp;
	Temp.Used = false;
	vector<Element> data;

	cout << "������� ���������� ��������� ��������� (�� 1 �� 10):" << endl;

	while ((Size < 1) || (Size > 10) || cin.fail())
	{
		//���������� �����
		cin.clear();
		cin.sync();
		cin >> Size;

		if ((Size < 1) || (Size > 10) || cin.fail())
		{
			cout << "������! �������� ����� �������." << endl;
			continue;
		}
		else
		{
			data.reserve(Size);
			break;
		};
	};

		//������ �������� ���������
		cout << "������� �������� ��������� ��������� (�� 1 �� 20):" << endl;

		for(unsigned int i = 0; i < Size; i++)
		{
			//���������� �����
			cin.clear();
			cin.sync();
			cout << i + 1 << "-� �����:";
			cin >> Temp.Value;
			Temp.Order = i;

			if((Temp.Value < 1) || (Temp.Value > 20) || cin.fail())
			{
				cout << "������! ����� �� ����������� ������� [1; 20]." << endl;
				i--;
			}
			else
				data.insert(data.end(), Temp);
		}
		cout << endl;

	Sort(data);
	this->root = this->root->Build(0, Size - 1, data);
	RestoreSet(this->root, data);
	data.clear();
	return;
};


//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

//����� ������
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue) {
  deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {
    cout << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    cout << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  cout << endl;
}
 
//����� �����
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue) {
  deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    cout << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->LeftSon) ? setfill('_') : setfill(' '));
	if(*iter)
		cout << setw(branchLen+2) << (*iter)->key;
	else
		cout << setw(branchLen+2) << "";
    cout << ((*iter && (*iter)->RightSon) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
  }
  cout << endl;
}
 
//����� �������
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node*>& nodesQueue) {
  deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
	if(*iter)
	    cout << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << (*iter)->key;
	else 
		cout << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << "";
  }
  cout << endl;
}

int BinaryTree::Height(Node* TempNode){// ��� ������ � �������� ��������� ����� ������

	if(TempNode == NULL)
		return 0;

	int l, r;
	l = Height(TempNode->LeftSon);
	r = Height(TempNode->RightSon);

	if(l > r) return (l+1);
	else return (r+1);
};

//����� ������
void BinaryTree::TreeOut(void)
{
	cout << "�������� ������:" << this->Name << endl;
	if (this->root == NULL){
		cout << "������ �����..." << endl;
		return;
	}
	int h = this->Height(this->root);
	int nodesInThisLevel = 1;
 
	int branchLen = 2*((int)pow(2.0,h)-1) - (int)pow(2.0,h);  // ������ ����� 
	int nodeSpaceLen = 2 + (int)pow(2.0,h+1);  // ���������� ����� ������
	int startLen = branchLen + 2;  //��������� ������
    
	deque<Node*> nodesQueue;
	nodesQueue.push_back(this->root);
	for (int r = 1; r < h; r++) {
		printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
		branchLen = branchLen/2 - 1;
		nodeSpaceLen = nodeSpaceLen/2 + 1;
		startLen = branchLen + 2;
		printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
 
		for (int i = 0; i < nodesInThisLevel; i++) {
			Node *currNode = nodesQueue.front();
			nodesQueue.pop_front();
			if (currNode) {
				nodesQueue.push_back(currNode->LeftSon);
				nodesQueue.push_back(currNode->RightSon);
			} else {
				nodesQueue.push_back(NULL);
				nodesQueue.push_back(NULL);
			}
		}
		nodesInThisLevel *= 2;
	}
	printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
	printLeaves(0, 1, nodesInThisLevel, nodesQueue);
	cout << endl;
	return;
};

//����� ������������������
void BinaryTree::SetOut(void)
{
	cout << "��� ������������������:" << this->Name << endl;
	if (this->root == NULL)
	{
		cout << "������������������ �����..." << endl;
		return;
	};

	//������� ������� ������������������
	Node *Temp = Head;

	while (Temp)
	{
		cout << Temp->key << ' ';
		Temp = Temp->GetNextNode();
	};

	cout << endl;
};

