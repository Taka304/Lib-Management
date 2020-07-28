#pragma once
#define MAX_USERNAME 51
#define MAX_PASSWORD 26
#define MAX_STATUS 10
#define MAX_PERMISS 12
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
	char sex[MAX_SEX];
	char permiss[MAX_PERMISS]; //quan li or chuyen vien or admin
	char status[MAX_STATUS]; //hoat dong or block
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
void insertPassword(char *pass);
userInfo Login();
void ChangePassword(userInfo a, char* np);
userInfo createUser();
void addUserToFile(userInfo a);
bool checkPassWord(userInfo a, char* p);
void changeInfo(userInfo a);
void menuAdmin();
void menuManager();
void menuExpert();
