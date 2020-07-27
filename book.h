#pragma once
#define MAX_BID 9
#define MAX_BNAME 50
#define MAX_BAUTHOR 50
#define MAX_BNXB 50
#define MAX_BYEAR 5
#define MAX_BTYPE 20
#define MAX_BCOST 10
#define MAX_BNUM 10
struct bookInfo
{
	char ID[MAX_BID];
	char fullname[MAX_BNAME];
	char author[MAX_BAUTHOR];
	char nxb[MAX_BNXB];
	char pYear[MAX_BYEAR];
	char type[MAX_BTYPE];
	char cost[MAX_BCOST];
	char num[MAX_BNUM];
};

struct bNode
{
	bookInfo info;
	bNode* next;
};

struct bList
{
	bNode* head;
};
void init_bList(bList& l);
bNode* createbook(bookInfo a);
int FindX(char i[], bList l);
int Len(bList L);
void freebook(bList L);
void deleteHead(bList& d);
void deleteTail(bList& d);
void deleteAt(bList& L, int k);
void insertTail(bList& l, bookInfo a);
void read1Book(FILE* f, bookInfo& r);
void readBList(bList& l);
void infoOut(bookInfo r);
void readebListout(bList l);
void infoIn(bookInfo& r);
void write1book(FILE* f, bookInfo& r);
void insertbook(bookInfo& r);
void writeRList(bList& l);
void deletebook(bList& l);
void FindID(bList& l);
void changeInfodisplay();
void changeInfo(bookInfo& r);
void changeInfobyID(bList& l);