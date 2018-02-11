#pragma once
#include "SortedSequence.h"

template <class TElement>
class ListSortedSequence : public SortedSequence<TElement>
{
public:
	ListSortedSequence<TElement>();
	ListSortedSequence<TElement>(TElement& element);
	~ListSortedSequence<TElement>();
public:
	virtual TElement GetFirst();
	virtual TElement GetLast();
	virtual TElement Get(int index);
	virtual int IndexOf(TElement element);
	virtual void Add(TElement element);
//	virtual void Append(TElement &item);
//	virtual void Prepend(TElement &item);
//	virtual void InsertAt(int index, TElement &item);
	virtual ListSortedSequence<TElement>* GetSubSortedSequence(int start, int end);
	virtual void Show();
//	virtual void Swap(int& a, int& b);
//	virtual void Change(int index, TElement &item);
	virtual int Type();
	void DeleteSeq();
private:
	TElement data;
	ListSortedSequence<TElement>* next = nullptr;
};