#pragma once

template <class TElement, class TType>
class Tree
{
public:
	virtual void DeleteTree() = 0;
	virtual void Show() = 0;
	virtual Tree<TElement, TType>* GetSubsequence(int start, int end) = 0;
	virtual int IndexOf(TType key) = 0;
	virtual void Add(TElement element, TType keyElem) = 0;
	virtual TElement Search(TType keyElem) = 0;
};
