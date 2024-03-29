#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include "borrowBook.h"
#include "user.h"
#include "backBook.h"
#include "reader.h"
#include "book.h"
#include "satistic.h"
#include "menu.h"

using namespace std;

void menuBorrow()
{
	FILE* f = fopen("borrowbook.csv", "a+");
	bobInfo b;
	createBoBook(b, f);
	addBorrowBook(b, f);
	/*bobList l;
	init_borrowLinkedList(l);
	readBorrowBook(l, f);
	BorrowListOut(l);*/
	fclose(f);
}

void menuBack()
{
	FILE* f = fopen("borrowbook.csv", "r");
	char rId[MAX_RID];
	cout << "Nhap ma doc gia tra sach: ";
	cin >> rId;
	bobList l;
	init_borrowLinkedList(l);
	readBorrowBook(l, f);
	fclose(f);
	bobNode* temp = findBorrowByRId(l, rId);
	babInfo ba;
	createBaBook(ba, temp->info);
	backBookOut(ba);
	f = fopen("borrowbook.csv", "w");
	deleteBorrow(l, rId, f);
	fclose(f);
}

void menuReaderDisplay()
{
	cout << "Nhan 1 de xem danh sach doc gia trong thu vien" << endl;
	cout << "Nhan 2 de them doc gia" << endl;
	cout << "Nhan 3 de chinh sua thong tin doc gia" << endl;
	cout << "Nhan 4 de xoa thong tin doc gia" << endl;
	cout << "Nhan 5 de tim kiem doc gia theo CMND" << endl;
	cout << "Nhan 6 de tim kiem sach theo ho ten" << endl;
	cout << "Nhan 0 de tro lai menu" << endl;
	cout << "Lua chon cua ban: ";
}

void menuReader()
{
	int option;
	do
	{
		rList l;
		system("cls");
		menuReaderDisplay();
		cin >> option;
		switch (option)
		{
		case 1:
		{
			readRList(l);
			readerListout(l);
			cout << "Nhan bat ky de quay tro lai";
			system("pause");
			break;
		}
		case 2:
		{
			readRList(l);
			readersInfo a;
			insertReader(a, l);
			cout << "Nhap thanh cong!" << endl;
			cout << "Nhan bat ky de quay tro lai";
			system("pause");
			break;
		}
		case 3:
		{
			changeInfobyID(l);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			readRList(l);
			deleteReader(l);
			cout << "Nhan bat ky de quay tro lai";
			system("pause");
			break;
		}
		case 5:
		{
			readRList(l);
			FindCMND(l);
			cout << "Nhan bat ky de quay tro lai";
			system("pause");
			break;
		}
		case 6:
		{
			rList l1, l2;
			init_rList(l1);
			init_rList(l2);
			readRList(l1);
			FindBookByName(l1, l2);
			int leng = rLen(l2);
			if (leng == 1)
			{
				bookOut(l2, l2.head->info.ID);
			}
			else
			{
				NameByIdOut(l2);
				char id[MAX_RID];
				cout << "Nhap ma doc gia ban chon: ";
				cin >> id;
				bookOut(l2, id);
			}
			cout << "Nhan bat ky de quay tro lai";
			system("pause");
			break;
		}
		case 0:
		{
			return;
			break;
		}
		}
	} while (option >= 0 && option <= 6);
	return;
}

void menuBookDisplay()
{
	cout << "Nhan 1 de xem danh sach cac sach trong thu vien" << endl;
	cout << "Nhan 2 de them sach" << endl;
	cout << "Nhan 3 de chinh sua thong tin sach" << endl;
	cout << "Nhan 4 de xoa thong tin sach" << endl;
	cout << "Nhan 5 de tim kiem sach theo ISBN" << endl;
	cout << "Nhan 6 de tim kiem sach theo ten" << endl;
	cout << "Nhan 0 de tro lai menu" << endl;
	cout << "Lua chon cua ban: ";
}

