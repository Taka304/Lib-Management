#include<iostream>
using namespace std;



struct Node
{
	readersInfo info;
	rNode* next;
};

struct rList
{
	rNode* head;
};

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

