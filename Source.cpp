#include<iostream>
#include "book.h"
#include "reader.h"

using namespace std;

//Len de dem book

struct bookType
{
	char type[50];
	int count;
};

struct btNode
{
	bookType info;
	btNode* next;
};

struct btList
{
	btNode* head;
};

btNode* createbookt(bookType a)
{
	btNode* p = new btNode[sizeof(btNode)];
	p->info = a;
	p->next = NULL;
	return p;
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

void typeIn(bList l, btList &b )
{
	readBList(l);
	for (bNode* p=l.head; p != NULL; p = p->next)
	{
		for (btNode* bt=b.head; bt != NULL; bt = bt->next)
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
				strcat(a.type, p->info.type);
				insertbtTail(b, a);
			}
		}
	}
}

//dem Len cua btList

//Len cua reader

void sexCount(rList r)
{
	readRList(r);
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
	cout << "Co " << countF << " doc gia nu";
	cout << "Co " << countM << " doc gia nam";
}

