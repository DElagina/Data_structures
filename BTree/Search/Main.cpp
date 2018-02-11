
#include "Generator.h"
#include "BinaryTree.h"
#include "TreeBuilder.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "SortedSequence.h"
#include "B-Tree.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

const char *msgs1[] = { "1. Реализация массивом",
"2. Реализация списком", "0. Выход" };

const char *msgs3[] = { "1. Бинарное дерево",
"2. В-дерево", "0. Выход" };

const char *msgs2[] = { "1. Ручной ввод последовательности",
"2. Автоматическое заполнение последовательности", "3. Построение дерева из последовательности", "4. Вывод последовательности",
"5. Тестирование", "6. Таймирование различных видов сортировок", "0. Создание новой последовательности" };

const char *msgs4[] = { "1. Сортировка по возрастанию",
"2. Сортировка по убыванию", "0. Слишком много вопросов, передумал(а)" };

const char *msgs5[] = { "1. Произвольная последовательность",
"2. Отсортированная в обратном порядке", "3. Отсортированная в правильном порядке", "0. Слишком много вопросов, передумал(а)" };

const char *msgs6[] = { "1. Вывод дерева", "2. Вставка элемента в дерево", "3. Получение индекса элемента по ключу",
"4. Получение поддерева из дерева","5. Поиск элемента в дереве по ключу", "0. Назад к последовательности" };

const int NMsgs1 = sizeof(msgs1) / sizeof(msgs1[0]);
const int NMsgs2 = sizeof(msgs2) / sizeof(msgs2[0]);
const int NMsgs3 = sizeof(msgs3) / sizeof(msgs3[0]);
const int NMsgs4 = sizeof(msgs4) / sizeof(msgs4[0]);
const int NMsgs5 = sizeof(msgs5) / sizeof(msgs5[0]);
const int NMsgs6 = sizeof(msgs6) / sizeof(msgs6[0]);

template <class TElement> int Dialog_Create_Auto(Sequence<TElement>* seq);
template <class TElement> int getNum(TElement &a);
template <class TElement> void test(Sequence<TElement>* seq);
int dialog(const char *msgs[], int N);
template <class TElement> int Dialog_Enter(Sequence<TElement>* seq);
template <class TElement> int Dialog_SequenceShow(Sequence<TElement>* seq);
template <class TElement> int Time(Sequence<TElement>* Sseq);
template <class TElement> int TreeBuild(Sequence<TElement>* seq);

int main()
{
	setlocale(LC_ALL, "rus");
	Sequence<int>* seq = nullptr;
	int num, num1;
	while (num = dialog(msgs1, NMsgs1))
	{
		switch (num)
		{
		case 1:
			seq = new ArraySequence<int>();
			break;
		case 2:
			seq = new ListSequence<int>();
			break;
		default:
			cout << "Какие-то проблемки... :(" << endl;
			break;
		}
		while (num1 = dialog(msgs2, NMsgs2))
			switch (num1)
			{
			case 1:
				Dialog_Enter(seq);
				break;
			case 2:
				Dialog_Create_Auto(seq);
				break;
			case 3:
				TreeBuild(seq);
				break;
			case 4:
				Dialog_SequenceShow(seq);
				break;
			case 5:
				test(seq);
				break;
			case 6:
				Time(seq);
				break;
			default:
				cout << "Какие-то проблемки... :(" << endl;
				break;
			}
		seq->DeleteSeq();
	}
	cout << "     *** Закончена работа программы ***" << endl;
	system("pause");
	return 0;
}

