#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

struct node
{
	int info;
	struct node* pNext;
	struct node* pPrev;
};
typedef struct node NODE;
struct list
{
	NODE* pHead;
	NODE* pTail;
};
typedef struct list LIST;

void Init(LIST&);
bool IsEmpty(LIST);
NODE* GetNode(int);
void AddTail(LIST&, NODE*);
bool Inp(LIST&, string, int);
NODE* NodeAdr(LIST, int);
void MergeSort(LIST, int, int);
void Merge(LIST, int, int, int); 
int NodeCount(LIST);
void Outp(LIST);
bool Outp(LIST, string);

int main()
{
	cout << "Project K06" << endl;
	LIST l;
	for (int i = 1; i <= 13; i++)
	{
		string filename = "intdata";
		if (i < 10)
			filename += '0';
		filename += to_string(i);
		string filenameinp = filename;
		filenameinp += ".inp";
		if (Inp(l, filenameinp, i) == true)
		{
			MergeSort(l, 0, NodeCount(l) - 1);
			string filenameout = filename;
			filenameout += ".outp";
			Outp(l, filenameout);
			cout << "\nImport	" << filenameinp << "	successfully!";
			cout << "\nExport	" << filenameout << "	successfully!" << endl;
		}
		else cout << "\nCan't open the file " << filename << "\n";
	}
	return 1;
}

void Init(LIST& l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}
bool IsEmpty(LIST l)
{
	if (l.pHead == NULL)
		return true;
	return false;
}
NODE* GetNode(int x)
{
	NODE* p = new NODE;
	if (p == NULL)
		return NULL;
	p->info = x;
	p->pNext = NULL;
	p->pPrev = NULL;
	return p;
}
void AddTail(LIST& l, NODE* p)
{
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
	{
		l.pTail->pNext = p;
		p->pPrev = l.pTail;
		l.pTail = p;
	}
}

bool Inp(LIST& l, string filename, int i)
{
	ifstream fi(filename);
	if (fi.fail() == true)
		return false;
	int n;
	int x{};
	fi >> n;
	Init(l);
	for (int i = 1; i <= n; i++)
	{
		fi >> x;
		NODE* p = GetNode(x);
		if (p != NULL)
			AddTail(l, p);
	}
	return true;
}

NODE* NodeAdr(LIST l, int vt)
{
	int counter = 0;
	NODE* p = l.pHead;
	while (counter != vt)
	{
		counter++;
		p = p->pNext;
	}
	return p;
}

void MergeSort(LIST l, int Left, int Right)
{
	if (Left < Right)
	{
		int Mid = Left + (Right - Left) / 2;
		MergeSort(l, Left, Mid);		
		MergeSort(l, Mid + 1, Right);
		Merge(l, Left, Mid, Right);		
	}
}

void Merge(LIST l, int Left, int Mid, int Right)
{
	int* temp = new int[Right - Left + 1];
	int p = 0;
	NODE* MidNode = NodeAdr(l, Mid);
	NODE* RightNode = NodeAdr(l, Right);
	NODE* i = NodeAdr(l, Left);		
	NODE* j = NodeAdr(l, Mid + 1);	
	while (!(i == MidNode->pNext && j == RightNode->pNext))
	{
		if ((i != MidNode->pNext && j != RightNode->pNext && i->info < j->info) || j == RightNode->pNext)
		{
			temp[p++] = i->info;
			i = i->pNext;
		}
		else
		{
			temp[p++] = j->info;
			j = j->pNext;
		}
	}
	i = NodeAdr(l, Left);
	for (int o = 0; o < p; o++)
	{
		i->info = temp[o];
		i = i->pNext;
	}
	delete[]temp;
}
int NodeCount(LIST l)
{
	int counter = 0;
	NODE* p = l.pHead;
	while (p != NULL)
	{
		counter++;
		p = p->pNext;
	}
	return counter;
}
void Outp(LIST l)
{
	NODE* p = l.pHead;
	while (p != NULL)
	{
		cout << setw(5) << p->info;
		p = p->pNext;
	}
	cout << ".";
}
bool Outp(LIST l, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return false;
	fo << setw(5) << NodeCount(l) << endl;
	NODE* p = l.pHead;
	while (p != NULL)
	{
		fo << setw(5) << p->info;
		p = p->pNext;
	}
	return true;
}