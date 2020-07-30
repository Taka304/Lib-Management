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


void init_BTList(btList& l);

btNode* createbookt(bookType a);

int bookCount(bList l);

void insertbtTail(btList& l, bookType a);

int btLen(btList L);

void bookTypeCount(bList l, btList& b);

void bookTypeList(btList l);

int readerCount(rList l);

void sexCount(rList r);

int countBorrowBook(bobList& l);

void lateReader(bobList l);