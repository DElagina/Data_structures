// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "locale.h"
#include "malloc.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "float.h"

const char *msgs[] = { "0. Выход", "1. Добавление новой вершины",
"2. Добавление нового ребра", "3. Удаление вершины", "4. Поиск кратчайшего пути между двумя заданными вершинами",
"5. Вывод графа", "6. Таймирование поиска" };

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

FILE* fd;

typedef struct Versh {
	char *name;
	int x, y;
} Versh;

typedef struct HList {
	struct Versh Hversh;
	struct List *head;
} HList;

typedef struct List {
	struct Versh versh;
	struct List *next, *prev;
	struct HList *HVersh;
} List;

typedef struct Graph {
	int versh;
	char *fname;
	struct HList **adj;
} Graph;

typedef struct Mnozh {
	double d;
	int visit, pred;
} Mnozh;

int D_Show(Graph * gr);
int D_Delete(Graph * gr);
int D_AddVertex(Graph * gr);
int D_AddEdge(Graph * gr);
int dialog(const char *msgs[], int N);
int getInt(int *a);
char *getStr(void);
int D_Time(Graph * gr);
int D_Find(Graph * gr);
double Rasst(Versh *a, Versh *b);
int CreateAdj(Graph *gr);
int find_vertex_by_name(Graph *gr, char *name);
int find_vertex_by_coordinates(Graph *gr, int x, int y);
void graph_add_vertex(Graph *gr, Versh new_vertex, int i);
int graph_add_edge(HList *hlist_1, HList *hlist_2);
int FgetInt(int *a);
char *FgetStr(void);
void gr_del_versh(Graph *graph, int index);
void del_Item(List **deleted_item);
int Extract_Min(Graph *gr, Mnozh *S);
int Dijkstra(Graph *gr, HList *s, HList *p);
void load_file(Graph *gr);
void deleteGraph(Graph* gr);
Graph * generate_graph(int n);
double Dijkstra_Time(Graph *gr, HList *s, HList *p);

int(*fptr[])(Graph * gr) = { NULL, D_AddVertex, D_AddEdge, D_Delete,  D_Find, D_Show, D_Time };

const int MAX = 200;

int main(void)
{
	setlocale(LC_ALL, "");
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	int num;
	if (!CreateAdj(graph))
		return 0;
	while (num = dialog(msgs, NMsgs))
		if (!fptr[num](graph))
			break; // обнаружен конец файла
	load_file(graph);
	deleteGraph(graph);
	printf("*** Закончена работа программы ***\n");
	system("pause");
	return 0;
}

void deleteGraph(Graph* gr)
{
	int i;
	List *ptr;
	for (i = 0; i < gr->versh; i++) {
		while (gr->adj[i]->head) {
			ptr = gr->adj[i]->head;
			gr->adj[i]->head = gr->adj[i]->head->next;
			ptr->next = NULL;
			ptr->prev = NULL;
			ptr->HVersh = NULL;
			free(ptr);
		}
		free(gr->adj[i]);
	}
}

