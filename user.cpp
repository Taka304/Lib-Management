#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h> 
#include <ctype.h>
#include <string.h>
#include "user.h"
#include "reader.h"
using namespace std;

// tao danh sach user
void init_uList(uList& l)
{
	l.head = NULL;
}
// tim duoi cua danh sach
uNode* findTailuser(uList& l)
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
void addTailuser(uList& l, userInfo u)
{
	uNode* temp = createUserNode(u);
	if (l.head == NULL)
	{
		l.head = temp;
		return;
	}
	uNode* tail = findTailuser(l);
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
void read1userInfo(FILE* f, userInfo& u, int& dem)
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
	int dem = 1;
	while (dem != 0)
	{
		userInfo p;
		read1userInfo(fp, p, dem);
		addTailuser(l, p);
	}
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
uNode* takeNode(uList& l)
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
	init_uList(l);
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
bool checkUserName(userInfo a)
{
	uList l;
	init_uList(l);
	readUserFile(l);
	if (l.head == NULL)
	{
		return false;
	}
	while (l.head != NULL)
	{
		uNode* temp = takeNode(l);
		if (strcmp(temp->info.userName, a.userName) == 0)
		{
			return true;
		}
	}
	return false;
}
void insertPassword(char* pass) //Nhap mat khau duoi dang '*'
{
	int ch;
	int i = 0;
	fflush(stdout);
	while ((ch = _getch()) != EOF && ch != '\n' && ch != '\r')
	{
		if (ch == '\b' && i > 0)
		{
			printf("\b \b");
			fflush(stdout);
			i--;
			pass[i] = '\0';
		}
		else if (isalnum(ch))
		{
			putchar('*');
			pass[i++] = (char)ch;
		}
	}
	pass[i++] = '\0';
	cout << endl;
}

//tim doc gia tu ten dang nhap
userInfo findUserByUserName(uList l, char* uname)
{
	for (uNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.userName, uname) == 0)
		{
			return p->info;
		}
	}
}
userInfo Login()
{
	userInfo a;
	cout << "Nhap ten tai khoan va mat khau:" << endl;
	cout << "Tai khoan: ";
	cin >> a.userName;
	cout << "Mat khau: ";
	insertPassword(a.passWord);
	while (!checkUserName_Pass(a))
	{
		cout << "Sai tai khoan hoac mat khau, moi nhap lai:" << endl;
		cout << "Nhap ten tai khoan va mat khau:" << endl;
		cout << "Tai khoan: ";
		cin >> a.userName;
		cout << "Mat khau: ";
		insertPassword(a.passWord);
	}
	cout << "Chao mung ban." << endl;
	uList l;
	init_uList(l);
	readUserFile(l);
	a = findUserByUserName(l, a.userName);
	return a; //Them menu co quyen su dung sau
}
// doi mat khau
userInfo ChangePassword(userInfo a, char* np)
{
	uList l;
	init_uList(l);
	readUserFile(l);
	userInfo b;
	for (uNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.userName, a.userName) == 0)
		{
			strcpy(b.userName, p->info.userName);
			strcpy(b.passWord, np);
			strcpy(b.fullName, p->info.fullName);
			strcpy(b.identityID, p->info.identityID);
			b.birthDay.day = p->info.birthDay.day;
			b.birthDay.month = p->info.birthDay.month;
			b.birthDay.year = p->info.birthDay.year;
			strcpy(b.address, p->info.address);
			b.permiss = p->info.permiss;
			b.sex = p->info.sex;
			b.status = p->info.status;
			p->info = b;
		}
	}
	writeList(l);
	return b;
}
userInfo ChangeFullName(userInfo a, char* nname)
{
	uList l;
	init_uList(l);
	readUserFile(l);
	userInfo b;
	for (uNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.userName, a.userName) == 0)
		{
			strcpy(b.userName, p->info.userName);
			strcpy(b.passWord, p->info.passWord);
			strcpy(b.fullName, nname);
			strcpy(b.identityID, p->info.identityID);
			b.birthDay.day = p->info.birthDay.day;
			b.birthDay.month = p->info.birthDay.month;
			b.birthDay.year = p->info.birthDay.year;
			strcpy(b.address, p->info.address);
			b.permiss = p->info.permiss;
			b.sex = p->info.sex;
			b.status = p->info.status;
			p->info = b;
		}
	}
	writeList(l);
	return b;
}
void ChangeBirthDay(userInfo& a, date nb)
{
	uList l;
	init_uList(l);
	readUserFile(l);
	for (uNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.userName, a.userName) == 0)
		{
			a.birthDay = nb;
			p->info.birthDay = nb;
		}
	}
	writeList(l);
}
userInfo ChangeIdentity(userInfo a, char* ni)
{
	uList l;
	init_uList(l);
	readUserFile(l);
	userInfo b;
	for (uNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.userName, a.userName) == 0)
		{
			strcpy(b.userName, p->info.userName);
			strcpy(b.passWord, p->info.passWord);
			strcpy(b.fullName, p->info.fullName);
			strcpy(b.identityID, ni);
			b.birthDay.day = p->info.birthDay.day;
			b.birthDay.month = p->info.birthDay.month;
			b.birthDay.year = p->info.birthDay.year;
			strcpy(b.address, p->info.address);
			b.permiss = p->info.permiss;
			b.sex = p->info.sex;
			b.status = p->info.status;
			p->info = b;
		}
	}
	writeList(l);
	return b;
}
userInfo ChangeAddress(userInfo a, char* na)
{
	uList l;
	init_uList(l);
	readUserFile(l);
	userInfo b;
	for (uNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.userName, a.userName) == 0)
		{
			strcpy(b.userName, p->info.userName);
			strcpy(b.passWord, p->info.passWord);
			strcpy(b.fullName, p->info.fullName);
			strcpy(b.identityID, p->info.identityID);
			b.birthDay.day = p->info.birthDay.day;
			b.birthDay.month = p->info.birthDay.month;
			b.birthDay.year = p->info.birthDay.year;
			strcpy(b.address, na);
			b.permiss = p->info.permiss;
			b.sex = p->info.sex;
			b.status = p->info.status;
			p->info = b;
		}
	}
	writeList(l);
	return b;
}
void ChangeSex(userInfo& a)
{
	uList l;
	init_uList(l);
	readUserFile(l);
	for (uNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.userName, a.userName) == 0)
		{
			if (a.sex == 1)
			{
				a.sex = 2;
			}
			else
				a.sex = 1;
		}
	}
	writeList(l);
}
//Tao nguoi dung
userInfo createUser()
{
	userInfo a;
	cout << "Nhap ten dang nhap: ";
	cin >> a.userName;
	while (checkUserName(a))
	{
		cout << "Ten dang nhap da ton tai, moi chon ten dang nhap khac." << endl;
		cout << "Nhap ten dang nhap: ";
		cin >> a.userName;
	}
	cout << "Nhap mat khau: ";
	cin >> a.passWord;
	cout << "Nhap ho va ten: ";
	cin.ignore();
	cin.getline(a.fullName, sizeof(a.fullName));
	cout << "Nhap ngay sinh (DD/MM/YYYY): ";
	cin >> a.birthDay.day;
	cin >> a.birthDay.month;
	cin >> a.birthDay.year;
	cout << "Nhap CMND: ";
	cin >> a.identityID;
	cout << "Nhap dia chi: ";
	cin.ignore();
	cin.getline(a.address, sizeof(a.address));
	cout << "Nhap gioi tinh (1 la nu, 2 la nam): ";
	cin >> a.sex;
	cout << "Nhap phan quyen (1 la quan li, 2 la chuyen vien): ";
	cin >> a.permiss;
	cout << "Nhap tinh trang (1 la hoat dong, 2 la block): ";
	cin >> a.status;
	return a;
}

