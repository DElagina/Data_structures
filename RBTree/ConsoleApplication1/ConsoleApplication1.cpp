// ConsoleApplication1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "locale.h"
#include "malloc.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

const char *msgs[] = { "0. �����", "1. ���������� ������ ��������",
"2. ����� �� ��������� �����", "3. �������� ��������", "4. ����� � ���� �������",
"5. ����� ��������, �������� �������� �� �������� � ��������� �����, �� �� ������������ � ���",
"6. ����� � ���� ������", "7. ������� �� �����", "8. ������������ ������" };

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

FILE* fd;

int w = 0;

const int SIZE = 10;

struct Node {
	int color, key;  //1-������; 0-�������
	struct Node *left, *right, *parent;
	char * info;
};

struct Item {
	int key, busy;
	Node * node;
};

int D_F_Read(void);
char *FgetStr(void);
int FgetInt(int *a);
int D_Find2(void);
int D_Show_Tree(void);
int D_Show(void);
int D_Delete(void);
void RB_Delete(Node *x);
void RB_Delete_Fixup(Node *x);
int D_Find1(void);
int D_Add(void);
void Tab_Insert(Node *x);
int Search(int k);
Node * Search_Tree(int k);
int Search_Tab(int k);
Node * RB_Insert(Node *x);
void RB_Insert_Fixup(Node *x);
void Left_Rotate(Node *x);
void Right_Rotate(Node *x);
int dialog(const char *msgs[], int N);
int getInt(int *a);
char *getStr(void);
int hash(int key);
int Create_Tab(Item **tab, Node **root, Node **EList);
void show(Node *ptr);
Node *find(int k);
Node *dopfind(int k);
Node *Sled(Node *x);
Node *Pred(Node *x);
Node *Min(Node *ptr);
Node *Max(Node *ptr);
void Tab_output(void);
int D_Time(void);
void show_tree(Node *ptr);

int(*fptr[])(void) = { NULL, D_Add, D_Find1, D_Delete, D_Show, D_Find2, D_Show_Tree, D_F_Read, D_Time };

Node *root = NULL, *EList = NULL;

Item *tab = NULL;

