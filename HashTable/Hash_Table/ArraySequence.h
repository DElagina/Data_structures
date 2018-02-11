#pragma once

template <class TElement>
class ArraySequence 
{
public:
	ArraySequence<TElement>();
	ArraySequence<TElement>(TElement& element);
	~ArraySequence<TElement>();
	int Length();
	virtual TElement GetFirst();
	virtual TElement GetLast();
	virtual TElement Get(int index);
	virtual ArraySequence<TElement>* GetSubsequence(int start, int end);
	virtual void Append(TElement &item);
	virtual void Prepend(TElement &item);
	virtual void InsertAt(int index, TElement &item);
	virtual void Show();
	virtual void Swap(int& a, int& b);
	virtual void Change(int index, TElement &item);
	virtual int Type();
	void DeleteSeq();
private:
	TElement* data;
	int length = 0;
};

template <class TElement>
ArraySequence<TElement>::ArraySequence() {}

template <class TElement>
ArraySequence<TElement>::ArraySequence(TElement &element)
{
	this->length = 1;
	this->data = new TElement[1];
	this->data[0] = element;
}

template <class TElement>
ArraySequence<TElement>::~ArraySequence()
{
	this->length = 0;
	delete[] this;
}

template <class TElement>
int ArraySequence<TElement>::Length()
{
	return length;
}

template <class TElement>
TElement ArraySequence<TElement>::GetFirst()
{
	if (!this->length)
	{
		int errcode = 1;
		throw new Exception(errcode, "Массив пуст!");
	}
	return this->data[0];
}

template <class TElement>
TElement ArraySequence<TElement>::GetLast()
{
	if (!this->length)
	{
		int errcode = 1;
		throw new Exception(errcode, "Массив пуст!");
	}
	return this->data[this->length - 1];
}

template <class TElement>
TElement ArraySequence<TElement>::Get(int index)
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
ArraySequence<TElement>* ArraySequence<TElement>::GetSubsequence(int start, int end)
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
	ArraySequence<TElement>* seq = new ArraySequence();
	seq->length = end - start + 1;
	int memSize = sizeof(TElement) * (end - start + 1);
	seq->data = (TElement*)malloc(memSize + sizeof(TElement));
	memcpy(&seq->data[0], &this->data[start], memSize);
	return seq;
}

template <class TElement>
void ArraySequence<TElement>::Append(TElement &item)
{
	if (!this->length)
	{
		this->data = (TElement*)malloc(sizeof(TElement));
		this->data[this->length] = item;
		this->length++;
	}
	else
	{
		int memSize = sizeof(TElement) * this->length;
		this->data = (TElement*)realloc(this->data, memSize + sizeof(TElement));
		this->data[this->length] = item;
		this->length++;
	}
}

template <class TElement>
void ArraySequence<TElement>::Prepend(TElement &item)
{
	if (!this->length)
	{
		this->data = (TElement*)malloc(sizeof(TElement));
		this->data[this->length] = item;
		this->length++;
	}
	else
	{
		TElement* tmp = this->data;
		int memSize = sizeof(TElement) * this->length;
		this->data = (TElement*)realloc(this->data, memSize + sizeof(TElement));
		memcpy(&this->data[1], tmp, memSize);
		this->data[0] = item;
		this->length++;
	}
}

template <class TElement>
void ArraySequence<TElement>::InsertAt(int index, TElement &item)
{
	if (!this->length)
	{
		if (index == 0)
			Prepend(item);
		else
		{
			int errcode = 3;
			throw new Exception(errcode, "Недопустимый индекс элемента!");
		}
	}
	else
	{
		if (index < 0 || index > this->length)
		{
			int errcode = 3;
			throw new Exception(errcode, "Недопустимый индекс элемента!");
		}
		TElement *tmp2 = &this->data[index];
		this->data = (TElement*)realloc(this->data, sizeof(TElement) * this->length + sizeof(TElement));
		int memSize2 = sizeof(TElement) * (this->length - index);
		memcpy(&this->data[index + 1], tmp2, memSize2);
		this->data[index] = item;
		this->length++;
	}
}

template <class TElement>
void ArraySequence<TElement>::Show()
{
	cout << "Последовательность";
	if (!this->length)
		cout << " пуста!" << endl;
	else
	{
		cout << ": " << endl;
		for (int i = 0; i < this->length; i++)
			cout << this->data[i] << "   ";
		cout << endl;
	}
}

template <class TElement>
void ArraySequence<TElement>::Swap(int& ind1, int& ind2)
{
	if (!this->length)
	{
		int errcode = 1;
		throw new Exception(errcode, "Последовательность пуста!");
	}
	if (ind1 < 0 || ind1 > this->length)
	{
		int errcode = 3;
		throw new Exception(errcode, "Недопустимый индекс элемента!");
	}
	if (ind2 < 0 || ind2 > this->length)
	{
		int errcode = 3;
		throw new Exception(errcode, "Недопустимый индекс элемента!");
	}
	TElement a = this->data[ind1];
	this->data[ind1] = this->data[ind2];
	this->data[ind2] = a;
}

template <class TElement>
int ArraySequence<TElement>::Type()
{
	return 1;
}

template <class TElement>
void ArraySequence<TElement>::Change(int index, TElement &item)
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
	this->data[index] = item;
}

template <class TElement>
void ArraySequence<TElement>::DeleteSeq()
{
	free(this->data);
	free(this);
}