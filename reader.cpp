#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "reader.h"
#include "borrowBook.h" 
#include "backBook.h"
using namespace std;

//Tao ds doc gia
void init_rList(rList& l)
{
	l.head = NULL;
}

//Tao node doc gia
rNode* createReader(readersInfo a)
{
	rNode* p = new rNode[sizeof(rNode)];
	p->info = a;
	p->next = NULL;
	return p;
}

//Tim node doc gia dua tren thong tin
int FindrX(char i[], rList l)
{
	rNode* p;
	int dem = 0;
	for (p = l.head; p != NULL; p = p->next)
	{
		dem++;
		if (strcmp(p->info.ID, i) == 0)
			return dem;
	}
	return NULL;
}

int rLen(rList L) // Do dai danh sach
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

//xoa dau ds
void deleterHead(rList& d)
{
	if (d.head == NULL)
	{
		return;
	}
	d.head = d.head->next;
}

//xoa cuoi ds
void deleterTail(rList& d)
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

//xoa ds tai vi tri co thong tin da tim
void deleterAt(rList& L, int k)
{
	rNode* PH = L.head, * PT;
	int i = 1, l = rLen(L);
	if (k<1 || k> l + 1) printf("Vi tri xoa khong hop le !");
	else
	{
		if (k == 1) deleterHead(L);
		else
			if (k == l + 1) deleterTail(L);
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

//tao ngay lap the
date today()
{
	time_t now = time(0);
	tm* lotm = localtime(&now);
	date today;
	today.day = lotm->tm_mday;
	today.month = lotm->tm_mon + 1;
	today.year = lotm->tm_year + 1900;
	return today;
}

//tao ngay het han
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
void insertrTail(rList& l, readersInfo a)
{
	rNode* newReader = createReader(a);
	if (l.head == NULL)
	{
		l.head = newReader;
		return;
	}
	rNode* p = l.head;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = newReader;
	return;
}

//doc ngay
void readDate(FILE* filename, date& a)
{

	fscanf(filename, "%d", &a.day);
	fgetc(filename);
	fscanf(filename, "%d", &a.month);
	fgetc(filename);
	fscanf(filename, "%d", &a.year);
}

void readExDate(FILE* filename, date& a)
{

	fscanf(filename, "%d", &a.day);
	fgetc(filename);
	fscanf(filename, "%d", &a.month);
	fgetc(filename);
	fscanf(filename, "%d\n", &a.year);
}

//doc thong tin 1 doc gia tu file
void read1Reader(FILE* f, readersInfo& r)
{
	fscanf(f, "%[^,]", r.ID);
	fgetc(f);
	fscanf(f, "%[^,]", r.fullname);
	fgetc(f);
	fscanf(f, "%[^,]", r.cmnd);
	fgetc(f);
	readDate(f, r.bDay);
	fgetc(f);
	fscanf(f, "%d",&r.sex);
	fgetc(f);
	fscanf(f, "%[^,]", r.email);
	fgetc(f);
	fscanf(f, "%[^,]", r.address);
	fgetc(f);
	readDate(f, r.createdDay);
	fgetc(f);
	readExDate(f, r.exDay);
}

//doc ds doc gia tu file
void readRList(rList& l)
{
	FILE* f = fopen("reader.csv", "r+");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	init_rList(l);
	while (fgetc(f) != -1)
	{
		fseek(f, -1, SEEK_CUR);
		readersInfo r;
		read1Reader(f, r);
		insertrTail(l, r);
	}
	fclose(f);
}

//xuat thong tin 1 doc gia ra man hinh
void infoOut(readersInfo r)
{
	cout << "ID: " << r.ID << endl;
	cout << "Ho ten: " << r.fullname << endl;
	cout << "CMND: " << r.cmnd << endl;
	cout << "Ngay thang nam sinh: " << r.bDay.day << "/" << r.bDay.month << "/" << r.bDay.year << endl;
	cout << "Gioi tinh: " << r.sex << endl;
	cout << "Email: " << r.email << endl;
	cout << "Dia chi: " << r.address << endl;
	cout << "Ngay lap the: " << r.createdDay.day << "/" << r.createdDay.month << "/" << r.createdDay.year << endl;
	cout << "Ngay het han: " << r.exDay.day << "/" << r.exDay.month << "/" << r.exDay.year << endl;
}

//xuat ds thong tin doc gia tu file
void readerListout(rList l)
{
	int dem = 1;
	for (rNode* k = l.head; k != NULL; k = k->next)
	{
		cout << "\n\n\t\t Nguoi doc thu " << dem++ << "\n";
		infoOut(k->info);
	}
}

//nhap thong tin doc gia
void infoIn(readersInfo& r)
{
	cout << "Ho ten: ";
	cin.getline(r.fullname, sizeof(r.fullname));
	cout << "CMND: ";
	cin.getline(r.cmnd, sizeof(r.cmnd));
	cout << "Ngay thang nam sinh: ";
	cin >> r.bDay.day;
	cin >> r.bDay.month;
	cin >> r.bDay.year;
	cout << "Gioi tinh(1: Nu, 2: Nam): ";
	cin >> r.sex;
	cout << "Email: ";
	cin.ignore();
	cin.getline(r.email, sizeof(r.email));
	cout << "Dia chi: ";
	cin.getline(r.address, sizeof(r.address));
	r.createdDay = today();
	r.exDay = expDay();
}

//ghi ngay tu file
void writeDate(FILE* f, date a)
{
	fprintf(f, "%d/%d/%d,", a.day, a.month, a.year);
}

void writeExDate(FILE* f, date a)
{
	fprintf(f, "%d/%d/%d", a.day, a.month, a.year);
}

//ghi thong tin 1 doc gia vao file
void write1Reader(FILE* f, readersInfo& r)
{
	fprintf(f, "%s,%s,%s,", r.ID, r.fullname, r.cmnd);
	writeDate(f, r.bDay);
	fprintf(f, "%d,%s,%s,", r.sex, r.email, r.address);
	writeDate(f, r.createdDay);
	writeExDate(f, r.exDay);
	fprintf(f, "\n");
}

bool validCheck(readersInfo& r, rList& l)
{
	for (rNode* p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.ID, r.ID) == 0)
		{
			return true;
		}
	}
	return false;
}