int main(void)
{
	setlocale(LC_ALL, "");
	int num;
	if (!Create_Tab(&tab, &root, &EList))
		return 0;
	while (num = dialog(msgs, NMsgs))
		if (!fptr[num]())
			break; // ��������� ����� �����
	printf("*** ��������� ������ ��������� ***\n");
	//free(tree);
	free(tab);
	system("pause");
	return 0;
}
//+++
int D_Time(void)
{
	int k, i;
	Node *x;
	printf("������� ����: ");
	if (!getInt(&k))
		return 0;
	float fTimeStart = clock() / (float)CLOCKS_PER_SEC;
	for (i = 0; i <= 1000000; i++)
		x = find(k);
	float fTimeStop = clock() / (float)CLOCKS_PER_SEC;
	if (x) {
		puts("���� ������ � ������");
		printf(" %d   %s\n", x->key, x->info);
	}
	else
		puts("���� �� ������ � ������");
	printf("������������ �������� %f * 10^-6 ������\n", fTimeStop - fTimeStart);
	return 1;
}
//+++
int D_F_Read(void)
{
	char *fname, *info;
	int n, k;
	scanf_s("%*c");
	printf("������� �������� �����: ");
	fname = getStr();
	if (!fname)
		return 0;
	fopen_s(&fd, fname, "r+");
	if (fd == NULL)
	{
		printf("���� � ����� ��������� �� ������\n");
		return 1;
	}
	while (1) {
		n = FgetInt(&k);
		if (n == 0)
			break; // ��������� ����� �����
		fscanf_s(fd, "%*c");
		info = FgetStr();
		if (!info)
			break;  // ��������� ����� �����
		if (!Search(k))
			printf("������������ ����� %d\n", k);
		else {
			Node *x = (Node *)calloc(1, sizeof(Node));
			x->key = k;
			x->info = info;
			x = RB_Insert(x);
			Tab_Insert(x);
		}
	}
	fclose(fd);
	puts("***���������� ���������***");
	return 1;
}
//+++
char *FgetStr(void)
{
	char *ptr = (char *)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = fscanf_s(fd, "%80[^\n]", buf, 81);
		if (n < 0) {
			return ptr;
		}
		if (n == 0)
			fscanf_s(fd, "%*c");
		else {
			len += strlen(buf);
			ptr = (char *)realloc(ptr, len + 1);
			strcat_s(ptr, (strlen(ptr) + 1 + strlen(buf)), buf);
		}
	} while (n > 0);
	return ptr;
}
//+++
int FgetInt(int *a)
{
	int n;
	do {
		n = fscanf_s(fd, "%d", a, sizeof(int));
		if (n < 0)
			return 0;
		if (n == 0) {
			printf("������ �����. ���������:\n");
			fscanf_s(fd, "%*[^\n]");
		}
	} while (n == 0);
	return 1;
}
//+++
int D_Find2(void)
{
	Node *x, *ptr = root;
	int n, k;
	if (ptr == EList) {
		printf("������ �����, ����� ���������.\n");
		return 1;
	}
	puts("������� ����: ");
	n = getInt(&k);
	if (n == 0)
		return 0; // ��������� ����� �����
	else
		x = dopfind(k);
	if (x) {
		tab[hash(x->key)].key = x->key;
		tab[hash(x->key)].node = x;
		puts("��������� �������:");
		printf(" ���� ����������\n");
		printf("%5d %s\n", x->key, x->info);
	}
	else
		printf("��� ����������� ��������\n");
	return 1;
}
//+++
Node *dopfind(int k)
{
	Node *ptr = root, *max, *min;
	while (ptr != EList) {
		if (ptr->key == k) {
			max = Sled(ptr);
			min = Pred(ptr);
			if (max == EList) {
				if (min == EList)
					return 0;
				else
					return min;
			}
			else {
				if (min == EList)
					return max;
				else {
					if (max->key - k < k - min->key)
						return max;
					else
						return min;
				}
			}
		}
		else {
			if (k < ptr->key) {
				if (ptr->left != EList)
					ptr = ptr->left;
				else {
					max = ptr;
					min = Pred(ptr);
					if (max == EList) {
						if (min == EList)
							return 0;
						else
							return min;
					}
					else {
						if (min == EList)
							return max;
						else {
							if (max->key - k < k - min->key)
								return max;
							else
								return min;
						}
					}
				}
			}
			else {
				if (ptr->right != EList)
					ptr = ptr->right;
				else {
					max = Sled(ptr);
					min = ptr;
					if (max == EList) {
						if (min == EList)
							return 0;
						else
							return min;
					}
					else {
						if (min == EList)
							return max;
						else {
							if (max->key - k < k - min->key)
								return max;
							else
								return min;
						}
					}
				}
			}
		}
	}
}
//+++
int D_Show_Tree(void)
{
	Node *ptr = root;
	if (ptr != EList) {
		printf("������:\n");
		show_tree(ptr);
	}
	else
		puts("������ �����");
	return 1;
}
//+++
void show_tree(Node *ptr)
{
	int i = 0;
	if (ptr != EList) {
		w++;
		show_tree(ptr->right);
		w--;
		for (; i < w; i++)
			printf("               ");
		printf("%d) %d %d %s\n\n", w, ptr->key, ptr->color, ptr->info);
		w++;
		show_tree(ptr->left);
		w--;
	}
}
//+++
int D_Show(void)
{
	Node *ptr = root;
	if (ptr != EList) {
		printf("������:\n");
		printf(" ���� � ����������\n");
		show(ptr);
	}
	else
		puts("������ �����");
	return 1;
}
//+++
void show(Node *ptr)
{
	if (ptr != EList) {
		show(ptr->left);
		printf("%5d %d %s\n", ptr->key, ptr->color, ptr->info);
		show(ptr->right);
	}
}
//+++
void Tab_output(void)
{
	printf("�������:\n");
	for (int i = 0; i < SIZE; i++) {
		printf("%d. ", i);
		if (tab[i].busy)
			printf("%d\n", tab[i].key);
		else
			printf("�����\n");
	}
}
//+++
int D_Delete(void)
{
	Node *x;
	int n, k, r;
	if (root == EList) {
		printf("������ �����, ���������� ������� �������\n");
		return 1;
	}
	puts("������� ����: ");
	n = getInt(&k);
	if (n == 0)
		return 0; // ��������� ����� �����
	x = find(k);
	if (!x)
		puts("��� �������� � �������� ������");
	else {
		RB_Delete(x);
		if (tab[hash(k)].key == k)
			tab[hash(k)].busy = 0;
		puts("*** �������� �������� ��������� ������� ***");
	}
	return 1;
}
//+++
void RB_Delete(Node *x)
{
	Node *p = NULL, *y = NULL;
	if (x->left == EList || x->right == EList)
		y = x;
	else
		y = Sled(x);
	if (y->left == EList)
		p = y->right;
	else
		p = y->left;
	p->parent = y->parent;
	if (y->parent == EList)
		root = p;
	else
		if (y->parent->left == y)
			y->parent->left = p;
		else
			y->parent->right = p;
	if (x != y) {
		x->key = y->key;
		x->info = y->info;
	}
	if (y->color == 1)
		RB_Delete_Fixup(p);
}
//+++
void RB_Delete_Fixup(Node *x)

