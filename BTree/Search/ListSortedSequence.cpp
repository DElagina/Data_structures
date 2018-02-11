#include "ListSortedSequence.h"
#include "Exception.h"
#include <iostream>

using namespace std;

template <class TElement>
ListSortedSequence<TElement>::ListSortedSequence() {}

template <class TElement>
ListSortedSequence<TElement>::ListSortedSequence(TElement &element)
{
	this->next = new ListSortedSequence<TElement>();
	this->next->data = element;
	this->next->next = nullptr;
	this->length++;
}

template <class TElement>
ListSortedSequence<TElement>::~ListSortedSequence() 
{
	ListSortedSequence<TElement>* tmp = nullptr;
	while (this)
	{
		tmp = this;
		this = this->next;
		free(tmp);
	}
}

template <class TElement>
TElement ListSortedSequence<TElement>::GetFirst()
{
	if (this->next)
		return this->next->data;
	else
	{
		int errcode = 1;
		throw new Exception(errcode, "Список пуст!");
	}
}

template <class TElement>
TElement ListSortedSequence<TElement>::GetLast()
{
	ListSortedSequence<TElement> * cur = this->next;
	if (cur)
	{
		for (; cur->next; cur = cur->next) {}
		return cur->data;
	}
	else
	{
		int errcode = 1;
		throw new Exception(errcode, "Список пуст!");
	}
}

template <class TElement>
TElement ListSortedSequence<TElement>::Get(int index)
{
	ListSortedSequence<TElement> * cur = this->next;
	if (cur)
	{
		int count = 0;
		while (cur)
		{
			if (index == count)
				break;
			count++;
			cur = cur->next;
		}
		if (cur)
			return cur->data;
		else
		{
			int errcode = 2;
			throw new Exception(errcode, "В списке нет элемента с таким номером!");
		}
	}
	else
	{
		int errcode = 1;
		throw new Exception(errcode, "Список пуст!");
	}
}
/*
template <class TElement>
void ListSortedSequence<TElement>::Append(TElement &item)
{
	if (!this->next)
	{
		this->next = new ListSortedSequence<TElement>();
		this->next->data = item;
		this->next->next = nullptr;
		this->length++;
	}
	else
	{
		ListSortedSequence<TElement>* tmp = new ListSortedSequence<TElement>();
		tmp->data = item;
		tmp->next = nullptr;
		ListSortedSequence<TElement> * cur = this->next;
		for (; cur->next; cur = cur->next) {}
		cur->next = tmp;
		this->length++;
	}
}

template <class TElement>
void ListSortedSequence<TElement>::Prepend(TElement &item)
{
	if (!this->next)
	{
		this->next = new ListSortedSequence<TElement>();
		this->next->data = item;
		this->next->next = nullptr;
		this->length++;
	}
	else
	{
		ListSortedSequence<TElement>* tmp = new ListSortedSequence<TElement>();
		tmp->data = item;
		tmp->next = this->next;
		this->next = tmp;
		this->length++;
	}
}

template <class TElement>
void ListSortedSequence<TElement>::InsertAt(int index, TElement &item)
{
	if (!this->length)
	{
		if (index == 0)
		{
			this->next = new ListSortedSequence<TElement>(item);
			this->next->data = item;
			this->next->next = nullptr;
			this->length++;
		}
		else
		{
			int errcode = 3;
			throw new Exception(errcode, "Невозможно вставить в пустой массив элемент с ненулевым номером!");
		}
	}
	else
	{
		if (index < 0 || index > this->length)
		{
			int errcode = 3;
			throw new Exception(errcode, "Неверный индекс элемента!");
		}
		ListSortedSequence<TElement>* tmp = new ListSortedSequence<TElement>();
		tmp->data = item;
		tmp->next = nullptr;
		ListSortedSequence<TElement>* cur = this;
		if (!index)
			cur->Prepend(item);
		else
		{
			for (int i = 0; i < index; i++)
			{
				cur = cur->next;
			}
			tmp->next = cur->next;
			cur->next = tmp;
			this->length++;
		}
	}
}*/

