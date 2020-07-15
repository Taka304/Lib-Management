#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>

using namespace std;

#define MAX_RID 9
#define MAX_RNAME 50
#define MAX_REMAIL 50
#define MAX_RCMND 10
#define MAX_RADDRESS 250

struct date
{
	int day;
	int month;
	int year;
};

struct readersInfo
{
	char ID[MAX_RID];
	char fullname[MAX_RNAME];
	char cmnd[MAX_RCMND];
	date bDay;
	char sex[4];
	char email[MAX_REMAIL];
	char address[MAX_RADDRESS];
	date createdDay;
	date exDay;
};

struct rNode
{
	readersInfo info;
	rNode* next;
	rNode* prev;
};

struct rList
{
	rNode* head;
	rNode* tail;
};

//Tao ds doc gia
void init_rList(rList& l) 
{
	l.head = NULL;
	l.tail = NULL;
}

//Tao doc gia
rNode *createReader(readersInfo a)
{
	rNode* p = new rNode[sizeof(rNode)];
	p->info = a;
	p->next = NULL;
	p->prev = NULL;
	return p;
}

date today()
{
	time_t now= time(0);
	tm* lotm = localtime(&now);
	date today;
	today.day = lotm->tm_mday;
	today.month = lotm->tm_mon + 1;
	today.year = lotm->tm_year + 1900;
	return today;
}

date expDay()
{
	time_t now = time(0);
	tm* lotm = localtime(&now);
	date today;
	today.day = lotm->tm_mday;
	today.month = lotm->tm_mon + 1;
	today.year = lotm->tm_year + 1904;
	return today;
}

//Nhap doc gia vao cuoi danh sach
void insertTail(rList& l, readersInfo a)
{
	rNode* newReader = createReader(a);
	if (l.head == NULL)
	{
		l.head = newReader;
		l.tail = newReader;
		return;
	}
	else
	{
		l.tail->next = newReader;
		newReader->prev = l.tail;
		l.tail = newReader;
	}
}

void readDate(FILE* filename, date &a)
{
	fread(&a.day, sizeof(a.day), 1, filename);
	fseek(filename, 1, SEEK_CUR);
	fread(&a.month, sizeof(a.month), 1, filename);
	fseek(filename, 1, SEEK_CUR);
	fread(&a.year, sizeof(a.year), 1, filename);
}

void writeDate(FILE* filename, date& a)
{
	fwrite(&a.day, sizeof(a.day), 1, filename);
	fwrite("/", sizeof(char), 1, filename);
	fwrite(&a.month, sizeof(a.month), 1, filename);
	fwrite("/", sizeof(char), 1, filename);
	fwrite(&a.year, sizeof(a.year), 1, filename);
}

void read1Reader(FILE* f,readersInfo& r)
{
	fread(&r.ID, sizeof(r.ID), 1, f);
	fseek(f, 1, SEEK_CUR);
	fread(&r.fullname, sizeof(r.fullname), 1, f);
	fseek(f, 1, SEEK_CUR);
	fread(&r.cmnd, sizeof(r.cmnd), 1, f);
	fseek(f, 1, SEEK_CUR);
	readDate(f, r.bDay);
	fseek(f, 1, SEEK_CUR);
	fread(&r.sex, sizeof(r.sex), 1, f);
	fseek(f, 1, SEEK_CUR);
	fread(&r.email, sizeof(r.email), 1, f);
	fseek(f, 1, SEEK_CUR);
	fread(&r.address, sizeof(r.address), 1, f);
	fseek(f, 1, SEEK_CUR);
	readDate(f, r.createdDay);
	fseek(f, 1, SEEK_CUR);
	readDate(f, r.exDay);
	fseek(f, 1, SEEK_CUR);
}

void input1Reader(readersInfo& r)
{
	FILE* f = fopen("reader1.txt", "wb+");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	fwrite(r.ID, sizeof(r.ID), 1, f);
	fwrite(",", sizeof(char), 1, f);
	fwrite(r.fullname, sizeof(r.fullname), 1, f);
	fwrite(",", sizeof(char), 1, f);
	fwrite(r.cmnd, sizeof(r.cmnd), 1, f);
	fwrite(",", sizeof(char), 1, f);
	writeDate(f, r.bDay);
	fwrite(",", sizeof(char), 1, f);
	fwrite(r.sex, sizeof(r.sex), 1, f);
	fwrite(",", sizeof(char), 1, f);
	fwrite(r.email, sizeof(r.email), 1, f);
	fwrite(",", sizeof(char), 1, f);
	fwrite(r.address, sizeof(r.address), 1, f);
	fwrite(",", sizeof(char), 1, f);
	r.createdDay = today();
	writeDate(f, r.createdDay);
	fwrite(",", sizeof(char), 1, f);
	r.exDay = expDay();
	writeDate(f, r.exDay);
	fclose(f);
}

void infoOut(readersInfo r)
{
	cout << "ID: " << r.ID << endl;
	cout << "Ho ten: " << r.fullname << endl;
	cout << "CMND: " << r.cmnd << endl;
	cout << "Ngay thang nam sinh: " << r.bDay.day << "/" << r.bDay.month << "/" << r.bDay.year << endl;
	cout << "Gioi tinh " << r.sex << endl;
	cout << "Dia chi: " << r.address << endl;
	cout << "Ngay lap the: " << r.createdDay.day << "/" << r.createdDay.month << "/" << r.createdDay.year << endl;
	cout << "Ngay het han: " << r.exDay.day << "/" << r.exDay.month << "/" << r.exDay.year << endl;
}

void readRList(rList& l)
{
	FILE* f = fopen("reader1.txt", "rb+");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	while (ftell(f)!= SEEK_END)
	{
		readersInfo r;
		read1Reader(f, r);
		insertTail(l, r);
	}
	fclose(f);
}

void readerListout(rList l)
{
	int dem = 1;
	for (rNode* k = l.head; k != NULL; k = k->next)
	{
		cout << "\n\n\t\t Nguoi doc thu " << dem++;
		infoOut(k->info);
	}
}

void infoIn(readersInfo &r)
{
	cout << "ID: ";
	cin.getline(r.ID,sizeof(r.ID));
	cout << "Ho ten: ";
	cin.getline(r.fullname, sizeof(r.fullname));
	cout << "CMND: ";
	cin.getline(r.cmnd, sizeof(r.cmnd));
	cout << "Ngay sinh: ";
	cin >> r.bDay.day;
	cout << "Thang sinh: ";
	cin >> r.bDay.month;
	cout << "Nam sinh: ";
	cin >> r.bDay.year;
	cout << "Gioi tinh: ";
	cin.getline(r.sex, sizeof(r.sex));
	cout << "Dia chi: ";
	cin.getline(r.address, sizeof(r.address));
}

int main()
{
	rList l;
	init_rList(l);
	readRList(l);
	readerListout(l);
}