//Nhap thong tin 1 doc gia vao cuoi file
void insertReader(readersInfo& r, rList& l)
{
	FILE* f = fopen("reader.csv", "a");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	readRList(l);
	do
	{
		cout << "Ma doc gia: ";
		cin.ignore();
		cin.getline(r.ID, sizeof(r.ID));
	} while (validCheck(r, l));
	infoIn(r);
	write1Reader(f, r);
	fclose(f);
}

void writeRList(rList& l)
{
	FILE* f = fopen("reader.csv", "w+");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	for (rNode* p = l.head; p != NULL; p = p->next)
	{
		write1Reader(f, p->info);
	}
	fclose(f);
}

//xoa thong tin 1 doc gia
void deleteReader(rList& l)
{
	char newID[MAX_RID];
	cout << "Nhap Id can xoa: ";
	cin >> newID;
	int flag = FindrX(newID, l);
	if (flag)
	{
		FILE* f = fopen("reader.csv", "w+");
		if (!f)
		{
			cout << "Khong mo duoc";
			return;
		}
		deleterAt(l, flag);
		for (rNode* p = l.head; p != NULL; p = p->next)
		{
			write1Reader(f, p->info);
		}
		fclose(f);
	}
	else
	{
		cout << "Khong ton tai nguoi doc co ID tren!";
	}

}

//tim doc gia theo cmnd
void FindCMND(rList& l)
{
	rNode* p;
	char i[MAX_RCMND];
	cout << "Nhap cmnd: ";
	cin >> i;
	for (p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->info.cmnd, i) == 0)
		{
			infoOut(p->info);
			return;
		}

	}
	cout << "Khong tim duoc cmnd tren!";
}

