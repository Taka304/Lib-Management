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
using namespace std;
int main()
{
	/*FILE* f = fopen("borrowbook.csv", "a+");
	bobInfo b, c;
	createBoBook(b);
	addBorrowBook(b, f);
	fclose(f);
	FILE* f2 = fopen("borrowbook.csv", "r");
	readBorrowBook(c, f2);
	BoBookOut(c);
	fclose(f2);*/
	userInfo b = Login();
	menuUser(b, b.permiss);
}
