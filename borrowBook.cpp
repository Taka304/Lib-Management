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
ISBNNode* createISBNNode(char* x)
{
	ISBNNode* node = new ISBNNode;
	strcpy(node->ISBN, x);
	node->next = NULL;
	return node;
}

//tao + them node id sach
void addISBN(ISBNList& l, char* x)
{
	ISBNNode* node = createISBNNode(x);
	if (l.head == NULL)
	{
		l.head = node;
		return;
	}
	ISBNNode* tail = findTailISBNList(l);
	tail->next = node;
}

//khoi tao danh sach phieu muon
void init_borrowLinkedList(bobList& l)
{
	l.head = NULL;
}

//tao node phieu muon
bobNode* createBorrowNode(bobInfo b)
{
	bobNode* temp = new bobNode;
	temp->info = b;
	temp->next = NULL;
	return temp;
}

//tim duoi borrow
bobNode* findTailBorrowList(bobList l)
{
	for (bobNode* p = l.head; p; p = p->next)
	{
		if (p->next == NULL)
		{
			return p;
		}
	}
	return NULL;
}

//them phieu muon vao danh sach
void addBorrow(bobList& l, bobInfo b)
{
	bobNode* node = createBorrowNode(b);
	if (l.head == NULL)
	{
		l.head = node;
		return;
	}
	bobNode* tail = findTailBorrowList(l);
	tail->next = node;
}

//Kiem tra ISBN
bool checkISBN(bobList l, char* id)
{
	for (bobNode* p = l.head; p; p = p->next)
	{
		for (ISBNNode* i = p->info.l.head; i; i = i->next)
		{
			if (strcmp(i->ISBN, id) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

//nhap danh sach id sach
void ISBNList_in(bobList l1, ISBNList& l, int n)
{
	for (int i = 0; i < n; i++)
	{
		char id[MAX_BID];
		cout << "Nhap id sach: ";
		cin >> id;
		while (checkISBN(l1, id))
		{
			cout << "Sach co ISBN tren da duoc muon." << endl;
			cout << "Nhap id sach: ";
			cin >> id;
		}
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
		cout << dem << ". " << p->ISBN << endl;
	}
}

//tao phieu muon
void createBoBook(bobInfo& b)
{
	cout << "Nhap ma doc gia: ";
	cin >> b.rID;
	cout << "Ngay thang nam muon sach: ";
	b.borrowDate = today();
	cout << "Ngay tra du kien: ";
	cin >> b.exBackDate.day;
	cin >> b.exBackDate.month;
	cin >> b.exBackDate.year;
	init_ISBNList(b.l);
	cout << "Nhap so luong sach muon: ";
	cin >> b.amount;
	ISBNList_in(b.l, b.amount);
}

//tim duoi ISBN list
ISBNNode* findTailISBNList(ISBNList l)
{
	for (ISBNNode* p = l.head; p; p = p->next)
	{
		if (p->next == NULL)
		{
			return p;
		}
	}
	return NULL;
}

//doc phieu muon tu file
void readBorrowBook(bobInfo& b, FILE* f)
{
	fscanf(f, "%[^,]", b.rID);
	fgetc(f);
	readDate(f, b.borrowDate);
	fgetc(f);
	readDate(f, b.exBackDate);
	fgetc(f);
	fscanf(f, "%d", &b.amount);
	fgetc(f);
	init_ISBNList(b.l);
	for (int i = 0; i < b.amount; i++)
	{
		char id[MAX_BID];
		fscanf(f, "%[^,]", id);
		fgetc(f);
		addISBN(b.l, id);
	}
}

//ghi phieu muon vao file
void addBorrowBook(bobInfo b, FILE* f)
{
	fprintf(f, "%s,%d/%d/%d,%d/%d/%d,%d", b.rID, b.borrowDate, b.exBackDate, b.amount);
	for (ISBNNode* p = b.l.head; p; p = p->next)
	{
		fprintf(f, ",%s", p->ISBN);
	}
	fprintf(f, "\n");
}

//in phieu muon
void BoBookOut(bobInfo b)
{
	cout << "Ma doc gia: " << b.rID << endl;
	cout << "Ngay muon sach: " << b.borrowDate.day << "/" << b.borrowDate.month << "/" << b.borrowDate.year << endl;
	cout << "Ngay tra du kien: " << b.exBackDate.day << "/" << b.exBackDate.month << "/" << b.exBackDate.year << endl;
	cout << "So luong sach muon: " << b.amount << endl;
	cout << "Danh sach sach muon: ";
	ISBNList_out(b.l);
}