int CreateAdj(Graph *gr)
{
	char *fname;
	printf("Введите название файла: ");
	fname = getStr();
	if (!fname)
		return 0;
	fopen_s(&fd, fname, "rt");
	if (fd) {
		int vertex_amount, i, ind1, ind2;
		Versh new_vertex;
		char *name_1, *name_2;
		puts("* Чтение из существующего файла *");
		gr->fname = fname;
		if (!FgetInt(&vertex_amount))
			return 0;
		gr->versh = vertex_amount;
		if (!gr->versh) {
			gr->adj = NULL;
			puts("*** Граф успешно считан из файла ***");
			return 1;
		}
		gr->adj = (HList**)realloc(gr, (gr->versh+1)*sizeof(HList));
		for (i = 0; i < vertex_amount; ++i) {
			FgetInt(&new_vertex.x);
			fscanf_s(fd, "%*c"); //skipping space
			FgetInt(&new_vertex.y);
			fscanf_s(fd, "%*c"); //skipping space
			new_vertex.name = FgetStr();
			graph_add_vertex(gr, new_vertex, i+1);
		}
		while (!feof(fd)) { //Getting all edges
			name_1 = FgetStr();
			if (!name_1)
				return 0;
			if (feof(fd))
				break; //eof
			name_2 = FgetStr();
			if (!name_2)
				return 0;
			if (feof(fd))
				break; //eof
			ind1 = find_vertex_by_name(gr, name_1); //Guaranteed to be found
			ind2 = find_vertex_by_name(gr, name_2);
			graph_add_edge(gr->adj[ind1], gr->adj[ind2]);
		}
		puts("*** Граф успешно считан из файла ***");
		fclose(fd);
		return 1;
	}
	else {
		puts("* Создание нового файла *");
		gr->fname = fname;
		srand((unsigned)time(NULL));
		int n, i, j, s;
		do {
			s = 0;
			printf("Введите число вершин графа: ");
			if (!getInt(&n))
				return 0;
			if (n < 0)
				puts("Число вершин не может быть отрицательным. Повторите ввод");
			else
				s = 1;
		} while (!s);
		gr->versh = 0;
		if (!n) {
			gr->adj = NULL;
			puts("*** Граф и файл созданы успешно ***");
			return 1;
		}
		Versh* new_versh = (Versh *)calloc(1, sizeof(Versh));
		for (i = 0; i < n; i++) {
			do {
				new_versh->x = rand() % MAX - MAX / 2;
				new_versh->y = rand() % MAX - MAX / 2;
				new_versh->name = (char *)calloc((i / 10)+1, sizeof(char));
				sprintf_s(new_versh->name, (i/10 +2)*sizeof(char), "%d", i);
			} while (find_vertex_by_name(gr, new_versh->name) != -1 || find_vertex_by_coordinates(gr, new_versh->x, new_versh->y) != -1);
			if (gr->versh)
				gr->adj = (HList **)realloc(gr->adj, (gr->versh + 1)*sizeof(HList));
			else
				gr->adj = (HList **)calloc(1, sizeof(HList));
			gr->versh++;
			graph_add_vertex(gr, *new_versh, gr->versh);
		}
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (rand() % 2) 
					graph_add_edge(gr->adj[i], gr->adj[j]);
			}
		}
		puts("*** Граф создан успешно ***");
	}
	return 1;
}

void load_file(Graph *gr)
{
	char *fname = gr->fname;
	fopen_s(&fd, fname, "wt");
	fprintf(fd, "%d\n", gr->versh);
	int i;
	List *ptr;
	for (i = 0; i < gr->versh; i++) 
		fprintf(fd, "%d %d %s\n", gr->adj[i]->Hversh.x, gr->adj[i]->Hversh.y, gr->adj[i]->Hversh.name);
	for (i = 0; i <gr->versh; ++i) {
		ptr = gr->adj[i]->head;
		while (ptr) {
			fprintf(fd, "%s\n%s\n", gr->adj[i]->Hversh.name, ptr->versh.name);
			ptr = ptr->next;
		}
	}
	fclose(fd);
} 

