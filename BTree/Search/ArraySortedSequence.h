#pragma once
#include "SortedSequence.h"

template <class TElement>
class ArraySortedSequence : public SortedSequence<TElement>
{
public:
	ArraySortedSequence<TElement>();
	ArraySortedSequence<TElement>(TElement& element);
	~ArraySortedSequence<TElement>();
public:
	virtual TElement GetFirst();
	virtual TElement GetLast();
	virtual TElement Get(int index);
	virtual ArraySortedSequence<TElement>* GetSubSortedSequence(int start, int end);
	virtual int IndexOf(TElement element);
	virtual void Add(TElement element);
//	virtual void Append(TElement &item);
//	virtual void Prepend(TElement &item);
//	virtual void InsertAt(int index, TElement &item);
	virtual void Show();
//	virtual void Swap(int& a, int& b);
//	virtual void Change(int index, TElement &item);
	virtual int Type();
	void DeleteSeq();
private:
	TElement* data;
};