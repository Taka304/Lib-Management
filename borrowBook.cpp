#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "borrowBook.h"
using namespace std;
//khoi tao danh sach id sach
void init_ISBNList(ISBNList& l)
{
	l.head = NULL;
}
//tao node id sach
ISBNNode * createISBNNode(char *x)
{
	ISBNNode* node = new ISBNNode;
	strcpy(node->ISBN,x);
	node->next = NULL;
	return node;
}
//them node id sach
void addISBN(ISBNList& l, char *x)
{
	ISBNNode* node = createISBNNode(x);
	if (l.head == NULL)
	{
		l.head = node;
		return;
	}
	for (ISBNNode* p = l.head; p; p = p->next)
	{
		if (p->next == NULL)
		{
			p->next = node;
			return;
		}
	}
}
//nhap danh sach id sach
void ISBNList_in(ISBNList& l, int n)
{
	for (int i = 0; i < n; i++)
	{
		char id[MAX_BID];
		cout << "Nhap id sach: ";
		cin >> id;
		addISBN(l, id);
	}
}
//xuat danh sach id sach
void ISBNList_out(ISBNList l)
{
	int dem = 0;
	for (ISBNNode* p = l.head; p; p = p->next)
	{
		dem++;
		cout << dem<<". "<<p->ISBN << endl;
	}
}
//tao phieu muon
void createBoBook(bobInfo& b)
{
	cout << "Nhap ma doc gia: ";
	cin >> b.rID;
	cout << "Nhap ngay muon sach: ";
	cin >> b.BoDate;
	cout << "Ngay tra du kien: ";
	cin >> b.exBackDate;
	init_ISBNList(b.l);
	int n;
	cout << "Nhap so luong sach muon: ";
	cin >> n;
	ISBNList_in(b.l, n);
}
//in phieu muon
void BoBookOut(bobInfo b)
{
	cout << "Ma doc gia: " << b.rID << endl;
	cout << "Ngay muon sach: " << b.BoDate << endl;
	cout << "Ngay tra du kien: " << b.exBackDate << endl;
	cout << "Danh sach sach muon: ";
	ISBNList_out(b.l);
}