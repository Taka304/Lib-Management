#pragma once
#include "reader.h"
#include "borrowBook.h"

struct babInfo
{
	char rID[MAX_RID];
	date borrowDate;
	date exBackDate;
	date reBackDate;
	int amount;
	ISBNList l;
	int lateDay;
	int lostCount;
	ISBNList lost;
	int fee;
	int money;
};

bool KiemTraNamNhuan(int nam);

int TinhChenhLechNgay(int ngay1, int thang1, int nam1, int ngay2, int thang2, int nam2);

int lostFee(bList l, ISBNList il);

bobNode* findBorrowByRId(bobList l, char* id);

bobNode* findBeforeBorrowByid(bobList l, char* id);

void deleteBorrow(bobList& l, char *id);

void ISBNLostList_in(ISBNList& l, int n);

void createBaBook(babInfo& b, bobInfo bo);

void backBookOut(babInfo b);
