#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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
	userInfo* b=new userInfo;
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
		if (strcmp(b->userName,a.userName)==0 && strcmp(b->passWord, a.passWord)==0)
		{
			delete[]b;
			fclose(fp);
			return true;
		}
	} while (dem == 1);
	delete[]b;
	return false;
}
void Login()
{
	userInfo a;
	cout << "Nhap ten tai khoan va mat khau:" << endl;
	cout << "Tai khoan: ";
	cin >> a.userName;
	cout << "Mat khau: ";
	cin >> a.passWord;
	while (!checkUser(a))
	{
		cout << "Sai tai khoan hoac mat khau, moi nhap lai:" << endl;
		cout << "Nhap ten tai khoan va mat khau:" << endl;
		cout << "Tai khoan: ";
		cin >> a.userName;
		cout << "Mat khau: ";
		cin >> a.passWord;
	}
	cout << "Chao mung ban." << endl;
	return; //Them menu co quyen su dung sau
}
int main()
{
	Login();
}
