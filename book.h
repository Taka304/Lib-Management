#pragma once
#define MAX_ISBN 9
#define MAX_BNAME 50
#define MAX_BAUTHOR 50
#define MAX_BNXB 50
#define MAX_BYEAR 5
#define MAX_BTYPE 20
#define MAX_BNUM 10
struct bookInfo
{
	char ISBN[MAX_ISBN];
	char fullname[MAX_BNAME];
	char author[MAX_BAUTHOR];
	char nxb[MAX_BNXB];
	char pYear[MAX_BYEAR];
	char type[MAX_BTYPE];
	int cost;
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
int FindbX(char i[], bList l);
int bLen(bList L);
void freebbook(bList L);
void deletebHead(bList& d);
void deletebTail(bList& d);
void deletebAt(bList& L, int k);
void insertbTail(bList& l, bookInfo a);
void read1Book(FILE* f, bookInfo& r);
void readBList(bList& l);
void infoBOut(bookInfo r);
void readebListout(bList l);
void infoBIn(bookInfo& r);
void write1book(FILE* f, bookInfo& r);
void insertBook(bookInfo& r);
void writeBList(bList& l);
void deleteBook(bList& l);
void FindISBN(bList& l);
void FindBookByName(bList& l);
void changebInfodisplay();
void changebInfo(bookInfo& r);
void changeInfobyISBN(bList& l);