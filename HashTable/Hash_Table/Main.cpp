#define _CRT_SECURE_NO_WARNINGS 

#include "IDictionary.h"
#include "IDictionaryOpenAddressing.h"
#include "IDictionarySeperateChanging.h"
#include "ArraySequence.h"
#include "Generator.h"
#include <ctime>
#include <fstream>

const char *msgs2[] = { "1. Ручной ввод последовательности",
"2. Автоматическое заполнение последовательности", "3. Построение хеш-таблицы из последовательности", "4. Вывод последовательности", "0. Выход" };
const char *msgs3[] = { "1. Перемешивание сложением",
"2. Перемешивание сцеплением", "0. Выход" };
const char *msgs5[] = { "1. Произвольная последовательность",
"2. Отсортированная в обратном порядке", "3. Отсортированная в правильном порядке", "0. Слишком много вопросов, передумал(а)" };
const char *msgs6[] = { "1. Вывод таблицы", "2. Вставка элемента в таблицу", "3. Удаление элемента из таблицы",
"4. Поиск элемента в таблице по ключу", "0. Назад к последовательности" };

const int NMsgs2 = sizeof(msgs2) / sizeof(msgs2[0]);
const int NMsgs3 = sizeof(msgs3) / sizeof(msgs3[0]);
const int NMsgs5 = sizeof(msgs5) / sizeof(msgs5[0]);
const int NMsgs6 = sizeof(msgs6) / sizeof(msgs6[0]);

template <class TElement> int Dialog_Create_Auto(ArraySequence<TElement>* seq);
template <class TElement> int getNum(TElement &a);
template <class TElement> int Dialog_Enter(ArraySequence<TElement>* seq);
template <class TElement> int Dialog_SequenceShow(ArraySequence<TElement>* seq);
template <class TElement> int HashBuild(ArraySequence<TElement>* seq);
int dialog(const char *msgs[], int N);

int main()
{
	setlocale(LC_ALL, "rus");
	int num1;
	ArraySequence<int>* seq = new ArraySequence<int>();
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
			HashBuild(seq);
			break;
		case 4:
			Dialog_SequenceShow(seq);
			break;
		default:
			cout << "Произошла ошибка в ходе выполнения программы" << endl;
			break;
		}
	seq->DeleteSeq();
	cout << "     *** Закончена работа программы ***" << endl;
	system("pause");
	return 0;
}

template <class TElement>
int HashBuild(ArraySequence<TElement>* seq)
{
	int num, num1, n;
	const char* pr = "";
	TElement key, element;
	do
	{
		cout << pr << endl;
		cout << "Введите размер хеш-таблицы: ";
		pr = "Вы ошиблись! Повторите ввод";
		if (getNum(n) < 0)
			return 0;
	} while (n <= 0);
	num = dialog(msgs3, NMsgs3);
	IDictionary<TElement, TElement>* table = nullptr;
	switch (num)
	{
	case 1:
		table = new IDictionaryOpenAddressing<TElement, TElement>(n);
		break;
	case 2:
		table = new IDictionarySeparateChanging<TElement, TElement>(n);
		break;
	case 0:
		return 1;
	default:
		cout << "Произошла ошибка в ходе выполнения программы" << endl;
		break;
	}
	for (int i = 0; i < seq->Length(); ++i)
	{
		try
		{
			table->Add(seq->Get(i), seq->Get(i));
		}
		catch (Exception* e)
		{
			e->Show();
		}
	}
	while (num1 = dialog(msgs6, NMsgs6))
		switch (num1)
		{
		case 1:
		{
			table->Show();
			break;
		};
		case 2:
			cout << "Введите элемент: ";
			if (getNum(element) < 0)
				return 0;
			try
			{
				table->Add(element, element);
			}
			catch (Exception* e)
			{
				e->Show();
			}
			break;
		case 3:
			cout << "Введите ключ удаляемого элемента: ";
			if (getNum(key) < 0)
				return 0;
			try
			{
				table->Remove(key);
			}
			catch (Exception* e)
			{
				e->Show();
			}
			break;
		case 4:
			cout << "Введите ключ искомого элемента: ";
			if (getNum(key) < 0)
				return 0;
			try
			{
				cout << "Найденный элемент: " << table->Get(key) << endl;
			}
			catch (Exception* e)
			{
				e->Show();
			}
		}
	table->DeleteTable();
	return 1;
}

