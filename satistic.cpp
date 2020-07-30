#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "book.h"
#include "reader.h"
#include "borrowBook.h"
#include "backBook.h"
#include "satistic.h"

using namespace std;

//Len de dem book
void init_BTList(btList& l)
{
	l.head = NULL;
}

btNode* createbookt(bookType a)
{
	btNode* p = new btNode[sizeof(btNode)];
	p->info = a;
	p->next = NULL;
	return p;
}

//dem so sach trong thu vien
int bookCount(bList l)
{
	int count = bLen(l);
	return count;
}

void insertbtTail(btList& l, bookType a)
{
	btNode* newbook = createbookt(a);
	if (l.head == NULL)
	{
		l.head = newbook;
		return;
	}
	btNode* p = l.head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = newbook;
	return;
}

int btLen(btList L)
{
	btNode* PH = L.head;
	int i = 0;
	if (PH != NULL) i = 1;
	while (PH != NULL)
	{
		if (PH == NULL) break;
		PH = PH->next;
		i++;
	}
	return i;
}

void bookTypeCount(bList l, btList& b)
{
	for (bNode* p = l.head; p != NULL; p = p->next)
	{
		for (btNode* bt = b.head; bt != NULL; bt = bt->next)
		{
			if (strcmp(p->info.type, bt->info.type) == 0)
			{
				bt->info.count++;
				break;
			}
			else if (bt->next == NULL)
			{
				bookType a;
				a.count = 1;
				strcpy(a.type, p->info.type);
				insertbtTail(b, a);
			}
		}
	}
}

void bookTypeList(btList l)
{
	btNode* p;
	for (p = l.head; p; p = p->next)
	{
		cout << p->info.type << ": " << p->info.count << " quyen" << endl;
	}
}

//Len cua reader
int readerCount(rList l)
{
	int count = rLen(l);
	return count;
}

void sexCount(rList r)
{
	int countF = 0;
	int countM = 0;
	for (rNode* p = r.head; p != NULL; p = p->next)
	{
		if (p->info.sex == 1)
			countF++;
		else
		{
			countM++;
		}
	}
	cout << "Co " << countF << " doc gia nu" << endl;
	cout << "Co " << countM << " doc gia nam" << endl;
}

//so sach dang duoc muon
int countBorrowBook(bobList &l)
{
	FILE* f = fopen("borrowbook.csv", "r");
	if (!f)
	{
		cout << "Khong mo duoc.";
		return 0;
	}
	init_borrowLinkedList(l);
	readBorrowBook(l,f);
	fclose(f);
	int dem = 0;
	for (bobNode* p = l.head; p; p = p->next)
	{
		dem = dem + p->info.amount;
	}
	return dem;
}

//Danh sach doc gia tre hen
void lateReader(bobList l)
{
	FILE* f = fopen("borrowbook.csv", "r");
	if (!f)
	{
		cout << "Khong mo duoc.";
		return;
	}
	init_borrowLinkedList(l);
	readBorrowBook(l, f);
	fclose(f);
	date td = today();
	cout << "Danh sach doc gia tre han: " << endl;
	for (bobNode* p = l.head; p; p = p->next)
	{
		int late = TinhChenhLechNgay(td.day, td.month, td.year, p->info.exBackDate.day, p->info.exBackDate.month, p->info.exBackDate.year);
		if (late > 0)
		{
			cout << p->info.rID << endl;
		}
	}
}