template <class TElement>
int ListSortedSequence<TElement>::IndexOf(TElement element)
{
	int count = 0;
	ListSortedSequence<TElement>* cur = this->next;
	while (cur)
	{
		if (element == cur->data)
			return count;
		else
			if (element > cur->data)
			{
				count++;
				cur = cur->next;
			}
			else
				return -1;
	}
	return -1;
}

template <class TElement>
void ListSortedSequence<TElement>::Add(TElement item)
{
	ListSortedSequence<TElement>* tmp = new ListSortedSequence<TElement>();
	tmp->data = item;
	tmp->next = nullptr;
	ListSortedSequence<TElement>* cur = this->next;
	if (cur)
	{
		while (cur->next)
		{
			if (item > cur->next->data)
				cur = cur->next;
			else
				break;
		}
		if (item > cur->data)
		{
			if (!cur->next)
				cur->next = tmp;
			else
			{
				ListSortedSequence<TElement>* ptr = cur->next;
				cur->next = tmp;
				tmp->next = ptr;
			}
		}
		else
		{
			tmp->next = cur;
			this->next = tmp;
		}
	}
	else
		this->next = tmp;
	this->length++;
}

template <class TElement>
ListSortedSequence<TElement>* ListSortedSequence<TElement>::GetSubSortedSequence(int start, int end)
{
	if (!this->length)
	{
		int errcode = 1;
		throw new Exception(errcode, "Массив пуст!");
	}
	if (start < 0 || start >= this->length)
	{
		int errcode = 2;
		throw new Exception(errcode, "Не существует элемента с таким индексом!");
	}
	if (end < 0 || end >= this->length)
	{
		int errcode = 2;
		throw new Exception(errcode, "Не существует элемента с таким индексом!");
	}
	if (end < start)
	{
		int s = start;
		start = end;
		end = s;
	}
	ListSortedSequence<TElement> * cur = this->next;
	for (int i = 0; i < start; i++)
		cur = cur->next;
	ListSortedSequence<TElement> * subseq = new ListSortedSequence<TElement>();
	for (int i = 0; i <= end - start; i++)
	{
		subseq->Add(cur->data);
		cur = cur->next;
	}
	return subseq;
}

template <class TElement>
void ListSortedSequence<TElement>::Show()
{
	ListSortedSequence<TElement>*cur = this->next;
	cout << "Последовательность";
	if (cur)
	{
		cout << ":" << endl;
		while (cur)
		{
			cout << cur->data << "   ";
			cur = cur->next;
		}
		cout << endl;
	}
	else
		cout << " пуста!" << endl;
}
/*
template <class TElement>
void ListSortedSequence<TElement>::Swap(int& a, int& b)
{
	if (!this->length)
	{
		int errcode = 1;
		throw new Exception(errcode, "Последовательность пуста!");
	}
	if (a < 0 || a > this->length)
	{
		int errcode = 3;
		throw new Exception(errcode, "Недопустимый индекс элемента!");
	}
	if (b < 0 || b > this->length)
	{
		int errcode = 3;
		throw new Exception(errcode, "Недопустимый индекс элемента!");
	}
	ListSortedSequence* cur = this->next; //меняем местами
	TElement tmpR = Get(b);
	for (int count = 0; count < a; count++)
		cur = cur->next;
	TElement tmpL = cur->data;
	cur->data = tmpR;
	for (int count = a; count < b; count++)
		cur = cur->next;
	cur->data = tmpL;
}

template <class TElement>
void ListSortedSequence<TElement>::Change(int index, TElement &item)
{
	if (!this->length)
	{
		int errcode = 1;
		throw new Exception(errcode, "Массив пуст!");
	}
	if (index < 0 || index >= this->length)
	{
		int errcode = 2;
		throw new Exception(errcode, "Не существует элемента с таким индексом!");
	}
	ListSortedSequence<TElement>* cur = this->next;
	for (int i = 0; i < index; i++)
		cur = cur->next;
	cur->data = item;
}*/

template <class TElement>
int ListSortedSequence<TElement>::Type()
{
	return 0;
}

template <class TElement>
void ListSortedSequence<TElement>::DeleteSeq()
{
	ListSortedSequence<TElement>* tmp = nullptr;
	ListSortedSequence<TElement>* cur = nullptr;
	cur = this->next;
	for (int i = 0; i < this->length; i++)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	free(this);
}