template <class TElement>
int Dialog_Enter(ArraySequence<TElement>* seq)
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
int Dialog_Create_Auto(ArraySequence<TElement>* seq)
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
		cout << "Произошла ошибка в ходе выполнения программы" << endl;
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
int Dialog_SequenceShow(ArraySequence<TElement>* seq)
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

//template <class TElement>
//int Time(ArraySequence<TElement>* Sseq)
//{
//	cout << "   *** Таймирование ***" << endl;
//
//	char *fname = new char[100];
//	double start_time, stop_time;
//	int lower_border, upper_border, step, n;
//
//	cout << "Введите название .csv файла: ";
//	scanf("%s", fname);
//	cout << endl;
//	ofstream F1;
//	F1.open(fname);
//	delete fname;
//	lower_border = 100;
//	upper_border = 400;
//	step = 50;
//	/*cout << "Введите нижнюю границу количества элементов в дереве: ";
//	if (getNum(lower_border) < 0)
//	return 0;
//	cout << "Введите верхнюю границу количества элементов в дереве: ";
//	if (getNum(upper_border) < 0)
//	return 0;
//	if (upper_border < lower_border)
//	{
//	int s = upper_border;
//	upper_border = lower_border;
//	lower_border = s;
//	}
//	cout << "Введите шаг: ";
//	if (getNum(step) < 0)
//	return 0;*/
//	Generator<TElement>* gen = new Generator<TElement>();
//	int TypeSeq = dialog(msgs5, NMsgs5);
//	int TypeHash = dialog(msgs3, NMsgs3);
//	n = lower_border;
//	while (n <= upper_border)
//	{
//		ArraySequence<TElement>* seq = new ArraySequence<TElement>();
//		switch (TypeSeq)
//		{
//		case 1:
//			try
//			{
//				seq = gen->RandGenerate(seq, n, upper_border, -upper_border);
//			}
//			catch (Exception* e)
//			{
//				e->Show();
//			}
//			break;
//		case 2:
//			try
//			{
//				seq = gen->GenerateDecreaseSequence(seq, n);
//			}
//			catch (Exception* e)
//			{
//				e->Show();
//			}
//			break;
//		case 3:
//			try
//			{
//				seq = gen->GenerateIncreaseSequence(seq, n);
//			}
//			catch (Exception* e)
//			{
//				e->Show();
//			}
//			break;
//		case 0:
//			return 1;
//		default:
//			cout << "Какие-то проблемки... :(" << endl;
//			break;
//		}
//		IDictionary<TElement, TElement>* table = nullptr;
//		switch (TypeHash)
//		{
//		case 1:
//			table = new IDictionaryOpenAddressing<TElement, TElement>(n + 50);
//			break;
//		case 2:
//			table = new IDictionarySeparateChanging<TElement, TElement>(n + 50);
//			break;
//		default:
//			cout << "Какие-то проблемки... :(" << endl;
//			break;
//		}
//		for (int i = 0; i < seq->Length(); ++i)
//		{
//			try
//			{
//				table->Add(seq->Get(i), seq->Get(i));
//				cout << i;
//			}
//			catch (Exception* e)
//			{
//				e->Show();
//			}
//		}
//		start_time = clock() / (float)CLOCKS_PER_SEC;
//		for (int i = 0; i < seq->Length(); ++i)
//			table->ContainsKey(seq->Get(i));
//		stop_time = clock() / (float)CLOCKS_PER_SEC;
//		table->DeleteTable();
//		cout << "Длительность процесса (мс): " << (stop_time - start_time) * 1000000000 / n << endl;
//		F1 << n << ";" << (stop_time - start_time) * 1000000 / n << endl;
//		delete gen;
//		seq->DeleteSeq();
//		n += step;
//	}
//	F1.close();
//	cout << "   *** Таймирование завершено ***" << endl;
//	return 1;
//}
