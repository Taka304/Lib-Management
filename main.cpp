#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "borrowBook.h"
#include "user.h"

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
	/*bobInfo b, c;
	createBoBook(b, f);
	addBorrowBook(b, f);*/
	bobList l;
	init_borrowLinkedList(l);
	readBorrowBook(l, f);
	BorrowListOut(l);
	fclose(f);
}
using namespace std;
int main()
{
	/*userInfo b = Login();
	menuUser(b, b.permiss);*/
	menuBorrow();
}
