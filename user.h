#pragma once
#define MAX_USERNAME 51
#define MAX_PASSWORD 26
#define MAX_STATUS 10
#define MAX_PERMISS 8
#define MAX_NAME 51
#define MAX_BIRTHDAY 11
#define MAX_CMND 13
#define MAX_ADDRESS 251
#define MAX_SEX 4
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
	char status[MAX_STATUS + 1]; //activated or block
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
uNode* findTail(uList& l);
void addTail(uList& l, userInfo u);
uNode* createUserNode(userInfo x);
void read1userInfo(FILE* f, userInfo& u, int& dem);
void readUserFile(uList& l);
void writeList(uList l);
uNode* takeNode(uList& l);
bool checkUserName_Pass(userInfo a);
bool checkUser(userInfo a);
void insertPassword(userInfo& a);
userInfo Login();
void ChangePassword(userInfo a, char* np);
userInfo createUser();
void addUserToFile(userInfo a);
bool checkPassWord(userInfo a, char* p);
void changeInfo(userInfo a);
void menuAdmin();
void menuManager();
void menuExpert();