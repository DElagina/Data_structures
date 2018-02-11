#define _CRT_SECURE_NO_WARNINGS 

#include "IDictionary.h"
#include "IDictionaryOpenAddressing.h"
#include "IDictionarySeperateChanging.h"
#include "ArraySequence.h"
#include "Generator.h"
#include <ctime>
#include <fstream>

const char *msgs2[] = { "1. ������ ���� ������������������",
"2. �������������� ���������� ������������������", "3. ���������� ���-������� �� ������������������", "4. ����� ������������������", "0. �����" };
const char *msgs3[] = { "1. ������������� ���������",
"2. ������������� ����������", "0. �����" };
const char *msgs5[] = { "1. ������������ ������������������",
"2. ��������������� � �������� �������", "3. ��������������� � ���������� �������", "0. ������� ����� ��������, ���������(�)" };
const char *msgs6[] = { "1. ����� �������", "2. ������� �������� � �������", "3. �������� �������� �� �������",
"4. ����� �������� � ������� �� �����", "0. ����� � ������������������" };

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
			cout << "��������� ������ � ���� ���������� ���������" << endl;
			break;
		}
	seq->DeleteSeq();
	cout << "     *** ��������� ������ ��������� ***" << endl;
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
		cout << "������� ������ ���-�������: ";
		pr = "�� ��������! ��������� ����";
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
		cout << "��������� ������ � ���� ���������� ���������" << endl;
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
			cout << "������� �������: ";
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
			cout << "������� ���� ���������� ��������: ";
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
			cout << "������� ���� �������� ��������: ";
			if (getNum(key) < 0)
				return 0;
			try
			{
				cout << "��������� �������: " << table->Get(key) << endl;
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
		cout << "������� ���������� ��������� � ������������������: ";
		pr = "�� ��������! ��������� ����";
		if (getNum(n) < 0)
			return 0;
	} while (n < 0);
	if (!n)
		return 1;
	TElement a;
	cout << "������� �������� ������������������: " << endl;
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
		cout << "������� ���������� ��������� � ������������������: ";
		pr = "�� ��������! ��������� ����";
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
		cout << "������� ������������ �������� ��������: ";
		if (getNum(max) < 0)
			return 0;
		cout << "������� ����������� �������� ��������: ";
		if (getNum(min) < 0)
			return 0;
		seq = gen->RandGenerate(seq, n, max, min);
		return 1;
	case 0:
		return 1;
	default:
		cout << "��������� ������ � ���� ���������� ���������" << endl;
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
		errmsg = "�� ��������! ��������� ����";	// ����� ������ �����������
		for (int i = 0; i < N; ++i)
			puts(msgs[i]);
		cout << "������� ����� ������������ ��������: " << endl;
		if (getNum(num) < 0) // ���� No ������������
			return 0;
	} while (num < 0 || num >= N);
	return num;
}

//template <class TElement>
//int Time(ArraySequence<TElement>* Sseq)
//{
//	cout << "   *** ������������ ***" << endl;
//
//	char *fname = new char[100];
//	double start_time, stop_time;
//	int lower_border, upper_border, step, n;
//
//	cout << "������� �������� .csv �����: ";
//	scanf("%s", fname);
//	cout << endl;
//	ofstream F1;
//	F1.open(fname);
//	delete fname;
//	lower_border = 100;
//	upper_border = 400;
//	step = 50;
//	/*cout << "������� ������ ������� ���������� ��������� � ������: ";
//	if (getNum(lower_border) < 0)
//	return 0;
//	cout << "������� ������� ������� ���������� ��������� � ������: ";
//	if (getNum(upper_border) < 0)
//	return 0;
//	if (upper_border < lower_border)
//	{
//	int s = upper_border;
//	upper_border = lower_border;
//	lower_border = s;
//	}
//	cout << "������� ���: ";
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
//			cout << "�����-�� ���������... :(" << endl;
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
//			cout << "�����-�� ���������... :(" << endl;
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
//		cout << "������������ �������� (��): " << (stop_time - start_time) * 1000000000 / n << endl;
//		F1 << n << ";" << (stop_time - start_time) * 1000000 / n << endl;
//		delete gen;
//		seq->DeleteSeq();
//		n += step;
//	}
//	F1.close();
//	cout << "   *** ������������ ��������� ***" << endl;
//	return 1;
//}
