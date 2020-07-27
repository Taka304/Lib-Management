#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h> 
#include <ctype.h> 
#include "user.h"
using namespace std;

// tao danh sach user
void init_uList(uList& l)
{
	l.head = NULL;
}
// tim duoi cua danh sach
uNode* findTail(uList& l)
{
	for (uNode* p = l.head; p; p = p->next)
	{
		if (p->next == NULL)
		{
			return p;
		}
	}
	return NULL;
}

//them user vao cuoi danh sach
void addTail(uList& l, userInfo u)
{
	uNode* temp = createUserNode(u);
	if (l.head == NULL)
	{
		l.head = temp;
		return;
	}
	uNode* tail = findTail(l);
	tail->next = temp;
}
// tao node user
uNode* createUserNode(userInfo x)
{
	uNode* p = new uNode;
	p->info = x;
	p->next = NULL;
	return p;
}
// doc 1 user tu file
void read1userInfo(FILE *f, userInfo &u, int &dem)
{
	userInfo* temp = &u;
	dem = fread(temp, sizeof(userInfo), 1, f);
	fclose(f);
}
//doc danh sach user tu file
void readUserFile(uList& l)
{
	FILE* fp = fopen("account.txt", "rb");
	if (fp == NULL)
	{
		return;
	}
	init_uList(l);
	int dem;
	do
	{
		userInfo p;
		read1userInfo(fp, p, dem);
		addTail(l, p);
	} while (dem != 0);
	fclose(fp);
}
//Ghi danh sach vao file
void writeList(uList l)
{
	FILE* fp = fopen("account.txt", "wb");
	if (!fp)
	{
		return;
	}
	for (uNode* p = l.head; p; p = p->next)
	{
		if (p->next == NULL)
		{
			fclose(fp);
			return;
		}
		userInfo* temp = &p->info;
		fwrite(temp, sizeof(userInfo), 1, fp);
	}
}
//Lay node tu danh sach
uNode* takeNode(uList &l)
{
	if (l.head == NULL)
	{
		return NULL;
	}
	uNode* temp = l.head;
	l.head = l.head->next;
	return temp;
}
//Kiem tra ten dang nhap va mat khau
bool checkUserName_Pass(userInfo a)
{
	uList l;
	readUserFile(l);
	while (l.head != NULL)
	{
		uNode* temp = takeNode(l);
		if (strcmp(temp->info.userName, a.userName) == 0 && strcmp(temp->info.passWord, a.passWord) == 0)
		{
			return true;
		}
	}
	return false;
}
//Kiem tra ten dang nhap
bool checkUser(userInfo a)
{
	uList l;
	readUserFile(l);
	while (l.head != NULL)
	{
		uNode* temp = takeNode(l);
		if (strcmp(temp->info.userName, a.userName))
		{
			return true;
		}
	}
	return false;
}
void insertPassword(userInfo& a) //Nhap mat khau duoi dang '*'
{
	int ch;
	int i = 0;
	cout << "Mat khau: ";
	fflush(stdout);
	while ((ch = _getch()) != EOF && ch != '\n' && ch != '\r')
	{
		if (ch == '\b' && i > 0)
		{
			printf("\b \b");
			fflush(stdout);
			i--;
			a.passWord[i] = '\0';
		}
		else if (isalnum(ch))
		{
			putchar('*');
			a.passWord[i++] = (char)ch;
		}
	}
	a.passWord[i++] = '\0';
	cout << endl;
}
userInfo Login()
{
	userInfo a;
	cout << "Nhap ten tai khoan va mat khau:" << endl;
	cout << "Tai khoan: ";
	cin >> a.userName;
	insertPassword(a);
	while (!checkUserName_Pass(a))
	{
		cout << "Sai tai khoan hoac mat khau, moi nhap lai:" << endl;
		cout << "Nhap ten tai khoan va mat khau:" << endl;
		cout << "Tai khoan: ";
		cin >> a.userName;
		insertPassword(a);
	}
	cout << "Chao mung ban." << endl;
	return a; //Them menu co quyen su dung sau
}
// doi mat khau
void ChangePassword(userInfo a, char* np)
{
	uList l;
	readUserFile(l);
	for (uNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.userName, a.userName) == 0)
		{
			strcpy(p->info.passWord, np);
		}
	}
	writeList(l);
}
//Tao nguoi dung
userInfo createUser()
{
	userInfo a;
	cout << "Nhap ten: ";
	cin >> a.userName;
	cout << "Nhap mat khau: ";
	cin >> a.passWord;
	cout << "Nhap ho va ten: ";
	cin >> a.fullName;
	cout << "Nhap ngay sinh (DD/MM/YYYY): ";
	cin >> a.birthDay;
	cout << "Nhap CMND: ";
	cin >> a.identityID;
	cout << "Nhap dia chi: ";
	cin >> a.address;
	cout << "Nhap gioi tinh: ";
	cin >> a.sex;
	cout << "Nhap phan quyen: ";
	cin >> a.permiss;
	cout << "Nhap tinh trang: ";
	cin >> a.status;
	while (checkUser(a))
	{
		cout << "Ten dang nhap da duoc su dung, moi nhap ten khac:" << endl;
		cout << "Nhap ten: ";
		cin >> a.userName;
		cout << "Nhap mat khau: ";
		cin >> a.passWord;
		cout << "Nhap ho va ten: ";
		cin >> a.fullName;
		cout << "Nhap ngay sinh (DD/MM/YYYY): ";
		cin >> a.birthDay;
		cout << "Nhap CMND: ";
		cin >> a.identityID;
		cout << "Nhap dia chi: ";
		cin >> a.address;
		cout << "Nhap gioi tinh: ";
		cin >> a.sex;
		cout << "Nhap phan quyen: ";
		cin >> a.permiss;
		cout << "Nhap tinh trang: ";
		cin >> a.status;
	}
	return a;
}
//Them nguoi dung vao file
void addUserToFile(userInfo a)
{
	FILE* f = fopen("account.txt", "ab");
	if (!f)
	{
		return;
	}
	userInfo* b = &a;
	fwrite(b, sizeof(userInfo), 1, f);
	fclose(f);
}
bool checkPassWord(userInfo a, char* p)
{
	if (strcmp(a.passWord,p))
		return true;
	return false;
}
void changeInfo(userInfo a)
{
	int cases = -1;
	while (cases != 0)
	{
		cout << "Chon thong tin ban muon thay doi: " << endl;
		cout << "1. Mat khau." << endl;
		cout << "2. Ho va ten." << endl;
		cout << "3. Ngay sinh." << endl;
		cout << "4. CMND." << endl;
		cout << "5. Dia chi." << endl;
		cout << "6. Gioi tinh" << endl;
		cout << "0. Thoat." << endl;
		cout << "Nhap lua chon: ";
		cin >> cases;
		switch (cases)
		{
			case 1:
			{
				char op[MAX_PASSWORD + 1], np[MAX_PASSWORD + 1];
				cout << "Xac nhan mat khau cu:" << endl;
				cout << "Nhap mat khau cu: ";
				cin >> op;
				if (checkPassWord(a, op))
				{
					cout << "Nhap mat khau moi: " << endl;
					cin >> np;
					ChangePassword(a, np);
				}
				while (!checkPassWord(a, op))
				{
					cout << "Mat khau sai, moi nhap lai." << endl;
					cin >> op;
				}
				cout << "Nhap mat khau moi: " << endl;
				cin >> np;
				ChangePassword(a, np);
			}
			case 2:
			{

			}
		}
	}
}
void menuAdmin()
{
	//
}
void menuManager()
{
	//
}
void menuExpert()
{
	//
}
int main()
{
	userInfo a;
	a= createUser();
	addUserToFile(a);
	userInfo b = Login();
	char np[MAX_PASSWORD+1];
	cout << "Nhap mat khau moi: ";
	cin >> np;
	//ChangePassword(b, np);
	//Login();
}