//Them nguoi dung vao file
void addUserToFile(userInfo a)
{
	FILE* f = fopen("account.txt", "ab+");
	if (!f)
	{
		cout << "Khong mo duoc.";
		return;
	}
	userInfo* b = &a;
	fwrite(b, sizeof(userInfo), 1, f);
	fclose(f);
}
bool checkPassWord(userInfo a, char* p)
{
	if (strcmp(a.passWord, p) == 0)
		return true;
	return false;
}
void changeInfo(userInfo &a)
{
	int cases = -1;
	while (cases != 0)
	{
		cout << "Chon thong tin ban muon thay doi: " << endl;
		cout << "1. Ho va ten." << endl;
		cout << "2. Ngay sinh." << endl;
		cout << "3. CMND." << endl;
		cout << "4. Dia chi." << endl;
		cout << "5. Gioi tinh" << endl;
		cout << "0. Thoat." << endl;
		cout << "Nhap lua chon: ";
		cin >> cases;
		switch (cases)
		{
		case 1:
		{
			char nname[MAX_NAME];
			cout << "Nhap ho va ten moi: ";
			cin.ignore();
			cin.getline(nname, sizeof(nname));
			a = ChangeFullName(a, nname);
			break;
		}
		case 2:
		{
			date nBirthDay;
			cout << "Nhap ngay thang nam sinh moi: ";
			cin >> nBirthDay.day;
			cin >> nBirthDay.month;
			cin >> nBirthDay.year;
			ChangeBirthDay(a, nBirthDay);
			break;
		}
		case 3:
		{
			char nidentity[MAX_CMND];
			cout << "Nhap CMND moi: ";
			cin >> nidentity;
			a = ChangeIdentity(a, nidentity);
			break;
		}
		case 4:
		{
			char naddress[MAX_ADDRESS];
			cout << "Nhap dia chi moi: ";
			cin.ignore();
			cin.getline(naddress, MAX_ADDRESS);
			a = ChangeAddress(a, naddress);
			break;
		}
		case 5:
		{
			ChangeSex(a);
		}
		case 0:
		{
			return;
		}
		}
	}
}

