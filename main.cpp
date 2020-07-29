#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "borrowBook.h"
#include "user.h"

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
	/*userInfo a;
	a = createUser();
	addUserToFile(a);*/
	userInfo b = Login();
	char np[MAX_PASSWORD];
	cout << "Nhap mat khau moi: ";
	cin >> np;
	ChangePassword(b, np);
	//Login();
}