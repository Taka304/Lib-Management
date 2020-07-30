#pragma once
#include "reader.h"
#define MAX_RID 10
#define MAX_BID 9
#define DATE 11

struct ISBNNode
{
	char ISBN[MAX_BID];
	ISBNNode* next;
};
struct ISBNList
{
	ISBNNode* head;
};
struct bobInfo
{
	char rID[MAX_RID];
	date borrowDate;
	date exBackDate;
	int amount;
	ISBNList l;
};
struct bobNode
{
	bobInfo info;
	bobNode* next;
};
struct bobList
{
	bobNode* head;
};

void init_ISBNList(ISBNList& l);

ISBNNode* createISBNNode(char* x);

void addISBN(ISBNList& l, char* x);

void init_borrowLinkedList(bobList& l);

bobNode* createBorrowNode(bobInfo b);

bobNode* findTailBorrowList(bobList l);

void addBorrow(bobList& l, bobInfo b);

bool checkISBN(bobList l, char* id);

void ISBNList_in(bobList l1, ISBNList& l, int n);

void ISBNList_out(ISBNList l);

void createBoBook(bobInfo& b);

ISBNNode* findTailISBNList(ISBNList l);

void readBorrowBook(bobInfo& b, FILE* f);

void addBorrowBook(bobInfo b, FILE* f);

void BoBookOut(bobInfo b);
