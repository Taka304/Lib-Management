#pragma once
#define MAX_RID 10
#define MAX_RNAME 50
#define MAX_REMAIL 50
#define MAX_RCMND 13
#define MAX_RADDRESS 250
#define MAX_RSEX 4

struct date
{
	int day;
	int month;
	int year;
};

struct readersInfo
{
	char ID[MAX_RID];
	char fullname[MAX_RNAME];
	char cmnd[MAX_RCMND];
	date bDay;
	int sex;
	char email[MAX_REMAIL];
	char address[MAX_RADDRESS];
	date createdDay;
	date exDay;
};

struct rNode
{
	readersInfo info;
	rNode* next;
};

struct rList
{
	rNode* head;
};
void init_rList(rList& l);
rNode* createReader(readersInfo a);
int FindrX(char i[], rList l);
int rLen(rList L);
void deleterHead(rList& d);
void deleterTail(rList& d);
void deleterAt(rList& L, int k);
date today();
date expDay();
void insertrTail(rList& l, readersInfo a);
void readDate(FILE* filename, date& a);
void read1Reader(FILE* f, readersInfo& r);
void readRList(rList& l);
void infoOut(readersInfo r);
void readerListout(rList l);
void infoIn(readersInfo& r);
void writeDate(FILE* f, date a);
void write1Reader(FILE* f, readersInfo& r);
void toStr(int n, readersInfo r);
void insertReader(readersInfo& r, rList& l);
void insertReader(readersInfo& r, rList& l);
void deleteReader(rList& l);
void FindCMND(rList& l);
void changeInfodisplay();
void changeInfo(readersInfo& r);
void changeInfobyID(rList& l);
void FindBookByName(rList l, rList& l2);
void NameByIdOut(rList l);
void bookOut(rList l, int i);

void menu2Display();

void menu2Option();