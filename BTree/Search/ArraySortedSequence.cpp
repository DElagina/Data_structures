#include "ArraySortedSequence.h"
#include "Exception.h"
#include <iostream>

using namespace std;

template <class TElement>
ArraySortedSequence<TElement>::ArraySortedSequence() {}

template <class TElement>
ArraySortedSequence<TElement>::ArraySortedSequence(TElement &element)
{
	this->length = 1;
	this->data = new TElement[1];
	this->data[0] = element;
}

template <class TElement>
ArraySortedSequence<TElement>::~ArraySortedSequence() 
{
	this->length = 0;
	delete[] this;
}

template <class TElement>
TElement ArraySortedSequence<TElement>::GetFirst()
{
	if (!this->length)
	{
		int errcode = 1;
		throw new Exception(errcode, "Массив пуст!");
	}
	return this->data[0];
}

template <class TElement>
TElement ArraySortedSequence<TElement>::GetLast()
{
	if (!this->length)
	{
		int errcode = 1;
		throw new Exception(errcode, "Массив пуст!");
	}
	return this->data[this->length - 1];
}

template <class TElement>
TElement ArraySortedSequence<TElement>::Get(int index)
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
	};
	return this->data[index];
}

template <class TElement>
int ArraySortedSequence<TElement>::IndexOf(TElement item)
{
	if (!this->length)
		return -1;
	else
	{
		int left = 0, right = this->length - 1, medium = 0;
		while (left <= right)
		{
			medium = (left + right) / 2;
			if (this->data[medium] == item)
				return medium;
			else
			{
				if (this->data[medium] > item)
					right = medium - 1;
				else
					left = medium + 1;
			}
		}
		return -1;
	}
}

template <class TElement>
void ArraySortedSequence<TElement>::Add(TElement item)
{
	if (!this->length)
	{
		this->data = (TElement*)malloc(sizeof(TElement));
		this->data[this->length] = item;
		this->length++;
	}
	else
	{
		int left = 0, right = this->length - 1, medium = 0;
		while (left <= right)
		{
			medium = (left + right) / 2;
			if (this->data[medium] == item)
				break;
			else
			{
				if (this->data[medium] > item)
					right = medium - 1;
				else
					left = medium + 1;
			}
		}
		if (this->data[medium] <= item)
		{
			if (medium == this->length - 1)
			{
				this->data = (TElement*)realloc(this->data, sizeof(TElement) * this->length + sizeof(TElement));
				this->data[this->length] = item;
			}
			else
			{
				TElement *tmp2 = &this->data[medium + 1];
				this->data = (TElement*)realloc(this->data, sizeof(TElement) * this->length + sizeof(TElement));
				int memSize2 = sizeof(TElement) * (this->length - medium);
				memcpy(&this->data[medium + 1], tmp2, memSize2);
				this->data[medium] = item;
			}
			this->length++;
		}
		else
		{
			TElement *tmp2 = &this->data[medium];
			this->data = (TElement*)realloc(this->data, sizeof(TElement) * this->length + sizeof(TElement));
			int memSize2 = sizeof(TElement) * (this->length - medium);
			memcpy(&this->data[medium + 1], tmp2, memSize2);
			this->data[medium] = item;
			this->length++;
		}
	}
}

template <class TElement>
ArraySortedSequence<TElement>* ArraySortedSequence<TElement>::GetSubSortedSequence(int start, int end)
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
	};
	if (end < 0 || end >= this->length)
	{
		int errcode = 2;
		throw new Exception(errcode, "Не существует элемента с таким индексом!");
	};
	if (end < start)
	{
		int s = start;
		start = end;
		end = s;
	}
	ArraySortedSequence<TElement>* seq = new ArraySortedSequence();
	seq->length = end - start + 1;
	int memSize = sizeof(TElement) * (end - start + 1);
	seq->data = (TElement*)malloc(memSize + sizeof(TElement));
	memcpy(&seq->data[0], &this->data[start], memSize);
	return seq;
}

template <class TElement>
void ArraySortedSequence<TElement>::Show()
{
	cout << "Последовательность";
	if (!this->length)
		cout << " пуста!" <<endl;
	else
	{
		cout << ": " << endl;
		for (int i = 0; i < this->length; i++)
			cout << this->data[i] << "   ";
		cout << endl;
	}
}

template <class TElement>
int ArraySortedSequence<TElement>::Type()
{
	return 1;
}

template <class TElement>
void ArraySortedSequence<TElement>::DeleteSeq()
{
	free(this->data);
	free(this);
}