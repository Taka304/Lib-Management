#pragma once
#include "reader.h"
#define MAX_RID 9
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
void init_borrowLinkedList(bobList& l);
bobNode* createBorrowNode(bobInfo b);
bobNode* findTailBorrowList(bobList l);
void addBorrow(bobList& l, bobInfo b);
void init_ISBNList(ISBNList& l);
ISBNNode* createISBNNode(char* x);
void addISBN(ISBNList& l, char* x);
void ISBNList_in(ISBNList& l, int n);
void createBoBook(bobInfo& b);
void addBorrowBook(bobInfo b, FILE* f);
void ISBNList_out(ISBNList l);
void BoBookOut(bobInfo b);
void readBorrowBook(bobInfo& b, FILE* f);
ISBNNode* findTailISBNList(ISBNList l);
