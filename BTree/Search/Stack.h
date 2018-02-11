#pragma once

template <class TElement>
class Stack
{
public:
	Stack();
	~Stack();
	void FreeStack();
	void Push(TElement item);
	TElement Pop();
	TElement Peek();
	int Size();
private:
	int size = 0;
	int limit = 100;
	TElement* data;
};


template <class TElement>
Stack<TElement>::Stack()
{
	this->data = (TElement*)malloc(this->limit * sizeof(TElement));
}

template <class TElement>
Stack<TElement>::~Stack() {}

template <class TElement>
void Stack<TElement>::FreeStack()
{
	free(this->data);
	free(this);
}

template <class TElement>
int Stack<TElement>::Size()
{
	return this->size;
}

template <class TElement>
void Stack<TElement>::Push(TElement item)
{
	if (this->size >= this->limit)
	{
		this->limit *= 2;
		this->data = (TElement*)realloc(this->data, this->limit * sizeof(TElement));
	}
	this->data[this->size++] = item;
}

template <class TElement>
TElement Stack<TElement>::Pop()
{
	if (this->size == 0)
	{
		int errcode = 6;
		throw new Exception(errcode, "Невозможно считать элемент из пустого стека!");
	}
	this->size--;
	return this->data[this->size];
}

template <class TElement>
TElement Stack<TElement>::Peek()
{
	return this->data[this->size - 1];
}