//menu doi thong tin
void changeInfodisplay()
{
	cout << "Nhan 1 de thay doi ho ten" << endl;
	cout << "Nhan 2 de thay ngay sinh" << endl;
	cout << "Nhan 3 de thay doi CMND" << endl;
	cout << "Nhan 4 de thay doi gioi tinh" << endl;
	cout << "Nhan 5 de thay doi email" << endl;
	cout << "Nhan 6 de thay doi dia chi" << endl;
	cout << "Nhan 0 de tro lai menu" << endl;
	cout << "Lua chon cua ban: ";
}

//lua chon doi thong tin
void changeInfo(readersInfo& r)
{
	int option;
	do
	{
		cout << endl;
		changeInfodisplay();
		cin >> option;
		switch (option)
		{
		case 1:
		{
			char i[MAX_RNAME];
			cout << "Nhap ho ten moi: ";
			cin.ignore();
			cin.getline(i, sizeof(i));
			strcpy(r.fullname, i);
			break;
		}
		case 2:
		{
			date i;
			cout << "Nhap ngay thang nam sinh moi: ";
			cin >> i.day >> i.month >> i.year;
			r.bDay.day = i.day;
			r.bDay.month = i.month;
			r.bDay.year = i.year;
			break;
		}
		case 3:
		{
			char i[MAX_RCMND];
			cout << "Nhap CMND moi: ";
			cin.ignore();
			cin.getline(i, sizeof(i));
			strcpy(r.cmnd, i);
			break;
		}
		case 4:
		{
			if (r.sex == 1)
			{
				r.sex = 2;
			}
			else
			{
				r.sex = 1;
			}
			break;
		}
		case 5:
		{
			char i[MAX_REMAIL];
			cout << "Nhap email moi: ";
			cin.ignore();
			cin.getline(i, sizeof(i));
			strcpy(r.email, i);
			break;
		}
		case 6:
		{
			char i[MAX_RADDRESS];
			cout << "Nhap dia chi moi: ";
			cin.ignore();
			cin.getline(i, sizeof(i));
			strcpy(r.address, i);
			break;
		}
		case 0:
		{
			return;
		}
		}
		return;
	} while (option > 0 && option <= 6);
}

//doi thong tin dua vao ID
void changeInfobyID(rList& l)
{
	rNode* p;
	char i[MAX_RID];
	cout << "Nhap ID: ";
	cin >> i;
	readRList(l);
	for (p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->info.ID, i) == 0)
		{
			cout << "Thong tin nguoi doc ban muon doi\n\n";
			infoOut(p->info);
			changeInfo(p->info);
			writeRList(l);
			cout << "Doi thong tin thanh cong!" << endl;
			cout << "Nhan bat ky de quay lai" << endl;
			system("pause");
			return;
		}
	}
	cout << "Khong tim duoc ID tren!";
}

//tach danh sach theo ho ten
void FindBookByName(rList l, rList& l2)
{
	rNode* p;
	char name[MAX_RNAME];
	cout << "Nhap ho ten can tim sach: ";
	cin.getline(name, sizeof(name));
	for (p = l.head; p; p = p->next)
	{
		if (strcmp(p->info.fullname, name) == 0)
		{
			insertrTail(l2, p->info);
		}
	}
}

//in danh sach ho ten trung kem id
void NameByIdOut(rList l)
{
	for (rNode* p = l.head; p; p = p->next)
	{
		cout << ". ID: " << p->info.ID << ", ho va ten: " << p->info.fullname;
	}
}

//in sach theo ho ten va id da chon
void bookOut(rList l, char* id)
{
	FILE* f = fopen("borrowbook.csv", "r");
	bobList l1;
	init_borrowLinkedList(l1);
	readBorrowBook(l1, f);
	bobNode* temp = findBorrowByRId(l1, id);
	if (temp == NULL)
	{
		cout << "Doc gia khong muon sach.";
	}
	else
	{
		cout << "So sach muon: " << temp->info.amount << endl;
		cout << "Danh sach sach muon: " << endl;
		ISBNList_out(temp->info.l);
	}
}