template <class TElement>
int TreeBuild(Sequence<TElement>* seq)
{
	int num, num1, index;
	TElement element;
	int start, end;
	TreeBuilder<TElement, TElement>* builder = new TreeBuilder<TElement, TElement>();
	num = dialog(msgs3, NMsgs3);
	switch (num)
	{
	case 1:
	{
		BinaryTree<TElement, TElement>* tree = builder->BinaryTreeBuilder(seq);
		while (num1 = dialog(msgs6, NMsgs6))
			switch (num1)
			{
			case 1:
				tree->Show();
				break;
			case 2:
				cout << "Введите элемент: ";
				if (getNum(element) < 0)
					return 0;
				tree->Add(element, element);
				break;
			case 3:
				cout << "Введите ключ искомого элемента: ";
				if (getNum(element) < 0)
					return 0;
				try
				{
					index = tree->IndexOf(element);
					if (index < 0)
						cout << "Элемент с ключом " << element << " не найден!" << endl;
					else
						cout << "Индекс = " << index << endl;
				}
				catch (Exception* e)
				{
					e->Show();
				}
				break;
			case 4:
				cout << "Введите индекс начала подпоследовательности: ";
				if (getNum(start) < 0)
					return 0;
				cout << "Введите индекс конца подпоследовательности: ";
				if (getNum(end) < 0)
					return 0;
				try
				{
					BinaryTree<TElement, TElement>* newtree = tree->GetSubsequence(start, end);
					cout << "Подпоследовательность: " << endl;
					newtree->Show();
					newtree->DeleteTree();
				}
				catch (Exception* e)
				{
					e->Show();
				}
				break;
			case 5:
				cout << "Введите ключ искомого элемента: ";
				if (getNum(element) < 0)
					return 0;
				try
				{
					cout << "Найденный элемент: " << tree->Search(element) << endl;
				}
				catch (Exception* e)
				{
					e->Show();
				}
			}
		tree->DeleteTree();
		break;
	}
	case 2:
	{	BTree<TElement, TElement>* btree = builder->BTreeBuilder(seq);
		while (num1 = dialog(msgs6, NMsgs6))
			switch (num1)
			{
			case 1:
				btree->Show();
				break;
			case 2:
				cout << "Введите элемент: ";
				if (getNum(element) < 0)
					return 0;
				btree->Add(&btree, element, element);
				break;
			case 3:
				cout << "Введите ключ искомого элемента: ";
				if (getNum(element) < 0)
					return 0;
				try
				{
					index = btree->IndexOf(element);
					if (index < 0)
						cout << "Элемент с ключом " << element << " не найден!" << endl;
					else
						cout << "Индекс = " << index << endl;
				}
				catch (Exception* e)
				{
					e->Show();
				}
				break;
			case 4:
				cout << "Введите индекс начала подпоследовательности: ";
				if (getNum(start) < 0)
					return 0;
				cout << "Введите индекс конца подпоследовательности: ";
				if (getNum(end) < 0)
					return 0;
				try
				{
					BTree<TElement, TElement>* newbtree = btree->GetSubsequence(start, end);
					cout << "Подпоследовательность: " << endl;
					newbtree->Show();
					newbtree->DeleteTree();
				}
				catch (Exception* e)
				{
					e->Show();
				}
				break;
			case 5:
				cout << "Введите ключ искомого элемента: ";
				if (getNum(element) < 0)
					return 0;
				try
				{
					cout << "Найденный элемент: " << btree->Search(element) << endl;
				}
				catch (Exception* e)
				{
					e->Show();
				}
			}
		btree->DeleteTree();
		break;
	}
	default:
		cout << "Какие-то проблемки... :(" << endl;
		break;
	}
	return 1;
}

template <class TElement>
int Dialog_Enter(Sequence<TElement>* seq)
{
	const char* pr = "";
	int n;
	do
	{
		cout << pr << endl;
		cout << "Введите количество элементов в последовательности: ";
		pr = "Вы ошиблись! Повторите ввод";
		if (getNum(n) < 0)
			return 0;
	} while (n < 0);
	if (!n)
		return 1;
	TElement a;
	cout << "Введите элементы последовательности: " << endl;
	for (int i = 0; i < n; i++)
	{
		if (getNum(a) < 0)
			return 0;
		seq->Append(a);
	}
	return 1;
}

template <class TElement>
int Dialog_Create_Auto(Sequence<TElement>* seq)
{
	const char* pr = "";
	int n, max, min, num;
	do
	{
		cout << pr << endl;
		cout << "Введите количество элементов в последовательности: ";
		pr = "Вы ошиблись! Повторите ввод";
		if (getNum(n) < 0)
			return 0;
	} while (n < 0);
	if (!n)
		return 1;
	Generator<TElement>* gen = new Generator<TElement>();
	switch (num = dialog(msgs5, NMsgs5))
	{
	case 3:
		seq = gen->GenerateIncreaseSequence(seq, n);
		break;
	case 2:
		seq = gen->GenerateDecreaseSequence(seq, n);
		break;
	case 1:
		cout << "Введите максимальное значение элемента: ";
		if (getNum(max) < 0)
			return 0;
		cout << "Введите минимальное значение элемента: ";
		if (getNum(min) < 0)
			return 0;
		seq = gen->RandGenerate(seq, n, max, min);
		return 1;
	case 0:
		return 1;
	default:
		cout << "Какие-то проблемки... :(" << endl;
		return 0;
	}
	delete gen;
	return 1;
}

template <class TElement>
int getNum(TElement &a)
{
	cin >> a;
	if (!cin.good())
		return -1;
	return 1;
}

