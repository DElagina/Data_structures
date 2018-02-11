#pragma once
#include "Exception.h"
#include "Stack.h"
#include "SortedSequence.h"

template <class TElement, class TType>
class BinaryTree: public SortedSequence<TElement, TType>
{
public:
	BinaryTree<TElement, TType>();
	~BinaryTree<TElement, TType>();
	TElement Get();
	void Add(TElement item, TType key);
	int IndexOf(TType key);
	BinaryTree<TElement, TType>* GetSubsequence(int start, int end);
	void DeleteTree();
	void Show();
	TElement Search(TType key);
	BinaryTree<TElement, TType>* Left();
	BinaryTree<TElement, TType>* Right();
private:
	BinaryTree<TElement, TType>* left, *right;
	TElement data;
	TType key;
	int busy = 0;
	void DeleteBinaryTree(BinaryTree<TElement, TType>* tree);
};


template <class TElement, class TType>
BinaryTree<TElement, TType>::BinaryTree() 
{
	busy = 0;
	left = nullptr;
	right = nullptr;
}

template <class TElement, class TType>
BinaryTree<TElement, TType>::~BinaryTree() {}

template <class TElement, class TType>
BinaryTree<TElement, TType>* BinaryTree<TElement, TType>::Left()
{
	return left;
}

template <class TElement, class TType>
BinaryTree<TElement, TType>* BinaryTree<TElement, TType>::Right()
{
	return right;
}

template <class TElement, class TType>
TElement BinaryTree<TElement, TType>::Get()
{
	if (this->busy)
		return this->data;
	int errcode = 1;
	throw new Exception(errcode, "Дерево пусто!");

}

template <class TElement, class TType>
void BinaryTree<TElement, TType>::Add(TElement item, TType newkey)
{
	if (this->busy != 1)
	{
		this->data = item;
		this->key = newkey;
		this->busy = 1;
		this->right = nullptr;
		this->left = nullptr;
	}
	else
	{
		BinaryTree<TElement, TType>* tmp = new BinaryTree<TElement, TType>();
		tmp->data = item;
		tmp->key = newkey;
		tmp->busy = 1;
		tmp->left = nullptr;
		tmp->right = nullptr;
		BinaryTree<TElement, TType>* ptr = this;
		while (ptr)
		{
			if (newkey > ptr->key)
			{
				if (ptr->right)
					ptr = ptr->right;
				else
				{
					ptr->right = tmp;
					break;
				}
			}
			else
			{
				if (ptr->left)
					ptr = ptr->left;
				else
				{
					ptr->left = tmp;
					break;
				}
			}
		}
	}
}

template <class TElement, class TType>
int BinaryTree<TElement, TType>::IndexOf(TType key)
{
	if (this->busy != 1)
	{
		int errcode = 1;
		throw new Exception(errcode, "Дерево пусто!");
	};
	int i = 0;
	BinaryTree<TElement, TType>* ptr = this;
	Stack<BinaryTree<TElement, TType>*> *stack = new Stack<BinaryTree<TElement, TType>*>();
	while (stack->Size() != 0 || ptr != nullptr)
	{
		if (ptr != nullptr)
		{
			stack->Push(ptr);
			ptr = ptr->left;
		}
		else
		{
			try
			{
				ptr = stack->Pop();
			}
			catch (Exception* e)
			{
				e->Show();
			}

			if (ptr->key == key)
				return i;
			i++;

			ptr = ptr->right;
		}
	}
	stack->FreeStack();
	return -1;
}

template <class TElement, class TType>
BinaryTree<TElement, TType>* BinaryTree<TElement, TType>::GetSubsequence(int start, int end)
{
	int flag = 0;
	if (this->busy != 1)
	{
		int errcode = 1;
		throw new Exception(errcode, "Дерево пусто!");
	};
	if (start < 0)
	{
		int errcode = 2;
		throw new Exception(errcode, "Отрицательный индекс!");
	}
	if (end < 0)
	{
		int errcode = 2;
		throw new Exception(errcode, "Отрицательный индекс!");
	}
	if (end < start)
	{
		int s = start;
		start = end;
		end = s;
	}
	int i = 0;
	BinaryTree<TElement, TType>* ptr = this;
	BinaryTree<TElement, TType>* newtree = new BinaryTree<TElement, TType>();
	Stack<BinaryTree<TElement, TType>*> *stack = new Stack<BinaryTree<TElement, TType>*>();
	while (stack->Size() != 0 || ptr != nullptr)
	{
		if (ptr != nullptr)
		{
			stack->Push(ptr);
			ptr = ptr->left;
		}
		else
		{
			try
			{
				ptr = stack->Pop();
			}
			catch (Exception* e)
			{
				e->Show();
			}
			if (i == start)
				flag = 1;
			if (flag)
				newtree->Add(ptr->data, ptr->key);
			if (i == end)
				flag = 0;
			i++;
			ptr = ptr->right;
		}
	}
	stack->FreeStack();
	i--;
	if (i < end)
	{
		newtree->DeleteTree();
		int errcode = 2;
		throw new Exception(errcode, "Индекс больше длины последовальности!");
	}
	return newtree;
}

template <class TElement, class TType>
void BinaryTree<TElement, TType>::DeleteTree()
{
	DeleteBinaryTree(this);
}

template <class TElement, class TType>
void BinaryTree<TElement, TType>::DeleteBinaryTree(BinaryTree<TElement, TType>* tree)
{
	if (tree && tree->busy)
	{
		if (tree->left && tree->left->busy)
			tree->left->DeleteBinaryTree(tree->left);
		if (tree->right && tree->right->busy)
			tree->right->DeleteBinaryTree(tree->right);
		free(tree);
	}
}

template <class TElement, class TType>
void BinaryTree<TElement, TType>::Show()
{
	if (this->busy != 1)
		cout << "Дерево пусто!" << endl;
	else
	{
		cout << "Дерево: " << endl;
		BinaryTree<TElement, TType>* ptr = this;
		Stack<BinaryTree<TElement, TType>*> *stack = new Stack<BinaryTree<TElement, TType>*>();
		while (stack->Size() != 0 || ptr)
		{
			if (ptr)
			{
				stack->Push(ptr);
				ptr = ptr->left;
			}
			else
			{
				try
				{
					ptr = stack->Pop();
				}
				catch (Exception* e)
				{
					e->Show();
				}
				cout << ptr->data << "   ";
				ptr = ptr->right;
			}
		}
		cout << endl;
		stack->FreeStack();
	}
}

template <class TElement, class TType>
TElement BinaryTree<TElement, TType>::Search(TType key)
{
	BinaryTree<TElement, TType>* tree = this;
	while (tree)
	{
		if (key == tree->key)
			return tree->data;
		if (key < tree->key)
			tree = tree->left;
		else
			tree = tree->right;
	}
	int errcode = 7;
	throw new Exception(errcode, "Элемент не найден!");
}
