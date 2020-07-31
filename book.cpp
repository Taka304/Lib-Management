#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "book.h"

using namespace std;

//Tao ds quyen sach
void init_bList(bList& l)
{
	l.head = NULL;
}

//Tao node quyen sach
bNode* createbook(bookInfo a)
{
	bNode* p = new bNode[sizeof(bNode)];
	p->info = a;
	p->next = NULL;
	return p;
}

//Tim node quyen sach dua tren thong tin
int FindbX(char i[], bList l)
{
	bNode* p;
	int dem = 0;
	for (p = l.head; p != NULL; p = p->next)
	{
		dem++;
		if (strcmp(p->info.ISBN, i) == 0)
			return dem;
	}
	return dem;
}

int bLen(bList L) // Do dai danh sach
{
	bNode* PH = L.head;
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

//giai phong node
void freebbook(bList L)
{
	bNode* p = L.head;
	while (p != NULL)
	{
		bNode* q = p->next;
		free(p);
		p = q;
	}
}

//xoa dau ds
void deletebHead(bList& d)
{
	if (d.head == NULL)
	{
		return;
	}
	d.head = d.head->next;
}

//xoa cuoi ds
void deletebTail(bList& d)
{
	if (d.head == NULL)
	{
		return;
	}
	bNode* p = d.head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = NULL;
}

//xoa ds tai vi tri co thong tin da tim
void deletebAt(bList& L, int k)
{
	bNode* PH = L.head, * PT;
	int i = 1, l = bLen(L);
	if (k<1 || k> l + 1) printf("Vi tri xoa khong hop le !");
	else
	{
		if (k == 1) deletebHead(L);
		else
			if (k == l + 1) deletebTail(L);
			else
			{
				while (PH != NULL && i != k - 1)
				{
					i++;
					PH = PH->next;
				}
				PT = PH->next->next;
				delete(PH->next);
				PH->next = PT;
			}
	}
}

//Nhap quyen sach vao cuoi danh sach
void insertbTail(bList& l, bookInfo a)
{
	bNode* newbook = createbook(a);
	if (l.head == NULL)
	{
		l.head = newbook;
		return;
	}
	bNode* p = l.head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = newbook;
	return;
}

//doc thong tin 1 quyen sach tu file
void read1Book(FILE* f, bookInfo& r)
{
	fscanf(f, "%[^,]", r.ISBN);
	fgetc(f);
	fscanf(f, "%[^,]", r.fullname);
	fgetc(f);
	fscanf(f, "%[^,]", r.author);
	fgetc(f);
	fscanf(f, "%[^,]", r.nxb);
	fgetc(f);
	fscanf(f, "%[^,]", r.pYear);
	fgetc(f);
	fscanf(f, "%[^,]", r.type);
	fgetc(f);
	fscanf(f, "%d", &r.cost);
	fgetc(f);
	fscanf(f, "%s\n", r.num);
}

//doc ds quyen sach tu file
void readBList(bList& l)
{
	FILE* f = fopen("book.csv", "r+");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	init_bList(l);
	while (fgetc(f) != -1)
	{
		fseek(f, -1, SEEK_CUR);
		bookInfo r;
		read1Book(f, r);
		insertbTail(l, r);
	}
	fclose(f);
}

//xuat thong tin 1 quyen sach ra man hinh
void infoBOut(bookInfo r)
{
	cout << "ISBN: " << r.ISBN << endl;
	cout << "Ten sach: " << r.fullname << endl;
	cout << "Tac gia: " << r.author << endl;
	cout << "Nha xuat ban: " << r.nxb << endl;
	cout << "Nam xuat ban: " << r.pYear << endl;
	cout << "The loai: " << r.type << endl;
	cout << "Gia sach: " << r.cost << endl;
	cout << "So luong: " << r.num << endl;
}

//xuat ds thong tin quyen sach tu file
void readebListout(bList l)
{
	int dem = 1;
	for (bNode* k = l.head; k != NULL; k = k->next)
	{
		cout << "\n\n\t\t Sach thu " << dem++ << "\n";
		infoBOut(k->info);
	}
	freebbook(l);
}

//nhap thong tin quyen sach
void infoBIn(bookInfo& r)
{
	cin.ignore();
	cout << "ISBN: ";
	cin.getline(r.ISBN, sizeof(r.ISBN));
	cout << "Ten sach: ";
	cin.getline(r.fullname, sizeof(r.fullname));
	cout << "Tac gia: ";
	cin.getline(r.author, sizeof(r.author));
	cout << "Nha xuat ban: ";
	cin.getline(r.nxb, sizeof(r.nxb));
	cout << "Nam xuat ban: ";
	cin.getline(r.pYear, sizeof(r.pYear));
	cout << "The loai: ";
	cin.getline(r.type, sizeof(r.type));
	cout << "Gia sach: ";
	cin >> r.cost;
	cin.ignore();
	cout << "So luong: ";
	cin.getline(r.num, sizeof(r.num));
}

//ghi thong tin 1 quyen sach vao file
void write1book(FILE* f, bookInfo& r)
{
	fprintf(f, "%s,%s,%s,", r.ISBN, r.fullname, r.author);
	fprintf(f, "%s,%s,%s,%d,%s", r.nxb, r.pYear, r.type, r.cost, r.num);
	fprintf(f, "\n");
}

//Nhap thong tin 1 quyen sach vao cuoi file
void insertBook(bookInfo& r)
{
	FILE* f = fopen("book.csv", "a");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	infoBIn(r);
	write1book(f, r);
	fclose(f);
}

//ghi lai ds quyen sach vao file
void writeBList(bList& l)
{
	FILE* f = fopen("book.csv", "w+");
	if (!f)
	{
		cout << "Khong mo duoc";
		return;
	}
	for (bNode* p = l.head; p != NULL; p = p->next)
	{
		write1book(f, p->info);
	}
	fclose(f);
}

//xoa thong tin 1 quyen sach
void deleteBook(bList& l)
{
	readBList(l);
	char newISBN[MAX_ISBN];
	cout << "Nhap ISBN can xoa: ";
	cin >> newISBN;
	int flag = FindbX(newISBN, l);
	if (flag)
	{
		deletebAt(l, flag);
		writeBList(l);
	}
	else
	{
		cout << "Khong ton tai ISBN tren!";
	}
}

//tim quyen sach theo ISBN
void FindISBN(bList& l)
{
	bNode* p;
	char i[MAX_ISBN];
	cout << "Nhap ISBN: ";
	cin >> i;
	readBList(l);
	for (p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->info.ISBN, i) == 0)
		{
			cout << "Thong tin sach co ISBN tren: " << endl;
			infoBOut(p->info);
			return;
		}

	}
	cout << "Khong tim duoc ISBN tren!";
}