template <class TElement>
void test(Sequence<TElement>* seq)
{
	cout << "     *** Тестирование начато ***" << endl;
	cout << "Тестирование бинарного дерева" << endl;
	int tests = 0, count = 0;
	TElement i1 = 1, i2 = 2, i3 = 3, i4 = 4, i0 = 0, ii1 = -1;
	BinaryTree<TElement, TElement>* tree = new BinaryTree<TElement, TElement>();
	cout << "Тест №" << ++tests << ": " << "Вывод пустой последовательности" << endl;
	try
	{
		tree->Show();
		cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
		cout << "Ок" << endl;
		++count;
	}
	cout << "Тест №" << ++tests << ": " << "Вставка 1" << endl;
	tree->Add(i1, i1);
	if (tree->Get() == 1)
	{
		cout << "Ок" << endl;
		++count;
	}
	else
		cout << "Ошибочка вышла" << endl;
	cout << "Тест №" << ++tests << ": " << "Вставка 3" << endl;
	tree->Add(i3, i3);
	if (tree->Right()->Get() == 3)
	{
		cout << "Ок" << endl;
		++count;
	}
	else
		cout << "Ошибочка вышла" << endl;
	cout << "Тест №" << ++tests << ": " << "Вставка 2" << endl;
	tree->Add(i2, i2);
	if (tree->Right()->Left()->Get() == 2)
	{
		cout << "Ок" << endl;
		++count;
	}
	else
		cout << "Ошибочка вышла" << endl;
	cout << "Тест №" << ++tests << ": " << "Индекс 0" << endl;
	try
	{
		if (tree->IndexOf(i0)==-1)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	cout << "Тест №" << ++tests << ": " << "Индекс 1" << endl;
	try
	{
		if (tree->IndexOf(i1) == 0)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	cout << "Тест №" << ++tests << ": " << "Индекс 2" << endl;
	try
	{
		if (tree->IndexOf(i2) == 1)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	cout << "Тест №" << ++tests << ": " << "Индекс 3" << endl;
	try
	{
		if (tree->IndexOf(i3) == 2)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	cout << "Тест №" << ++tests << ": " << "Индекс 4" << endl;
	try
	{
		if (tree->IndexOf(i4) == -1)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	BinaryTree<TElement, TElement>* newtree;
	cout << "Тест №" << ++tests << ": " << "Подпоследовательность (-1, -1)" << endl;
	try
	{
		newtree = tree->GetSubsequence(ii1, ii1);
		cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
		cout << "Ок" << endl;
		++count;
	}
	cout << "Тест №" << ++tests << ": " << "Подпоследовательность (1, 4)" << endl;
	try
	{
		newtree = tree->GetSubsequence(i1, i4);
		cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
		cout << "Ок" << endl;
		++count;
	}
	cout << "Тест №" << ++tests << ": " << "Подпоследовательность (1, 2)" << endl;
	try
	{
		newtree = tree->GetSubsequence(i1, i2);
		cout << "Ок" << endl;
		++count;
	}
	catch (Exception* e)
	{
		e->Show();
		cout << "Ошибочка вышла" << endl;
	}
	newtree->DeleteTree();
	tree->DeleteTree();

	cout << "Тестирование B-дерева" << endl;
	BTree<TElement, TElement>* btree = new BTree<TElement, TElement>();
	cout << "Тест №" << ++tests << ": " << "Вывод пустой последовательности" << endl;
	try
	{
		btree->Show();
		cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
		cout << "Ок" << endl;
		++count;
	}
	cout << "Тест №" << ++tests << ": " << "Вставка 1" << endl;
	btree->Add(&btree, i1, i1);
	cout << "Ок" << endl;
	++count;
	cout << "Тест №" << ++tests << ": " << "Вставка 3" << endl;
	btree->Add(&btree, i3, i3);
	cout << "Ок" << endl;
	++count;
	cout << "Тест №" << ++tests << ": " << "Вставка 2" << endl;
	btree->Add(&btree, i2, i2);
	cout << "Ок" << endl;
	++count;
	cout << "Тест №" << ++tests << ": " << "Индекс 0" << endl;
	try
	{
		if (btree->IndexOf(i0) == -1)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	cout << "Тест №" << ++tests << ": " << "Индекс 1" << endl;
	try
	{
		if (btree->IndexOf(i1) == 0)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	cout << "Тест №" << ++tests << ": " << "Индекс 2" << endl;
	try
	{
		if (btree->IndexOf(i2) == 1)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	cout << "Тест №" << ++tests << ": " << "Индекс 3" << endl;
	try
	{
		if (btree->IndexOf(i3) == 2)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	cout << "Тест №" << ++tests << ": " << "Индекс 4" << endl;
	try
	{
		if (btree->IndexOf(i4) == -1)
		{
			cout << "Ок" << endl;
			++count;
		}
		else
			cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
	}
	BTree<TElement, TElement>* newbtree;
	cout << "Тест №" << ++tests << ": " << "Подпоследовательность (-1, -1)" << endl;
	try
	{
		newbtree = btree->GetSubsequence(ii1, ii1);
		cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
		cout << "Ок" << endl;
		++count;
	}
	cout << "Тест №" << ++tests << ": " << "Подпоследовательность (1, 4)" << endl;
	try
	{
		newbtree = btree->GetSubsequence(i1, i4);
		cout << "Ошибочка вышла" << endl;
	}
	catch (Exception* e)
	{
		e->Show();
		cout << "Ок" << endl;
		++count;
	}
	cout << "Тест №" << ++tests << ": " << "Подпоследовательность (1, 2)" << endl;
	try
	{
		newbtree = btree->GetSubsequence(i1, i2);
		cout << "Ок" << endl;
		++count;
	}
	catch (Exception* e)
	{
		e->Show();
		cout << "Ошибочка вышла" << endl;
	}
	newbtree->DeleteTree();
	btree->DeleteTree();
	cout << "Всего тестов: " << tests << endl;
	cout << "Пройдено тестов: " << count << endl;
	cout << "     *** Тестирование завершено ***" << endl;
}

template <class TElement>
int Dialog_SequenceShow(Sequence<TElement>* seq)
{
	seq->Show();
	return 1;
}

int dialog(const char *msgs[], int N)
{
	char *errmsg = "";
	int num;
	do {
		puts(errmsg);
		errmsg = "Вы ошиблись! Повторите ввод";	// вывод списка альтернатив
		for (int i = 0; i < N; ++i)
			puts(msgs[i]);
		cout << "Введите номер выполняемого действия: " << endl;
		if (getNum(num) < 0) // ввод No альтернативы
			return 0;
	} while (num < 0 || num >= N);
	return num;
}

template <class TElement>
int Time(Sequence<TElement>* Sseq)
{
	cout << "   *** Таймирование ***" << endl;

	char *fname = new char[100];
	double start_time, stop_time;
	int lower_border, upper_border, step, n;

	cout << "Введите название .csv файла: ";
	scanf("%s", fname);
	cout << endl;
	ofstream F1;
	F1.open(fname);
	delete fname;
	lower_border = 1000;
	upper_border = 4000;
	step = 500;
	/*cout << "Введите нижнюю границу количества элементов в дереве: ";
	if (getNum(lower_border) < 0)
		return 0;
	cout << "Введите верхнюю границу количества элементов в дереве: ";
	if (getNum(upper_border) < 0)
		return 0;
	if (upper_border < lower_border)
	{
		int s = upper_border;
		upper_border = lower_border;
		lower_border = s;
	}
	cout << "Введите шаг: ";
	if (getNum(step) < 0)
		return 0;*/
	Generator<TElement>* gen = new Generator<TElement>();
	int TypeSeq = dialog(msgs5, NMsgs5);
	int TypeTree = dialog(msgs3, NMsgs3);
	n = lower_border;
	while (n <= upper_border)
	{
		Sequence<TElement>* seq = new ArraySequence<TElement>();
		switch (TypeSeq)
		{
		case 1:
			try
			{
				seq = gen->RandGenerate(seq, n, upper_border, -upper_border);
			}
			catch (Exception* e)
			{
				e->Show();
			}
			break;
		case 2:
			try
			{
				seq = gen->GenerateDecreaseSequence(seq, n);
			}
			catch (Exception* e)
			{
				e->Show();
			}
			break;
		case 3:
			try
			{
				seq = gen->GenerateIncreaseSequence(seq, n);
			}
			catch (Exception* e)
			{
				e->Show();
			}
			break;
		case 0:
			return 1;
		default:
			cout << "Какие-то проблемки... :(" << endl;
			break;
		}
		TreeBuilder<TElement, TElement>* builder = new TreeBuilder<TElement, TElement>();
		switch (TypeTree)
		{
		case 1:
		{
			start_time = clock() / (float)CLOCKS_PER_SEC;
			BinaryTree<TElement, TElement>* tree = builder->BinaryTreeBuilder(seq);
			stop_time = clock() / (float)CLOCKS_PER_SEC;
			tree->DeleteTree();
			break;
		}
		case 2:
		{	
			start_time = clock() / (float)CLOCKS_PER_SEC;
			BTree<TElement, TElement>* btree = builder->BTreeBuilder(seq);
			stop_time = clock() / (float)CLOCKS_PER_SEC;
			btree->DeleteTree();
			break;
		}
		default:
			cout << "Какие-то проблемки... :(" << endl;
			break;
		}
		cout << "Длительность процесса (мс): " << (stop_time - start_time)*1000000 << endl;
		F1 << n << ";" << (stop_time - start_time)*1000000 << endl;
		delete gen;
		seq->DeleteSeq();
		n += step;
	}
	F1.close();
	cout << "   *** Таймирование завершено ***" << endl;
	return 1;
}