{
	Node *p = x->parent, *c = NULL; /*x � ������������� ���� ������; p = x->parent � ������������ ����; c = p->right (��� p->left) � ������ ������� ���� p*/
	while (x != root && x->color == 1) { //���������� ��������
		p = x->parent; //��������, � ����� ��������� ����� x:
		if (x == p->left) {
			c = p->right;
			if (c->color == 0) { //�������� ����� � c � p:
				c->color = 1;
				p->color = 0;
				Left_Rotate(p);
				c = p->right;
			}
			if (c->left->color == 1 && c->right->color == 1) { //��� ������� ������
				c->color = 0; //������� ������ �������
				x = p; //������������� ����� �� ������
			}
			else {
				if (c->right->color == 1) { //������ ������� c ������
					c->color = 0;
					c->left->color = 1;
					Right_Rotate(c);
					c = p->right;
				}
				c->color = p->color;
				p->color = 1;
				c->right->color = 1;
				Left_Rotate(p);
				x = root;
			}
		}
		else { // ���� �����, �� �������� left �� right
			c = p->left;
			if (c->color == 0) {
				c->color = 1;
				p->color = 0;
				Right_Rotate(p);
				c = p->left;
			}
			if (c->left->color == 1 && c->right->color == 1) {
				c->color = 0;
				x = p;
			}
			else {
				if (c->left->color == 1) {
					c->color = 0;
					c->right->color = 1;
					Left_Rotate(c);
					c = p->left;
				}
				c->color = p->color;
				p->color = 1;
				c->left->color = 1;
				Right_Rotate(p);
				x = root;
			}
		}
	}
	x->color = 1;
}
//+++
int D_Find1(void)
{
	Node *x;
	int n, k;
	if (root == EList) {
		printf("������ �����, ����� ���������.\n");
		return 1;
	}
	puts("������� ����: ");
	n = getInt(&k);
	if (n == 0)
		return 0; // ��������� ����� �����
	x = find(k);
	if (!x)
		puts("���������� �� �������");
	else {
		puts("��������� �������:");
		printf(" ���� ����������\n");
		printf("%5d %s\n", x->key, x->info);
	}
	return 1;
}
//+++
Node *find(int k)
{
	Node *ptr;
	int r = Search_Tab(k);
	if (r == -1) {  //������, �� �� �������
		ptr = Search_Tree(k);
		if (ptr) {  //�����
			tab[hash(k)].key = k;
			tab[hash(k)].node = ptr;
			return ptr;  //�����
		}
		else
			return 0;  //�� �����
	}
	if (r == 0)  //����� � ����
		return tab[hash(k)].node;
	else  //�� �����
		return 0;
}
//+++
int D_Add(void)
{
	int k, n;
	char *info = NULL;
	puts("������� ����: ");
	n = getInt(&k);
	if (n == 0)
		return 0; // ��������� ����� �����
	scanf_s("%*c");
	puts("������� ����������:");
	info = getStr();
	if (info == NULL)
		return 0; // ��������� ����� �����
	if (!Search(k))
		printf("������������ ����� %d\n", k);
	else {
		Node *x = (Node *)calloc(1, sizeof(Node));
		x->key = k;
		x->info = info;
		x = RB_Insert(x);
		Tab_Insert(x);
		puts("*** ���������� �������� ��������� ������� ***");
	}
	return 1;
}
//+++
void Tab_Insert(Node *x)
{
	tab[hash(x->key)].busy = 1;
	tab[hash(x->key)].key = x->key;
	tab[hash(x->key)].node = x;
}
//+++
int Search(int k)
{
	Node *ptr;
	int r = Search_Tab(k);
	if (r == -1) {
		ptr = Search_Tree(k);
		if (ptr) {
			tab[hash(k)].key = k;
			tab[hash(k)].node = ptr;
			return 0; //�����
		}
		else
			return 1;  //�� �����
	}
	if (r == 0)
		return 0; //�����
	else
		return 1;	//�� �����
}
//+++
Node *Search_Tree(int k)
{
	Node *ptr = root;
	while (ptr != EList) {
		if (ptr->key == k)
			return ptr;
		else {
			if (k < ptr->key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}
	return 0;
}
//+++
int Search_Tab(int k)
{
	if (!tab[hash(k)].busy)
		return 1;  //������ �� ������
	else {
		if (tab[hash(k)].key == k)
			return 0; //����� � ����
		else
			return -1;  //������, �� �� �������
	}
}
//+++
Node *RB_Insert(Node *x)
{
	Node *prev = EList, *ptr = root;   //������� � �������� ������   
	while (ptr != EList) {
		prev = ptr;
		if (x->key < ptr->key)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	x->parent = prev;
	if (prev == EList)
		root = x;
	else {
		if (x->key < prev->key)
			prev->left = x;
		else
			prev->right = x;
	}
	x->left = EList;
	x->right = EList;
	x->color = 0;
	RB_Insert_Fixup(x);
	return x;
}
//+++
void RB_Insert_Fixup(Node *z)
{
	Node *pp, *p1, *p2, *ptr = root;
	while (z->parent->color == 0) {
		p1 = z->parent;
		pp = p1->parent;
		if (p1 == pp->left) {
			p2 = pp->right;
			if (p2->color == 0) {  //������ 1
				p1->color = 1;
				p2->color = 1;
				pp->color = 0;
				z = pp;
			}
			else {
				if (z == p1->right) {  //������ 2
					z = p1;
					Left_Rotate(z);
					p1 = z->parent;
				}
				p1->color = 1;  //������ 3
				pp->color = 0;
				Right_Rotate(pp);
			}
		}
		else {
			p2 = pp->left;
			if (p2->color == 0) {  //������ 1
				p1->color = 1;
				p2->color = 1;
				pp->color = 0;
				z = pp;
			}
			else {
				if (z == p1->left) {  //������ 2
					z = p1;
					Right_Rotate(z);
					p1 = z->parent;
				}

				p1->color = 1;  //������ 3
				pp->color = 0;
				Left_Rotate(pp);
			}
		}
	}
	root->color = 1;
}
//+++
void Left_Rotate(Node *x)
{
	//Node *ptr = root;
	Node * y = x->right; //*p = x->parent;
	x->right = y->left;  //������������ ����� x-����� ��������� y
	if (y->left != EList)
		y->left->parent = x;
	y->parent = x->parent;  //������������ ����� p-y
	if (x->parent == EList)
		root = y;
	else {
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;  //������������ ����� y-x
	x->parent = y;
}
//+++
void Right_Rotate(Node *x)
{
	Node * y = x->left; //*p = x->parent;
	x->left = y->right;  //������������ ����� x-����� ��������� y
	if (y->right != EList)
		y->right->parent = x;
	y->parent = x->parent;  //������������ ����� p-y
	if (x->parent == EList)
		root = y;
	else {
		if (x->parent->right == x)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	y->right = x;  //������������ ����� y-x
	x->parent = y;
}
//+++
int dialog(const char *msgs[], int N)
{
	char *errmsg = "";
	int num;
	int i, n;
	do {
		puts(errmsg);
		errmsg = "�� ��������! ��������� ����";	// ����� ������ �����������
		for (i = 0; i < N; ++i)
			puts(msgs[i]);
		puts("������� ����� ������������ ��������: ");
		n = getInt(&num); // ���� No ������������
		if (n == 0) // ����� ����� � ����� ������
			num = 0;
	} while (num < 0 || num >= N);
	return num;
}
//+++
int getInt(int *a)
{
	int n;
	do {
		n = scanf_s("%d", a, sizeof(int));
		if (n < 0)
			return 0;
		if (n == 0) {
			printf("������ �����. ���������:\n");
			scanf_s("%*[^\n]");
		}
	} while (n == 0);
	return 1;
}
//+++
char *getStr(void)
{
	char *ptr = (char *)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = scanf_s("%80[^\n]", buf, 81);
		if (n < 0) {
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0)
			scanf_s("%*c");
		else {
			len += strlen(buf);
			ptr = (char *)realloc(ptr, len + 1);
			strcat_s(ptr, (strlen(ptr) + 1 + strlen(buf)), buf);
		}
	} while (n > 0);
	return ptr;
}
//+++
int hash(int key)
{
	if (key < 0)
		key = -key;
	return key%SIZE;
}
//+++
Node *Sled(Node *x)
{
	Node *ptr;
	if (x->right != EList) {
		ptr = Min(x->right);
		return ptr;
	}
	ptr = x->parent;
	while (ptr != EList && x == ptr->right) {
		x = ptr;
		ptr = x->parent;
	}
	return ptr;
}
//+++
Node *Pred(Node *x)
{
	Node *ptr;
	if (x->left != EList) {
		ptr = Max(x->left);
		return ptr;
	}
	ptr = x->parent;
	while (ptr != EList && x == ptr->left) {
		x = ptr;
		ptr = x->parent;
	}
	return ptr;
}
//+++
Node *Min(Node *ptr)
{
	if (ptr == EList)
		return EList;
	else
		while (ptr->left != EList)
			ptr = ptr->left;
	return ptr;
}
//+++
Node *Max(Node *ptr)
{
	if (ptr == EList)
		return EList;
	else
		while (ptr->right != EList)
			ptr = ptr->right;
	return ptr;
}
//+++
int Create_Tab(Item **tab, Node **root, Node **EList)
{
	int i = 0;
	*EList = (Node *)calloc(1, sizeof(Node));
	(*EList)->color = 1;
	(*EList)->info = NULL;
	(*EList)->parent = NULL;
	(*EList)->right = NULL;
	(*EList)->left = NULL;
	(*EList)->info = NULL;
	*root = *EList;
	*tab = (Item *)calloc(SIZE, sizeof(Item));
	for (i; i < SIZE; i++) {
		(*tab)[i].busy = 0;
		(*tab)[i].node = NULL;
	}
	return 1;
}