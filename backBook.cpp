#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "borrowBook.h"
#include "reader.h"
using namespace std;

struct babInfo
{
	char rID[MAX_RID];
	date borrowDate;
	date exBackDate;
	date reBackDate;
	ISBNList l;
	int lateDay;
	//them vu mat sach nua roi cong tong tien lai
	int money;
};
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
//tao phieu tra
void createBaBook(babInfo& b)
{
	cout << "Nhap ma doc gia: ";
	cin >> b.rID;
	cout << "Nhap ngay, thang, nam muon sach: ";
	cin >> b.borrowDate.day;
	cin >> b.borrowDate.month;
	cin >> b.borrowDate.year;
	cout << "Ngay thang nam tra du kien: ";
	cin >> b.exBackDate.day;
	cin >> b.exBackDate.month;
	cin >> b.exBackDate.year;
	cout << "Ngay tra thuc te: ";
	cin >> b.reBackDate.day;
	cin >> b.reBackDate.month;
	cin >> b.reBackDate.year;
	ISBNList lBook;
	init_ISBNList(lBook);
	int n;
	cout << "Nhap so luong sach muon: ";
	cin >> n;
	ISBNList_in(lBook, n);
	int Late = TinhChenhLechNgay(b.exBackDate.day, b.exBackDate.month, b.exBackDate.year, b.reBackDate.day, b.reBackDate.month, b.reBackDate.year);
	int money = Late * 5000 * n;
}