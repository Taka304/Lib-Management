#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>

using namespace std;

#define MAX_RID 9
#define MAX_RNAME 50
#define MAX_REMAIL 50
#define MAX_RCMND 13
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
};

struct rList
{
	rNode* head;
};

//Tao ds doc gia
void init_rList(rList& l) 
{
	l.head = NULL;
}

//Tao doc gia
rNode *createReader(readersInfo a)
{
	rNode* p = new rNode[sizeof(rNode)];
	p->info = a;
	p->next = NULL;
	return p;
}

int FindX(char i[], rList l)
{
	rNode* p;
	int dem = 0;
	for (p = l.head; p != NULL; p = p->next)
	{
		dem++;
		if (strcmp(p->info.ID, i)==0)
			return dem;
	}
	return NULL;
}

int Len(rList L) // Do dai danh sach
{
	rNode* PH = L.head;
	int i = 0;
	if (PH != NULL) i = 1;
	while (PH != NULL)
	{
		if (PH == NULL) break;
		PH = PH->next;
		i++;
	}
	return i;
}

void deleteHead(rList& d)
{
	if (d.head == NULL)
	{
		return;
	}
	d.head = d.head->next;
}

void deleteTail(rList& d)
{
	if (d.head == NULL)
	{
		return;
	}
	rNode* p = d.head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = NULL;
}

void deleteAt(rList& L, int k)
{
	rNode* PH = L.head, * PT;
	int i = 1, l = Len(L);
	if (k<1 || k> l + 1) printf("Vi tri xoa khong hop le !");
	else
	{
		if (k == 1) deleteHead(L);
		else
			if (k == l + 1) deleteTail(L);
			else
			{
				while (PH != NULL && i != k - 1)
				{
					i++;
					PH = PH->next;
				}
				PT = PH->next->next;
				PH->next = PT;
			}
	}
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
		return;
	}
	else
	{
		newReader->next = l.head;
		l.head = newReader;
		return;
	}
}

void readDate(FILE* filename, date &a)
{
	
	fscanf(filename, "%d", &a.day);
	fgetc(filename);
	fscanf(filename, "%d", &a.month);
	fgetc(filename);
	fscanf(filename, "%d", &a.year);
}

void read1Reader(FILE* f,readersInfo& r)
{
	fscanf(f, "%[^,]", r.ID);
	fgetc(f);
	fscanf(f, "%[^,]", r.fullname);
	fgetc(f);
	fscanf(f, "%[^,]", r.cmnd);
	fgetc(f);
	readDate(f, r.bDay);
	fgetc(f);
	fscanf(f, "%[^,]", r.sex);
	fgetc(f);
	fscanf(f, "%[^,]", r.email);
	fgetc(f);
	fscanf(f, "%[^,]", r.address);
	fgetc(f);
	readDate(f, r.createdDay);
	fgetc(f);
	readDate(f, r.exDay);
	fgetc(f);
}

void infoOut(readersInfo r)
{
	cout << "ID: " << r.ID << endl;
	cout << "Ho ten: " << r.fullname << endl;
	cout << "CMND: " << r.cmnd << endl;
	cout << "Ngay thang nam sinh: " << r.bDay.day << "/" << r.bDay.month << "/" << r.bDay.year << endl;
	cout << "Gioi tinh: " << r.sex << endl;
	cout << "Dia chi: " << r.address << endl;
	cout << "Ngay lap the: " << r.createdDay.day << "/" << r.createdDay.month << "/" << r.createdDay.year << endl;
	cout << "Ngay het han: " << r.exDay.day << "/" << r.exDay.month << "/" << r.exDay.year << endl;
}

void readRList(rList& l)
{
	FILE* f = fopen("reader.txt", "r+");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	init_rList(l);
	while (!feof(f))
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
		cout << "\n\n\t\t Nguoi doc thu " << dem++<<"\n";
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
	cout << "Ngay thang nam sinh: ";
	cin >> r.bDay.day;
	cin >> r.bDay.month;
	cin >> r.bDay.year;
	cout << "Gioi tinh: ";
	fgetc(stdin);
	cin.getline(r.sex, sizeof(r.sex));
	cout << "Dia chi: ";
	cin.getline(r.address, sizeof(r.address));
	r.createdDay = today();
	r.exDay = expDay();
}

void writeDate(FILE* f, date a)
{
	fprintf(f, "%d/%d/%d,", a.day, a.month, a.year);
}

void write1Reader(FILE *f,readersInfo& r)
{
	fprintf(f, "%s,%s,%s,", r.ID, r.fullname, r.cmnd);
	writeDate(f, r.bDay);
	fprintf(f, "%s,%s,%s,", r.sex,r.email, r.address);
	writeDate(f, r.createdDay);
	writeDate(f, r.exDay);
	fprintf(f, "\n");
}

void insertReader(readersInfo& r)
{

	FILE* f = fopen("reader.txt", "a");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	infoIn(r);
	write1Reader(f, r);
	fclose(f);
}

void deleteReader(rList& l)
{
	
	readRList(l);
	char newID[MAX_RID];
	cout << "Nhap Id can xoa: ";
	cin >> newID;
	int flag = FindX(newID, l);
	if (flag)
	{
		FILE* f = fopen("reader.txt", "w+");
		if (!f)
		{
			cout << "Khong mo duoc";
			return;
		}
		deleteAt(l, flag);
		for (rNode *p = l.head; p != NULL; p = p->next)
		{
			write1Reader(f,p->info);
		}
		fclose(f);
	}
	else
	{
		cout << "Khong ton tai nguoi doc co ID tren!";
	}

}

rNode* FindCMND(char i[], rList l)
{
	rNode* p;
	cout << "Nhap cmnd: ";
	for (p = l.head; p != NULL; p = p->next)
	{
		if (p->info.cmnd == i)
			return p;
	}
	return NULL;
}

int main()
{
	rList l;
	readRList(l);
	readerListout(l);
}
