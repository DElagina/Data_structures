#include "ListSequence.h"
#include "Exception.h"
#include <iostream>

using namespace std;

template <class TElement>
ListSequence<TElement>::ListSequence() {}

template <class TElement>
ListSequence<TElement>::ListSequence(TElement &element)
{
	this->next = new ListSequence<TElement>();
	this->next->data = element;
	this->next->next = nullptr;
	this->length++;
}

template <class TElement>
ListSequence<TElement>::~ListSequence() 
{
	ListSequence<TElement>* tmp = nullptr;
	while (this)
	{
		tmp = this;
		this = this->next;
		free(tmp);
	}
}

template <class TElement>
TElement ListSequence<TElement>::GetFirst()
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
TElement ListSequence<TElement>::GetLast()
{
	ListSequence<TElement> * cur = this->next;
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
TElement ListSequence<TElement>::Get(int index)
{
	ListSequence<TElement> * cur = this->next;
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

template <class TElement>
void ListSequence<TElement>::Append(TElement &item)
{
	if (!this->next)
	{
		this->next = new ListSequence<TElement>();
		this->next->data = item;
		this->next->next = nullptr;
		this->length++;
	}
	else
	{
		ListSequence<TElement>* tmp = new ListSequence<TElement>();
		tmp->data = item;
		tmp->next = nullptr;
		ListSequence<TElement> * cur = this->next;
		for (; cur->next; cur = cur->next) {}
		cur->next = tmp;
		this->length++;
	}
}

template <class TElement>
void ListSequence<TElement>::Prepend(TElement &item)
{
	if (!this->next)
	{
		this->next = new ListSequence<TElement>();
		this->next->data = item;
		this->next->next = nullptr;
		this->length++;
	}
	else
	{
		ListSequence<TElement>* tmp = new ListSequence<TElement>();
		tmp->data = item;
		tmp->next = this->next;
		this->next = tmp;
		this->length++;
	}
}

template <class TElement>
void ListSequence<TElement>::InsertAt(int index, TElement &item)
{
	if (!this->length)
	{
		if (index == 0)
		{
			this->next = new ListSequence<TElement>(item);
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
		ListSequence<TElement>* tmp = new ListSequence<TElement>();
		tmp->data = item;
		tmp->next = nullptr;
		ListSequence<TElement>* cur = this;
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
}

template <class TElement>
ListSequence<TElement>* ListSequence<TElement>::GetSubsequence(int start, int end)
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
	ListSequence<TElement> * cur = this->next;
	for (int i = 0; i < start; i++)
		cur = cur->next;
	ListSequence<TElement> * subseq = new ListSequence<TElement>();
	for (int i = 0; i <= end - start; i++)
	{
		subseq->Append(cur->data);
		cur = cur->next;
	}
	return subseq;
}

template <class TElement>
void ListSequence<TElement>::Show()
{
	ListSequence<TElement>*cur = this->next;
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

template <class TElement>
void ListSequence<TElement>::Swap(int& a, int& b)
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
	ListSequence* cur = this->next; //меняем местами
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
int ListSequence<TElement>::Type()
{
	return 0;
}

template <class TElement>
void ListSequence<TElement>::Change(int index, TElement &item)
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
	ListSequence<TElement>* cur = this->next;
	for (int i = 0; i < index; i++)
		cur = cur->next;
	cur->data = item;
}

template <class TElement>
void ListSequence<TElement>::DeleteSeq()
{
	ListSequence<TElement>* tmp = nullptr;
	ListSequence<TElement>* cur = nullptr;
	cur = this->next;
	for (int i = 0; i < this->length; i++)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	free(this);
}