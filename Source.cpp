#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h> 
#include <ctype.h> 
using namespace std;
#define MAX_USERNAME 50
#define MAX_PASSWORD 25
#define MAX_STATUS 9
#define MAX_PERMISS 7
#define MAX_NAME 50
#define MAX_BIRTHDAY 10
#define MAX_CMND 12
#define MAX_ADDRESS 250
#define MAX_SEX 3
struct userInfo
{
	char userName[MAX_USERNAME + 1];
	char passWord[MAX_PASSWORD + 1];
	char fullName[MAX_NAME + 1];
	char birthDay[MAX_BIRTHDAY + 1];
	char identityID[MAX_CMND + 1];
	char address[MAX_ADDRESS + 1];
	char sex[MAX_SEX + 1];
	char permiss[MAX_PERMISS + 1]; //manager or expert or admin
	char status[MAX_STATUS + 1]; //activatd or block
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
	userInfo *b=new userInfo;
	int dem;
	do
	{
		dem = fread(b, sizeof(userInfo), 1, f);
		if (strcmp(b->userName, a.userName) == 0 && strcmp(b->passWord, a.passWord) == 0)
		{
			char* name = b->userName;
			int len = sizeof(userInfo);
			fseek(f, -len, SEEK_CUR);
			fwrite(name, sizeof(b->userName), 1, f);
			fwrite(np, sizeof(b->passWord), 1, f);
			delete b;
			fclose(f);
			return;
		}
	} while (dem == 1);
}
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