void menuBook()
{
	int option;
	do
	{
		bList b;
		system("cls");
		menuBookDisplay();
		cin >> option;
		switch (option)
		{
		case 1:
		{
			readBList(b);
			readebListout(b);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 2:
		{
			readBList(b);
			bookInfo a;
			insertBook(a);
			cout << "Nhap thanh cong!" << endl;
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			changeInfobyISBN(b);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			readBList(b);
			deleteBook(b);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 5:
		{
			readBList(b);
			FindISBN(b);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 6:
		{
			readBList(b);
			FindBookByName(b);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 0:
		{
			return;
			break;
		}
		}
	} while (option >= 0 && option <= 6);
	return;
}

void menuBookDisplayForExpert()
{
	cout << "Nhan 1 de tim kiem sach theo ISBN" << endl;
	cout << "Nhan 2 de tim kiem sach theo ten" << endl;
	cout << "Nhan 0 de tro lai menu" << endl;
	cout << "Lua chon cua ban: ";
}

void menuBookForExpert()
{
	int option;
	do
	{
		bList b;
		system("cls");
		menuBookDisplayForExpert();
		cin >> option;
		switch (option)
		{

		case 1:
		{
			readBList(b);
			FindISBN(b);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 2:
		{
			readBList(b);
			FindBookByName(b);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 0:
		{
			return;
		}
		}
	} while (option >= 0 && option <= 2);
	return;
}

void menuSatisticDisplay()
{
	cout << "Nhan 1 de thong ke luong sach trong thu vien" << endl;
	cout << "Nhan 2 de thong ke luong sach theo the loai" << endl;
	cout << "Nhan 3 de thong ke so luong doc gia" << endl;
	cout << "Nhan 4 de thong ke so luong doc gia theo gioi tinh" << endl;
	cout << "Nhan 5 de thong ke so sach dang duoc muon" << endl;
	cout << "Nhan 6 de thong ke danh sach doc gia bi tre han" << endl;
	cout << "Nhan 0 tro lai menu" << endl;
	cout << "Lua chon cua ban: ";
}

void menuSatistic()
{
	int option;
	do
	{
		int dem;
		bList bl;
		rList rl;
		system("cls");
		menuSatisticDisplay();
		cin >> option;
		switch (option)
		{
		case 1:
		{
			readBList(bl);
			dem = bookCount(bl);
			cout << "Co " << dem << " quyen sach trong thu vien" << endl;
			cout << "Nhan bat ky de quay tro lai"<<endl;
			system("pause");
			break;
		}
		case 2:
		{
			btList bt;
			init_BTList(bt);
			readBList(bl);
			bookTypeCount(bl, bt);
			cout << "Thong ke sach theo the loai: " << endl;
			bookTypeList(bt);
			cout << "Nhan bat ky de quay tro lai";
			system("pause");
			break;
		}
		case 3:
		{
			readRList(rl);
			dem = readerCount(rl);
			cout << "Co " << dem << " doc gia trong thu vien" << endl;
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			readRList(rl);
			sexCount(rl);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 5:
		{
			bobList l;
			int count = countBorrowBook(l);
			cout << "So sach dang duoc muon la: " << count << endl;
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 6:
		{
			bobList l;
			FILE* f = fopen("borrowbook.csv", "r");
			if (!f)
			{
				cout << "Khong mo duoc.";
				return;
			}
			init_borrowLinkedList(l);
			readBorrowBook(l, f);
			fclose(f);
			lateReader(l);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 0:
		{
			return;
		}
		}
	} while (option >= 0 && option <= 6);
}

void menuSatisticDisplayForExpert()
{
	cout << "Nhan 1 de thong ke so sach dang duoc muon" << endl;
	cout << "Nhan 2 de thong ke danh sach doc gia bi tre han" << endl;
	cout << "Nhan bat ky de tro lai menu" << endl;
	cout << "Lua chon cua ban: ";
}

void menuSatisticForExpert()
{
	int option;
	do
	{
		system("cls");
		menuSatisticDisplayForExpert();
		cin >> option;
		switch (option)
		{
		case 1:
		{

			bobList l;
			int count = countBorrowBook(l);
			cout << "So sach dang duoc muon la: " << count << endl;
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 2:
		{
			bobList l;
			FILE* f = fopen("borrowbook.csv", "r");
			if (!f)
			{
				cout << "Khong mo duoc.";
				return;
			}
			init_borrowLinkedList(l);
			readBorrowBook(l, f);
			fclose(f);
			lateReader(l);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		}
	} while (option > 0 && option <= 2);
}

void menuFuncDisplay()
{
	cout << "Nhan 1 de thuc hien chuc nang 1" << endl;
	cout << "Nhan 2 de thuc hien chuc nang 2" << endl;
	cout << "Nhan 3 de thuc hien chuc nang 3" << endl;
	cout << "Nhan 4 de thuc hien chuc nang 4" << endl;
	cout << "Nhan 5 de thuc hien chuc nang 5" << endl;
	cout << "Nhan 6 de thuc hien chuc nang 6" << endl;
	cout << "Nhan 0 de thoat" << endl;
	cout << "Lua chon cua ban: ";
}

void menuReaderDisplayForExpert()
{
	cout << "Nhan 1 de xem danh sach doc gia trong thu vien" << endl;
	cout << "Nhan 2 de them doc gia" << endl;
	cout << "Nhan 3 de chinh sua thong tin doc gia" << endl;
	cout << "Nhan 4 de tim kiem doc gia theo CMND" << endl;
	cout << "Nhan 5 de tim kiem sach theo ho ten" << endl;
	cout << "Nhan bat ky de tro lai menu" << endl;
	cout << "Lua chon cua ban: ";
}

void menuReaderForExpert()
{
	int option;
	do
	{
		rList l;
		system("cls");
		menuReaderDisplayForExpert();
		cin >> option;
		switch (option)
		{
		case 1:
		{
			readRList(l);
			readerListout(l);
			cout << "Nhan bat ky de quay tro lai";
			system("pause");
			break;
		}
		case 2:
		{
			readRList(l);
			readersInfo a;
			insertReader(a, l);
			cout << "Nhap thanh cong!" << endl;
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			changeInfobyID(l);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			readRList(l);
			FindCMND(l);
			cout << "Nhan bat ky de quay tro lai" << endl;
			system("pause");
			break;
		}
		case 5:
		{
			rList l1, l2;
			init_rList(l1);
			init_rList(l2);
			readRList(l1);
			FindBookByName(l1, l2);
			int leng = rLen(l2);
			if (leng == 1)
			{
				bookOut(l2, l2.head->info.ID);
			}
			else
			{
				NameByIdOut(l2);
				char id[MAX_RID];
				cout << "Nhap ma doc gia ban chon: ";
				cin >> id;
				bookOut(l2, id);
			}
			cout << "Nhan bat ky de quay tro lai";
			system("pause");
			break;
		}
		}
	} while (option > 0 && option <= 5);
}

void menuDisplay(userInfo& a, int per)
{
	if (per == 3)
	{
		int optionA = 0;
		do
		{
			system("cls");
			menuFuncDisplay();
			cin >> optionA;
			switch (optionA)
			{
			case 1:
			{
				menuUAdmin(a);
				break;
			}
			case 2:
			{
				menuReader();
				break;
			}
			case 3:
			{
				menuBook();
				break;
			}
			case 4:
			{
				menuBorrow();
				break;
			}
			case 5:
			{
				menuBack();
				break;
			}
			case 6:
			{
				menuSatistic();
				break;
			}
			case 0:
			{
				return;
			}
			}
		} while (optionA >= 0 && optionA <= 6);
	}
	else if (per == 2)
	{
		int optionE;
		do
		{
			system("cls");
			menuFuncDisplay();
			cin >> optionE;
			switch (optionE)
			{
			case 1:
			{
				menuUExpert(a);
				break;
			}
			case 2:
			{
				menuReaderForExpert();
				break;
			}
			case 3:
			{
				menuBookForExpert();
				break;
			}
			case 4:
			{
				menuBorrow();
				break;
			}
			case 5:
			{
				menuBack();
				break;
			}
			case 6:
			{
				menuSatisticForExpert();
				break;
			}
			case 0:
			{
				return;
			}
			}
		} while (optionE >= 0 && optionE <= 6);
	}
	else
	{
		int optionM;
		do
		{
			system("cls");
			menuFuncDisplay();
			cin >> optionM;
			switch (optionM)
			{
			case 1:
			{
				menuUManager(a);
				break;
			}
			case 2:
			{
				menuReader();
				break;
			}
			case 3:
			{
				menuBook();
				break;
			}
			case 4:
			{
				menuBorrow();
				break;
			}
			case 5:
			{
				menuBack();
				break;
			}
			case 6:
			{
				menuSatistic();
				break;
			}
			case 0:
			{
				return;
			}
			}
		} while (optionM >= 0 && optionM <= 6);
	}
	if (per == 0)
		return;
}

void menuLogin()
{
	int option = -1;
	while (option != 0)
	{
		system("cls");
		cout << "Nhan 1 de dang nhap." << endl;
		cout << "Nhan 0 de thoat." << endl;
		cout << "Lua chon cua ban: ";
		cin >> option;
		switch (option)
		{
		case 1:
		{
			system("cls");
			userInfo b = Login();
			system("pause");
			menuDisplay(b, b.permiss);
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
}

