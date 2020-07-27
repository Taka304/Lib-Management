#pragma once
#define MAX_RID 9
#define MAX_BID 9
#define DATE 11
struct date
{
	int day;
	int month;
	int year;
};
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
	char BoDate[DATE];
	char exBackDate[DATE];
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
void ISBNList_in(ISBNList& l, int n);
void createBoBook(bobInfo& b);
void ISBNList_out(ISBNList l);
void BoBookOut(bobInfo b);