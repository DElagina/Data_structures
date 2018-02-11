#pragma once

template <class TElement, class TType>
class SortedSequence
{
public:
//	virtual TElement GetFirst() = 0;//
//	virtual TElement GetLast() = 0;//
	virtual TElement Get() = 0;
	virtual TElement Search(TType keyElem) = 0;
	virtual SortedSequence<TElement, TType>* GetSubsequence(int start, int end) = 0;
	virtual int IndexOf(TType key) = 0;
	//virtual void Add(SortedSequence<TElement, TType>**root, TElement element, TType key) = 0; //
	virtual void Show() = 0;
	virtual void DeleteTree() = 0;
};