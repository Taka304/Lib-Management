#pragma once
#include "reader.h"
#define MAX_USERNAME 51
#define MAX_PASSWORD 26
#define MAX_NAME 51
#define MAX_BIRTHDAY 11
#define MAX_CMND 13
#define MAX_ADDRESS 251
#define MAX_SEX 4
struct userInfo
{
	char userName[MAX_USERNAME];
	char passWord[MAX_PASSWORD];
	char fullName[MAX_NAME];
	date birthDay;
	char identityID[MAX_CMND];
	char address[MAX_ADDRESS];
	int sex; //1 la nu, 2 la nam
	int permiss; //1 la quan li, 2 la chuyen vien, 3 la admin
	int status; //1 la hoat dong, 2 la block
};
struct uNode
{
	userInfo info;
	uNode* next;
};
struct uList
{
	uNode* head;
};
void init_uList(uList& l);
uNode* findTailuser(uList& l);
void addTailuser(uList& l, userInfo u);
uNode* createUserNode(userInfo x);
void read1userInfo(FILE* f, userInfo& u, int& dem);
void readUserFile(uList& l);
void writeList(uList l);
uNode* takeNode(uList& l);
bool checkUserName_Pass(userInfo a);
bool checkUserName(userInfo a);
void insertPassword(char* pass);
userInfo Login();
userInfo ChangePassword(userInfo a, char* np);
userInfo ChangeFullName(userInfo a, char* nname);
void ChangeBirthDay(userInfo& a, date nb);
userInfo ChangeIdentity(userInfo a, char* ni);
userInfo ChangeAddress(userInfo a, char* na);
void ChangeSex(userInfo& a);
userInfo createUser();
void addUserToFile(userInfo a);
bool checkPassWord(userInfo a, char* p);
void changeInfo(userInfo a);
void menuAdmin();
void menuManager();
void menuExpert();