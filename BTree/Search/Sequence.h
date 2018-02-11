#pragma once

template <class TElement>
class Sequence
{
public:
	virtual int Length();
	virtual TElement GetFirst() = 0;
	virtual TElement GetLast() = 0;
	virtual TElement Get(int index) = 0;
	virtual Sequence<TElement>* GetSubsequence(int start, int end) = 0;
	virtual void Append(TElement &item) = 0;
	virtual void Prepend(TElement &item) = 0;
	virtual void InsertAt(int index, TElement &item) = 0;
	virtual void Show() = 0;
	virtual void Swap(int& a, int& b) = 0;
	virtual void Change(int index, TElement &item) = 0;
	virtual int Type() = 0;
	virtual void DeleteSeq() = 0;
protected:
	int length = 0;
};

template <class TElement>
int Sequence<TElement>::Length()
{
	return this->length;
}