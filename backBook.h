#pragma once

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
	int fee;
	int money;
};

bool KiemTraNamNhuan(int nam);

int TinhChenhLechNgay(int ngay1, int thang1, int nam1, int ngay2, int thang2, int nam2);

int lostFee(bList l, ISBNList il);

void deleteBorrow(bobList& l);

void createBaBook(babInfo& b);
