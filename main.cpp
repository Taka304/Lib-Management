#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "borrowBook.h"
#include "user.h"
#include "backBook.h"

using namespace std;

void menuUser(userInfo &a, int per)
{
	if (per == 3)
	{
		menuAdmin(a);
	}
	else if (per == 2)
	{
		menuExpert(a);
	}
	else
	{
		menuManager(a);
	}
}
void menuBorrow()
{
	FILE* f = fopen("borrowbook.csv", "a+");
	bobInfo b, c;
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
using namespace std;
int main()
{
	/*userInfo b = Login();
	menuUser(b, b.permiss);*/
	//menuBorrow();
	menuBack();
}