//menu doi thong tin
void changebInfodisplay()
{
	cout << "Nhan 1 de thay doi ten sach" << endl;
	cout << "Nhan 2 de thay doi tac gia" << endl;
	cout << "Nhan 3 de thay doi NXB" << endl;
	cout << "Nhan 4 de thay doi nam xuat ban" << endl;
	cout << "Nhan 5 de thay doi the loai" << endl;
	cout << "Nhan 6 de thay doi gia sach" << endl;
	cout << "Nhan 7 bat ky de thay doi so quyen sach" << endl;
	cout << "Nhan 0 de quay tro lai menu" << endl;
	cout << "Lua chon cua ban: ";
}

//lua chon doi thong tin
void changebInfo(bookInfo& r)
{
	int option;
	do
	{
		cout << endl;
		changebInfodisplay();
		cin >> option;
		switch (option)
		{
		case 1:
		{
			char i[MAX_BNAME];
			cout << "Nhap ten sach moi: ";
			cin.ignore();
			cin.getline(i,sizeof(i));
			strcpy(r.fullname, i);
			break;
		}
		case 2:
		{
			char i[MAX_BAUTHOR];
			cout << "Nhap ten tac gia moi: ";
			cin.ignore();
			cin.getline(i, sizeof(i));
			strcpy(r.author, i);
			break;
		}
		case 3:
		{
			char i[MAX_BNXB];
			cout << "Nhap NXB moi: ";
			cin.getline(i, sizeof(i));
			cin.ignore();
			strcpy(r.nxb, i);
			break;
		}
		case 4:
		{
			char i[MAX_BYEAR];
			cout << "Nhap nam xuat ban moi: ";
			cin.ignore();
			cin.getline(i, sizeof(i));
			strcpy(r.pYear, i);
			break;
		}
		case 5:
		{
			char i[MAX_BTYPE];
			cout << "Nhap the loai moi: ";
			cin.ignore();
			cin.getline(i, sizeof(i));
			strcpy(r.type, i);
			break;
		}
		case 6:
		{
			int i;
			cout << "Nhap gia moi: ";
			cin >> i;
			r.cost = i;
			break;
		}
		case 7:
		{
			char i[MAX_BNUM];
			cout << "Nhap so luong moi: ";
			cin.ignore();
			cin.getline(i, sizeof(i));
			strcpy(r.num, i);
			break;
		}
		case 0:
		{
			return;
		}
		}
		return;
	} while (option >= 0 && option <= 7);
}

//doi thong tin dua vao ISBN
void changeInfobyISBN(bList& l)
{
	bNode* p;
	char i[MAX_ISBN];
	cout << "Nhap ISBN: ";
	cin >> i;
	readBList(l);
	for (p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->info.ISBN, i) == 0)
		{
			cout << "Thong tin sach ban muon doi\n\n";
			infoBOut(p->info);
			changebInfo(p->info);
			writeBList(l);
			cout << "Doi thong tin thanh cong!" << endl;
			cout << "Nhan bat ky de quay lai" << endl;
			system("pause");
			return;
		}
	}
	cout << "Khong tim duoc ISBN tren!";
}


void FindBookByName(bList& l)
{
	bNode* p;
	int flag = 0;
	char i[MAX_BNAME];
	cout << "Nhap ten: ";
	cin >> i;
	for (p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->info.fullname, i) == 0)
		{
			cout << "\n\n\t\t Sach thu " << flag++ << "\n";
			infoBOut(p->info);
		}
	}
	if (flag == 0)
	{
		cout << "Khong tim duoc ten tren!";
		return;
	}
	else
		return;
}