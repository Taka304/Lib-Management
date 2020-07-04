#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h> 
#include <ctype.h> 
using namespace std;

#define MAX_USERNAME 50
#define MAX_PASSWORD 25

struct userInfo
{
	char userName[MAX_USERNAME + 1];
	char passWord[MAX_PASSWORD + 1];
};

bool checkUser(userInfo a)
{
	FILE* fp = fopen("account.txt", "rb");
	if (!fp)
	{
		return false;
	}
	userInfo* b = new userInfo;
	int dem;
	do
	{
		dem = fread(b, sizeof(userInfo), 1, fp);
		/*cout << b->userName << endl;                 THU
		cout << b->passWord << endl;
		int ss1 = strcmp(b->userName, a.userName);
		cout << ss1 << endl;
		int ss2= strcmp(b->passWord, a.passWord);
		cout << ss2 << endl;*/
		if (strcmp(b->userName, a.userName) == 0 && strcmp(b->passWord, a.passWord) == 0)
		{
			delete b;
			fclose(fp);
			return true;
		}
	} while (dem == 1);
	delete b;
	fclose(fp);
	return false;
}

void insertPassword(userInfo& a) //Nhap mat khau duoi dang '*'
{
	int ch;
	int i = 0;
	cout << "Mat khau: ";
	fflush(stdout);
	while ((ch = _getch()) != EOF && ch != '\n'&& ch!='\r')
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
	while (!checkUser(a))
	{
		cout << "Sai tai khoan hoac mat khau, moi nhap lai:" << endl;
		cout << "Nhap ten tai khoan va mat khau:" << endl;
		cout << "Tai khoan: ";
		cin >> a.userName;
		insertPassword(a);
	}
	cout << "Chao mung ban." << endl;
	return a; //Them menu có quyen su dung sau
}

void ChangePassword(userInfo a, char* np)
{
	FILE* f = fopen("account.txt", "rb+");
	if (!f)
	{
		return;
	}
	userInfo* b = new userInfo;
	int dem;
	do
	{
		dem = fread(b, sizeof(userInfo), 1, f);
		if (strcmp(b->userName, a.userName) == 0 && strcmp(b->passWord, a.passWord) == 0)
		{
			char* name = b->userName;
			int len = sizeof(userInfoToLogin);
			fseek(f, -len, SEEK_CUR);
			fwrite(name, sizeof(b->userName), 1, f);
			fwrite(np, sizeof(b->passWord), 1, f);
			delete b;
			fclose(f);
			return;
		}
	} while (dem == 1);
}

void DangKy(userInfo a)
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

int main()
{
	userInfo a;
	cout << "Nhap ten: ";
	cin >> a.userName;
	insertPassword(a);
	DangKy(a);
	a = Login();
	char np[MAX_PASSWORD];
	cout << "Nhap mat khau moi: ";
	cin >> np;
	ChangePassword(a, np);
}