int Dijkstra(Graph *gr, HList *s, HList *p)
{
	int i, indS, indP, w=0, index, a;
	Mnozh *S = (Mnozh*)calloc(gr->versh, sizeof(Mnozh));
	for (i = 0; i < gr->versh; i++) {
		if (gr->adj[i] == p)
			indP = i;
		if (gr->adj[i] == s) {
			indS = i;
			S[i].d = 0;
			S[i].pred = -1;
			S[i].visit = 0;
			continue;
		}
		S[i].d = DBL_MAX;
		S[i].pred = -1;
		S[i].visit = 0;
	}
	int* Q = (int*)calloc(gr->versh, sizeof(int));
	for (i = 0; i < gr->versh; i++) 
		Q[i] = i;
	List *ptr;
	int num, k;
	for (k = 0; k < gr->versh; k++) {
		index = Extract_Min(gr, S);
		if (index) {
			a = Q[0];
			Q[0] = Q[index]; 
			Q[index] = a;
		}
		ptr = gr->adj[Q[0]]->head;
		while (ptr) {
			num = find_vertex_by_name(gr, ptr->versh.name);
			if (S[num].d > S[Q[0]].d + Rasst(&gr->adj[num]->Hversh, &gr->adj[Q[0]]->Hversh)) {
				S[num].d = S[Q[0]].d + Rasst(&gr->adj[num]->Hversh, &gr->adj[Q[0]]->Hversh);
				S[num].pred = Q[0];
			}
			ptr = ptr->next;
		}
		S[Q[0]].visit = 1;
		for (i = 0; i < (gr->versh-k-1); i++) 
			Q[i] = Q[i + 1];
	}
	if (S[indP].d == DBL_MAX) {
		puts("Нет пути между этими вершинами");
		return 1;
	}
	printf("Длина пути между заданными вершинами: %5.1f\n", S[indP].d);
	puts("Путь:");
	int posled=indP;
	do {
		printf("{%d, %d} %s\n", gr->adj[posled]->Hversh.x, gr->adj[posled]->Hversh.y, gr->adj[posled]->Hversh.name);
		posled = S[posled].pred;
	} while (posled != -1);
	return 1;
}

double Dijkstra_Time(Graph *gr, HList *s, HList *p)
{
	int i, indS, indP, w = 0, index, a;
	Mnozh *S = (Mnozh*)calloc(gr->versh, sizeof(Mnozh));
	for (i = 0; i < gr->versh; i++) {
		if (gr->adj[i] == p)
			indP = i;
		if (gr->adj[i] == s) {
			indS = i;
			S[i].d = 0;
			S[i].pred = -1;
			S[i].visit = 0;
			continue;
		}
		S[i].d = DBL_MAX;
		S[i].pred = -1;
		S[i].visit = 0;
	}
	int* Q = (int*)calloc(gr->versh, sizeof(int));
	for (i = 0; i < gr->versh; i++)
		Q[i] = i;
	List *ptr;
	int num, k;
	for (k = 0; k < gr->versh; k++) {
		index = Extract_Min(gr, S);
		if (index) {
			a = Q[0];
			Q[0] = Q[index]; 
			Q[index] = a;
		}
		ptr = gr->adj[Q[0]]->head;
		while (ptr) {
			num = find_vertex_by_name(gr, ptr->versh.name);
			if (S[num].d > S[Q[0]].d + Rasst(&gr->adj[num]->Hversh, &gr->adj[Q[0]]->Hversh)) {
				S[num].d = S[Q[0]].d + Rasst(&gr->adj[num]->Hversh, &gr->adj[Q[0]]->Hversh);
				S[num].pred = Q[0];
			}
			ptr = ptr->next;
		}
		S[Q[0]].visit = 1;
		for (i = 0; i < (gr->versh - k - 1); i++)
			Q[i] = Q[i + 1];
	}
	return S[indP].d;
}

int Extract_Min(Graph *gr, Mnozh *S)
{
	double min = S[0].d;
	int ind = 0, i;
	for (i = 1; i < gr->versh; i++) {
		if (!S[i].visit) 
			if (min > S[i].d) {
				min = S[i].d;
				ind = i;
			}
	}
	return ind;
}

int D_Time(Graph *gr)
{
	int lower_border, upper_border, step, n, max, j, i;
	double result_time, d;
	char *file_name;
	FILE *result_file;
	clock_t start_time, stop_time, total_time;
	load_file(gr);
	deleteGraph(gr);
	printf("Введите нижнюю границу числа вершин в графе: ");
	if (!getInt(&lower_border))
		return 0; //eof
	printf("Введите верхнюю границу числа вершин в графе: ");
	if (!getInt(&upper_border))
		return 0; //eof
	printf("Введите шаг смещения: ");
	if (!getInt(&step))
		return 0; //eof
	printf("Введите имя .csv файла: ");
	scanf_s("%*c");
	if (!(file_name = getStr()))
		return 0; //eof
	max = 2 * upper_border;
	fopen_s(&result_file, file_name, "wt");
	n = lower_border;
	while (n <= upper_border)
	{
		gr = generate_graph(n);
		printf("%d elements in graph\n", n);
		start_time = clock();  //timing
		for (j = 0; j < gr->versh; ++j)
			for (i = 0; i < gr->versh; i++)
				d = Dijkstra_Time(gr, gr->adj[i], gr->adj[j]);
		stop_time = clock();
		total_time = stop_time - start_time;
		result_time = (double)total_time / ((double)CLOCKS_PER_SEC * (double)gr->versh) * (double)1000; //milliseconds
		fprintf(result_file, "%d;%f\n", n, result_time);
		deleteGraph(gr);
		n += step;  //next iteration
	}
	fclose(result_file);
	puts("*** Таймирование проведено успешно ***");
	return 1;
}

