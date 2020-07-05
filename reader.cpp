#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
using namespace std;

#define MAX_RID 10
#define MAX_RNAME 50
#define MAX_REMAIL 50
#define MAX_RCMND 10
#define MAX_RADDRESS 250

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
	rNode* prev;
};

struct rList
{
	rNode* head;
	rNode* tail;
};

//Tao ds doc gia
void init_rList(rList& l) 
{
	l.head = NULL;
	l.tail = NULL;
}

//Tao doc gia
rNode *createReader(readersInfo a)
{
	rNode* p = new rNode[sizeof(rNode)];
	p->info = a;
	p->next = NULL;
	p->prev = NULL;
	return p;
}

date today()
{
	time_t now= time(0);
	tm* lotm = localtime(&now);
	date today;
	today.day = lotm->tm_mday;
	today.month = lotm->tm_mon + 1;
	today.year = lotm->tm_year + 1900;
}

//Nhap doc gia vao cuoi danh sach
void insertTail(rList& l, readersInfo a)
{
	rNode* newReader = createReader(a);
	if (l.head == NULL)
	{
		l.head = newReader;
		l.tail = newReader;
		return;
	}
	else
	{
		l.tail->next = newReader;
		newReader->prev = l.tail;
		l.tail = newReader;
	}
}




