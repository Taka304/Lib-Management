#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "borrowBook.h"
#include "reader.h"
#include "book.h"
#include "backBook.h"
using namespace std;


bool KiemTraNamNhuan(int nam)
{
	if (nam % 4 == 0)
	{
		if (nam % 100 == 0)
		{
			if (nam % 400 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

int TinhChenhLechNgay(int ngay1, int thang1, int nam1, int ngay2, int thang2, int nam2)
{
	int quynam1 = 0, quynam2 = 0, quythang1 = 0, quythang2 = 0, quyngay1, quyngay2, chenhlech;
	for (int i = 1; i < nam1; i++)
	{
		if (KiemTraNamNhuan(i) == true)
		{
			quynam1 = quynam1 + 366;
		}
		else
		{
			quynam1 = quynam1 + 365;
		}
	}
	for (int i = 1; i < nam2; i++)
	{
		if (KiemTraNamNhuan(i) == true)
		{
			quynam2 = quynam2 + 366;
		}
		else
		{
			quynam2 = quynam2 + 365;
		}
	}
	for (int i = 1; i < thang1; i++)
	{
		if (i == 2 && KiemTraNamNhuan(nam1) == true)
		{
			quythang1 = quythang1 + 29;
		}
		else if (i == 2 && KiemTraNamNhuan(nam1) == false)
		{
			quythang1 = quythang1 + 28;
		}
		else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
		{
			quythang1 = quythang1 + 31;
		}
		else
		{
			quythang1 = quythang1 + 30;
		}
	}
	for (int i = 1; i < thang2; i++)
	{
		if (i == 2 && KiemTraNamNhuan(nam2) == true)
		{
			quythang2 = quythang2 + 29;
		}
		else if (i == 2 && KiemTraNamNhuan(nam2) == false)
		{
			quythang2 = quythang2 + 28;
		}
		else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
		{
			quythang2 = quythang2 + 31;
		}
		else
		{
			quythang2 = quythang2 + 30;
		}
	}
	quyngay1 = ngay1 - 1;
	quyngay2 = ngay2 - 1;
	chenhlech = (quynam2 + quythang2 + quyngay2) - (quynam1 + quythang1 + quyngay1);
	return chenhlech;
}

//Kiem tra sach bi mat
int lostFee(bList l, ISBNList il)
{
	ISBNNode* p;
	bNode* a;
	for (p = il.head; p != NULL; p = p->next)
	{
		for (a = l.head; a != NULL; a = a->next)
		{
			if (strcmp(p->ISBN, a->info.ISBN) == 0)
				return (a->info.cost) * 2;
		}
	}
}

//Tim node phieu muon chua ma doc gia da cho
bobNode* findBorrowByRId(bobList l, char* id)
{
	for (bobNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.rID, id) == 0)
		{
			return p;
		}
	}
	return NULL;
}

//Tim node truoc node phieu muon chua ma doc gia da cho
bobNode* findBeforeBorrowByid(bobList l, char* id)
{
	for (bobNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->next->info.rID, id) == 0)
		{
			return p;
		}
	}
	return NULL;
}

//tra sach ve thu vien
void deleteBorrow(bobList& l, char* id, FILE* f)
{
	bobNode* temp1 = findBorrowByRId(l, id);
	bobNode* temp2 = findBeforeBorrowByid(l, id);
	temp2->next = temp1->next;
	temp1->next = NULL;
	delete temp1;
	addBorrowList(l, f);
}

//list sach mat
void ISBNLostList_in(ISBNList& l, int n)
{
	for (int i = 0; i < n; i++)
	{
		char id[MAX_BID];
		cout << "Nhap id sach: ";
		cin >> id;
		addISBN(l, id);
	}
}
//tao phieu tra
void createBaBook(babInfo& b, bobInfo bo)
{
	strcpy(b.rID, bo.rID);
	b.borrowDate = bo.borrowDate;
	b.exBackDate = bo.exBackDate;
	b.reBackDate = today();
	init_ISBNList(b.l);
	b.amount = bo.amount;
	b.l = bo.l;
	cout << "Nhap so luong sach bi mat: ";
	cin >> b.lostCount;
	init_ISBNList(b.lost);
	ISBNLostList_in(b.lost, b.lostCount);
	bList l;
	readBList(l);
	b.fee = 0;
	for (int i = 1; i <= b.lostCount; i++)
	{
		b.fee += lostFee(l, b.lost);
	}
	b.lateDay = TinhChenhLechNgay(b.exBackDate.day, b.exBackDate.month, b.exBackDate.year, b.reBackDate.day, b.reBackDate.month, b.reBackDate.year);
	b.money = b.lateDay * 5000 * b.amount + b.fee;
}

//in phieu tra
void backBookOut(babInfo b)
{
	cout << "Ma doc gia: " << b.rID << endl;
	cout << "Ngay muon sach: " << b.borrowDate.day << "/" << b.borrowDate.month << "/" << b.borrowDate.year << endl;
	cout << "Ngay tra sach du kien: " << b.exBackDate.day << "/" << b.exBackDate.month << "/" << b.exBackDate.year << endl;
	cout << "Ngay tra sach thuc te: " << b.reBackDate.day << "/" << b.reBackDate.month << "/" << b.reBackDate.year << endl;
	cout << "So luong sach muon: " << b.amount << endl;
	cout << "Danh sach sach muon: " << endl;
	ISBNList_out(b.l);
	cout << "So sach mat: " << b.lostCount << endl;
	cout << "Danh sach sach mat: " << endl;
	ISBNList_out(b.lost);
	cout << "So ngay tre han: " << b.lateDay << endl;
	cout << "So tien phai tra: " << b.money << endl;
}