Graph * generate_graph(int n)
{
	Graph *gr = (Graph *)malloc(sizeof(Graph));
	srand((unsigned)time(NULL));
	int i, j;
	gr->versh = 0;
	if (!n) {
		gr->adj = NULL;
		return gr;
	}
	Versh* new_versh = (Versh *)calloc(1, sizeof(Versh));
	for (i = 0; i < n; i++) {
		do {
			new_versh->x = rand() % MAX - MAX / 2;
			new_versh->y = rand() % MAX - MAX / 2;
			new_versh->name = (char *)calloc((i / 10) + 1, sizeof(char));
			sprintf_s(new_versh->name, (i / 10 + 2)*sizeof(char), "%d", i);
		} while (find_vertex_by_name(gr, new_versh->name) != -1 || find_vertex_by_coordinates(gr, new_versh->x, new_versh->y) != -1);
		if (gr->versh)
			gr->adj = (HList **)realloc(gr->adj, (gr->versh + 1)*sizeof(HList));
		else
			gr->adj = (HList **)calloc(1, sizeof(HList));
		gr->versh++;
		graph_add_vertex(gr, *new_versh, gr->versh);
	}
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			if (rand() % 2)
				graph_add_edge(gr->adj[i], gr->adj[j]);
		}
	}
	return gr;
}

int graph_add_edge(HList *hlist_1, HList *hlist_2)
{
	List *cur, *new_1;
	cur = hlist_1->head;
	if (cur) { 
		if (!(strcmp(cur->versh.name, hlist_2->Hversh.name))) //If strcmp == 0 => strings are equal
			return 0;
		while (cur->next) {
			cur = cur->next;
			if (!(strcmp(cur->versh.name, hlist_2->Hversh.name))) //If strcmp == 0 => strings are equal
				return 0;
		}
		new_1 = (List *)calloc(1, sizeof(List));
		new_1->versh = hlist_2->Hversh;
		new_1->next = NULL;
		new_1->prev = cur;
		cur->next = new_1;
	}
	else {
		new_1 = (List *)calloc(1, sizeof(List));
		new_1->versh = hlist_2->Hversh;
		new_1->next = NULL;
		new_1->prev = NULL;
		hlist_1->head = new_1;
	}
	new_1->HVersh = hlist_1;
	return 1;
}

int find_vertex_by_name(Graph *gr, char *name)
{
	int i;
	for (i = 0; i < gr->versh; ++i) 
		if (!strcmp(gr->adj[i]->Hversh.name, name)) //If strcmp == 0 => strings are equal
			return i;
	return -1; //Not found
}

int find_vertex_by_coordinates(Graph *gr, int x, int y)
{
	int i;
	for (i = 0; i < gr->versh; ++i)
		if (gr->adj[i]->Hversh.x == x && gr->adj[i]->Hversh.y == y) {
			return i;
		}
	return -1; //Not found
}

void graph_add_vertex(Graph *gr, Versh new_vertex, int i)
{
	HList *new_header;
	new_header = (HList *)calloc(1, sizeof(HList));
	new_header->Hversh = new_vertex;
	new_header->head = NULL;
	gr->adj[i - 1] = new_header;
}