//in thong tin
void UserInfoOut(userInfo a)
{
	cout << "Ho va ten: " << a.fullName << endl;
	cout << "Ngay sinh: " << a.birthDay.day << "/" << a.birthDay.month << "/" << a.birthDay.year << endl;
	cout << "CMND: " << a.identityID << endl;
	cout << "Dia chi: " << a.address << endl;
	cout << "Gioi tinh: ";
	if (a.sex == 1)
	{
		cout << "Nu" << endl;
	}
	else if (a.sex == 2)
	{
		cout << "Nam" << endl;
	}
	cout << "Phan quyen: ";
	if (a.permiss == 1)
	{
		cout << "Quan li" << endl;
	}
	else if (a.permiss == 2)
	{
		cout << "Chuyen vien" << endl;
	}
	else if (a.permiss == 3)
	{
		cout << "Admin" << endl;
	}
}
void menuAdmin(userInfo &a)
{
	int cases = -1;
	while (cases != 0)
	{
		cout << "Chon chuc nang de thuc hien." << endl;
		cout << "1. Dang xuat." << endl;
		cout << "2. Doi mat khau." << endl;
		cout << "3. Cap nhat thong tin ca nhan." << endl;
		cout << "4. Tao nguoi dung + phan quyen nguoi dung." << endl;
		cout << "0. Thoat chuc nang." << endl;
		cout << "Chon chuc nang: ";
		cin >> cases;
		switch (cases)
		{
		case 1:
		{
			return;
		}
		case 2:
		{
			char op[MAX_PASSWORD], np[MAX_PASSWORD];
			cout << "Xac nhan mat khau cu:" << endl;
			cout << "Nhap mat khau cu: ";
			insertPassword(op);
			if (checkPassWord(a, op))
			{
				cout << "Nhap mat khau moi: " << endl;
				insertPassword(np);
				ChangePassword(a, np);
				break;
			}
			while (!checkPassWord(a, op))
			{
				cout << "Mat khau sai, moi nhap lai." << endl;
				insertPassword(op);
			}
			cout << "Nhap mat khau moi: " << endl;
			insertPassword(np);
			a = ChangePassword(a, np);
			break;
		}
		case 3:
		{
			changeInfo(a);
			break;
		}
		case 4:
		{
			userInfo b = createUser();
			addUserToFile(b);
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
}
void menuManager(userInfo &a)
{
	int cases = -1;
	while (cases != 0)
	{
		cout << "Chon chuc nang de thuc hien." << endl;
		cout << "1. Dang xuat." << endl;
		cout << "2. Doi mat khau." << endl;
		cout << "3. Cap nhat thong tin ca nhan." << endl;
		cout << "0. Thoat chuc nang." << endl;
		cout << "Chon chuc nang: ";
		cin >> cases;
		switch (cases)
		{
		case 1:
		{
			return;
		}
		case 2:
		{
			char op[MAX_PASSWORD], np[MAX_PASSWORD];
			cout << "Xac nhan mat khau cu:" << endl;
			cout << "Nhap mat khau cu: ";
			insertPassword(op);
			if (checkPassWord(a, op))
			{
				cout << "Nhap mat khau moi: " << endl;
				insertPassword(np);
				ChangePassword(a, np);
				break;
			}
			while (!checkPassWord(a, op))
			{
				cout << "Mat khau sai, moi nhap lai." << endl;
				insertPassword(op);
			}
			cout << "Nhap mat khau moi: " << endl;
			insertPassword(np);
			a = ChangePassword(a, np);
			break;
		}
		case 3:
		{
			changeInfo(a);
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
}
void menuExpert(userInfo &a)
{
	int cases = -1;
	while (cases != 0)
	{
		cout << "Chon chuc nang de thuc hien." << endl;
		cout << "1. Dang xuat." << endl;
		cout << "2. Doi mat khau." << endl;
		cout << "3. Cap nhat thong tin ca nhan." << endl;
		cout << "0. Thoat chuc nang." << endl;
		cout << "Chon chuc nang: ";
		cin >> cases;
		switch (cases)
		{
		case 1:
		{
			return;
		}
		case 2:
		{
			char op[MAX_PASSWORD], np[MAX_PASSWORD];
			cout << "Xac nhan mat khau cu:" << endl;
			cout << "Nhap mat khau cu: ";
			insertPassword(op);
			if (checkPassWord(a, op))
			{
				cout << "Nhap mat khau moi: " << endl;
				insertPassword(np);
				ChangePassword(a, np);
				break;
			}
			while (!checkPassWord(a, op))
			{
				cout << "Mat khau sai, moi nhap lai." << endl;
				insertPassword(op);
			}
			cout << "Nhap mat khau moi: " << endl;
			insertPassword(np);
			a = ChangePassword(a, np);
			break;
		}
		case 3:
		{
			changeInfo(a);
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
}