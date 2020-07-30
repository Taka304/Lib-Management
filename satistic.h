#pragma once


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


btNode* createbookt(bookType a);

int bookCount(bList l);

void insertbtTail(btList& l, bookType a);

int btLen(btList L);

int bookTypeCount(bList l, btList& b);

int readerCount(rList l);

void sexCount(rList r);

int countBorrowBook(bobList l);

void lateReader(bobList l);