int D_Show(Graph * gr)
{
	List *cur_item;
	printf("\n");
	HList *cur_header;
	if (gr->adj == NULL) { 
		puts("Граф пуст!");
		return 1;
	}
	int i;
	for (i = 0; i < gr->versh; ++i) {
		cur_header = gr->adj[i];
		cur_item = cur_header->head;
		printf("Вершина: {%d, %d} %s\n", cur_header->Hversh.x, cur_header->Hversh.y, cur_header->Hversh.name);
		if (cur_item) {
			puts("Смежные вершины: ");
			while (cur_item)
			{
				printf("{%4d, %4d} %5s - %5.1f\n", cur_item->versh.x, cur_item->versh.y, cur_item->versh.name, Rasst(&cur_item->versh,&cur_header->Hversh));
				cur_item = cur_item->next;
			}
		}
		else
			puts("Смежных вершин нет");
		printf("\n");
	}
	return 1;
}

int D_Delete(Graph * gr)
{
	int k = 0, ind;
	Versh v;
	char *errmsg = "";
	do {
		if (k)
			printf("%s", errmsg);
		printf("Введите имя удаляемой вершины: ");
		scanf_s("%*c");
		if (!(v.name = getStr()))
			return 0; //eof
		errmsg = "Нет вершины с таким именем!\n";
		k++;
	} while ((ind = find_vertex_by_name(gr, v.name)) < 0);
	gr_del_versh(gr, ind);
	puts("*** Вершина успешно удалена ***");
	return 1;
}

void gr_del_versh(Graph *gr, int index)
{
	int i;
	List *curr, *tmp;
	while (gr->adj[index]->head) {
		tmp = gr->adj[index]->head;
		gr->adj[index]->head = gr->adj[index]->head->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);		
	}
	for (i = 0; i < gr->versh; i++) {
		if (i == index)
			continue;
		curr = gr->adj[i]->head;
		if (curr && !strcmp(curr->versh.name, gr->adj[index]->Hversh.name)) {
			if (gr->adj[i]->head->next)
				gr->adj[i]->head = gr->adj[i]->head->next;
			else
				gr->adj[i]->head = NULL;
			curr->next = NULL;
			curr->prev = NULL;
			free(curr);
		}
		else {
			while (curr) {
				if (!strcmp(curr->versh.name, gr->adj[index]->Hversh.name)) {
						tmp = curr;
						if (curr->next)
							curr->prev->next = curr->next;
						else
							curr->prev->next = NULL;
						tmp->prev = NULL;
						tmp->next = NULL;
						free(tmp);
					break;
				}
				curr = curr->next;
			}
		}
	}
	free(gr->adj[index]); //Freeing header item
	for (i = index; i < gr->versh - 1; ++i)
		gr->adj[i] = gr->adj[i + 1];
	gr->versh--;
	gr->adj = (HList **)realloc(gr->adj, (gr->versh)*sizeof(HList));
	
}

void del_Item(List **deleted_item) //double pointer in case it is head
{
	List *temp;
	if ((*deleted_item)->prev)
	{ //It is not head of a list
		temp = *deleted_item;
		(*deleted_item)->prev->next = (*deleted_item)->next;
		free(temp);
	}
	else
	{ //It is head of a list
		temp = *deleted_item;
		if ((*deleted_item)->next)
			(*deleted_item)->next->prev = NULL; //Next element will be new head => no prev
		*deleted_item = (*deleted_item)->next;
		free(temp);
	}
}

int D_Find(Graph * gr)
{
	int k = 0, ind1, ind2;
	Versh v1, v2;
	char *errmsg = "";
	do {
		if (k)
			printf("%s", errmsg);
		printf("Введите имя первой вершины: ");
		scanf_s("%*c");
		if (!(v1.name = getStr()))
			return 0; //eof
		errmsg = "Нет вершины с таким именем!\n";
		k++;
	} while ((ind1 = find_vertex_by_name(gr, v1.name)) < 0);
	k = 0;
	do {
		if (k)
			printf("%s", errmsg);
		printf("Введите имя второй вершины: ");
		if (!(v2.name = getStr()))
			return 0;
		errmsg = "Нет вершины с таким именем!\n";
		k++;
	} while ((ind2 = find_vertex_by_name(gr, v2.name)) < 0);
	Dijkstra(gr, gr->adj[ind1], gr->adj[ind2]);
	return 1;
}

int D_AddVertex(Graph * gr)
{
	int k=0;
	Versh v;
	char *errmsg="";
	do
	{
		if (k)
			printf("%s", errmsg);
		printf("Введите имя вершины: ");
		scanf_s("%*c");
		if (!(v.name = getStr()))
			return 0; //eof
		errmsg = "Вершина с таким именем уже существует!\n";
		k++;
	} while ((find_vertex_by_name(gr, v.name)) >= 0);
	k = 0;
	do
	{
		if (k)
			printf("%s", errmsg);
		printf("Введите координату х: ");
		if (!getInt(&v.x))
			return 0; //eof
		printf("Введите координату y: ");
		if (!getInt(&v.y))
			return 0; //eof
		errmsg = "Вершина с такими координтами уже существует!\n";
		k++;
	} while (find_vertex_by_coordinates(gr, v.x, v.y) >= 0);
	if (gr->versh)
		gr->adj = (HList **)realloc(gr->adj, (gr->versh + 1)*sizeof(HList));
	else
		gr->adj = (HList **)calloc(1, sizeof(HList));
	gr->versh++;
	graph_add_vertex(gr, v, gr->versh);
	puts("*** Добавление вершины выполнено успешно ***");
	return 1;
}

int D_AddEdge(Graph * gr)
{
	int k=0, ind;
	Versh v1, v2;
	HList *hlist_1, *hlist_2;
	char *errmsg = "";
	do {
		if (k)
			printf("%s", errmsg);
		printf("Введите имя первой вершины: ");
		scanf_s("%*c");
		if (!(v1.name = getStr()))
			return 0; //eof
		errmsg = "Нет вершины с таким именем!\n";
		k++;
	} while ((ind = find_vertex_by_name(gr, v1.name)) < 0);
	hlist_1 = gr->adj[ind];
	k = 0;
	do {
		if (k)
			printf("%s", errmsg);
		printf("Введите имя второй вершины: ");
		if (!(v2.name = getStr()))
			return 0;
		errmsg = "Нет вершины с таким именем!\n";
		k++;
	} while ((ind = find_vertex_by_name(gr, v2.name)) < 0);
	hlist_2 = gr->adj[ind];
	if (!graph_add_edge(hlist_1, hlist_2)) {
		puts("В графе уже есть такое ребро");
		return 1;
	}
	puts("*** Добавление ребра выполнено успешно ***");
	return 1;
}

double Rasst(Versh *a, Versh *b)
{
	double d = sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
	return d;
}

int dialog(const char *msgs[], int N)
{
	char *errmsg = "";
	int num;
	int i, n;
	do {
		puts(errmsg);
		errmsg = "Вы ошиблись! Повторите ввод";	// вывод списка альтернатив
		for (i = 0; i < N; ++i)
			puts(msgs[i]);
		printf("Введите номер выполняемого действия: ");
		n = getInt(&num); // ввод No альтернативы
		if (n == 0) // конец файла – конец работы
			num = 0;
	} while (num < 0 || num >= N);
	return num;
}

int getInt(int *a)
{
	int n;
	do {
		n = scanf_s("%d", a, sizeof(int));
		if (n < 0)
			return 0;
		if (n == 0) {
			printf("Ошибка ввода. Повторите:\n");
			scanf_s("%*[^\n]");
		}
	} while (n == 0);
	return 1;
}

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

char *FgetStr(void)
{
	char *ptr = (char *)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = fscanf_s(fd, "%80[^\n]", buf, 81);
		if (n < 0) 
			return ptr;
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

int FgetInt(int *a)
{
	int n;
	do {
		n = fscanf_s(fd, "%d", a, sizeof(int));
		if (n < 0)
			return 0;
		if (n == 0) {
			printf("Ошибка ввода. Повторите:\n");
			fscanf_s(fd, "%*[^\n]");
		}
	} while (n == 0);
	return 1;
}