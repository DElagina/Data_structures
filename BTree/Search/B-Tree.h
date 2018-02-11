#pragma once

#include "SortedSequence.h"

const int T = 2;

template <class TElement, class TType>
struct Element
{
	TType key;
	TElement data;
};

template <class TElement, class TType>
class BTree: public SortedSequence<TElement, TType>
{
public:
	BTree<TElement, TType>();
	~BTree<TElement, TType>();
	TElement Search(TType keyElem);
	void Add(BTree<TElement, TType>** root, TElement element, TType keyElem);
	void Show();
	int IndexOf(TType key);
	BTree<TElement, TType>* GetSubsequence(int start, int end);
	TElement Get();
	void DeleteTree();
private:
	int key_amount; 
	Element<TElement, TType>* KeyData[2*T-1];
	BTree<TElement, TType> *parent;
	BTree<TElement, TType> *child[2*T]; 
	void RecurShow(BTree<TElement, TType>* tree);
	int IndexCounter(BTree<TElement, TType>* tree, TType key, int index, int* found);
	BTree<TElement, TType>* SubSequenceCounter(BTree<TElement, TType>* tree, BTree<TElement, TType>* newtree, int start, int end, int* index, int* flag);
	void B_Tree_Split(BTree<TElement, TType> *parent_node, int i);
	void B_Insert_Nonfull(BTree<TElement, TType>* nonfull_node, TElement element, TType keyElem);
	int isList(BTree<TElement, TType>* node);
	//void Insert(BTree<TElement, TType>** root, TElement element, TType keyElem);
	void DeleteBTree(BTree<TElement, TType>* tree);
};

template <class TElement, class TType>
BTree<TElement, TType>::BTree()
{
	parent = nullptr;
	for (int i = 0; i < 2 * T - 1; ++i)
	{
		KeyData[i] = nullptr;
		child[i] = nullptr;
	}
	child[2 * T - 1] = nullptr;
	key_amount = 0;
}

template <class TElement, class TType>
BTree<TElement, TType>::~BTree() {}

template <class TElement, class TType>
TElement BTree<TElement, TType>::Search(TType keyElem)
{
	if (!this->key_amount)
	{
		int errcode = 1;
		throw new Exception(errcode, "Дерево пусто!");
	};
	BTree<TElement, TType>* tree = this;
	int i;
	while (tree)
	{
		for (i = 0; i < tree->key_amount && keyElem > tree->KeyData[i]->key; ++i);
		if (i < tree->key_amount && keyElem == tree->KeyData[i]->key)
			return tree->KeyData[i]->data;
		tree = tree->child[i];
	}
	int errcode = 7;
	throw new Exception(errcode, "Элемент не найден!");
}

//template <class TElement, class TType>
//void BTree<TElement, TType>::Add(TElement element, TType keyElem)
//{
//	BTree<TElement, TType>*ptr = this;
//	this->Insert(&ptr, element, keyElem);
//}

template <class TElement, class TType>
void BTree<TElement, TType>::Add(BTree<TElement, TType>** root, TElement element, TType keyElem)
{
	BTree<TElement, TType>* tmpTree = *root;
	if (tmpTree->key_amount == 2 * T - 1)
	{
		BTree<TElement, TType>* new_head = new BTree<TElement, TType>();
		new_head->key_amount = 0;
		new_head->child[0] = tmpTree;
		(*root)->parent = new_head;
		*root = new_head;
		B_Tree_Split(new_head, 0);
		tmpTree = new_head;
	}
	B_Insert_Nonfull(tmpTree, element, keyElem);
}

template <class TElement, class TType>
void BTree<TElement, TType>::B_Tree_Split(BTree<TElement, TType> *parent_node, int i) 
{
	BTree<TElement, TType>* splitted_node = parent_node->child[i]; 
	int n = splitted_node->key_amount;
	for (int j = parent_node->key_amount; j > i; --j)
	{
		parent_node->KeyData[j] = parent_node->KeyData[j - 1];
		parent_node->child[j + 1] = parent_node->child[j];
	}
	BTree<TElement, TType>* new_node = new BTree<TElement, TType>();
	for (int j = 0; j < T - 1 ; j++)
	{
		new_node->KeyData[j] = splitted_node->KeyData[T + j];
		new_node->child[j] = splitted_node->child[T + j];
	}
	new_node->child[T - 1] = splitted_node->child[2 * T - 1];
	new_node->parent = parent_node;
	for (int j = 0; j < T; j++)
		if (new_node->child[j])
			new_node->child[j]->parent = new_node;
	parent_node->child[i + 1] = new_node;
	parent_node->KeyData[i] = splitted_node->KeyData[T - 1]; 
	++(parent_node->key_amount);
	splitted_node->key_amount = T - 1; 
	new_node->key_amount = T - 1; 
}

template <class TElement, class TType>
void BTree<TElement, TType>::B_Insert_Nonfull(BTree<TElement, TType>* nonfull_node, TElement element, TType keyElem)
{
	Element<TElement, TType> *new_item = new Element<TElement, TType>();  
	new_item->key = keyElem;
	new_item->data = element;

	int i;
	BTree<TElement, TType>* target_child;
	while (!(isList(nonfull_node)))
	{	
		if (keyElem < nonfull_node->KeyData[0]->key) 
			i = 0;
		else
		{
			if (nonfull_node->KeyData[nonfull_node->key_amount - 1]->key < keyElem)
				i = nonfull_node->key_amount;
			else
				for (i = 0; i < nonfull_node->key_amount && nonfull_node->KeyData[i]->key < keyElem && keyElem <= nonfull_node->KeyData[i + 1]->key; ++i);
		}
		BTree<TElement, TType>* target_child = nonfull_node->child[i];
		if (target_child->key_amount == 2 * T - 1)
		{
			B_Tree_Split(nonfull_node, i);
			if (keyElem > nonfull_node->KeyData[i]->key)
				target_child = nonfull_node->child[i + 1];
		}
		nonfull_node = target_child;
	}
	for (i = 0; i < nonfull_node->key_amount && nonfull_node->KeyData[i]->key < keyElem; ++i);
	for (int j = nonfull_node->key_amount; j > i; --j)
	{
		nonfull_node->KeyData[j] = nonfull_node->KeyData[j - 1];
		nonfull_node->child[j + 1] = nonfull_node->child[j];
	}
	++(nonfull_node->key_amount);
	nonfull_node->KeyData[i] = new_item;
}

template <class TElement, class TType>
int BTree<TElement, TType>::isList(BTree<TElement, TType>* node)
{
	for (int i = 0; i < node->key_amount + 1; ++i)
		if (node->child[i])
			return 0;
	return 1;
}

template <class TElement, class TType>
void BTree<TElement, TType>::Show()
{
	if (!this->key_amount)
		cout << "Дерево пусто!" << endl;
	else
	{
		cout << "Дерево: " << endl;
		RecurShow(this);
		cout << endl;
	}
}

template <class TElement, class TType>
void BTree<TElement, TType>::RecurShow(BTree<TElement, TType>* tree)
{
	if (tree)
	{
		for (int i = 0; i < tree->key_amount; ++i)
		{
			RecurShow(tree->child[i]);
			cout << tree->KeyData[i]->data <<"   ";
		}

		RecurShow(tree->child[tree->key_amount]);
	}
}

template <class TElement, class TType>
int BTree<TElement, TType>::IndexOf(TType key)
{
	int found = 0;
	int index = 0;
	index = this->IndexCounter(this, key, index, &found);
	if (found)
		return index;
	return -1;
}

template <class TElement, class TType>
int BTree<TElement, TType>::IndexCounter(BTree<TElement, TType>* tree, TType key, int index, int* found)
{
	if (tree)
	{
		for (int i = 0; i < tree->key_amount; ++i)
		{
			index = IndexCounter(tree->child[i], key, index, found);
			if (*found)
				return index;
			if (tree->KeyData[i]->key == key)
			{
				*found = 1;
				return index;
			}
			else
				index++;
		}
		index = IndexCounter(tree->child[tree->key_amount], key, index, found);
		if (*found)
			return index;
	}
	return index;
}

template <class TElement, class TType>
BTree<TElement, TType>* BTree<TElement, TType>::GetSubsequence(int start, int end)
{
	if (!this->key_amount)
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
	int index = 0;
	int flag = 0;
	BTree<TElement, TType>* newtree = new BTree<TElement, TType>();
	newtree = this->SubSequenceCounter(this, newtree, start, end, &index, &flag);
	--index;
	if (index < end)
	{
		newtree->DeleteTree();
		int errcode = 2;
		throw new Exception(errcode, "Индекс больше длины последовальности!");
	}
	return newtree;
}

template <class TElement, class TType>
BTree<TElement, TType>* BTree<TElement, TType>::SubSequenceCounter(BTree<TElement, TType>* tree, BTree<TElement, TType>* newtree, int start, int end, int* index, int* flag)
{
	if (tree)
	{
		for (int i = 0; i < tree->key_amount; ++i)
		{
			newtree = SubSequenceCounter(tree->child[i], newtree, start, end, index, flag);
			if (*index == start)
				*flag = 1;
			if (*flag)
				newtree->Add(&newtree, tree->KeyData[i]->data, tree->KeyData[i]->key);
			if (*index == end)
				*flag = 0;
			(*index)++;
		}
		newtree = SubSequenceCounter(tree->child[tree->key_amount], newtree, start, end, index, flag);
	}
	return newtree;
}

template <class TElement, class TType>
void BTree<TElement, TType>::DeleteTree()
{
	DeleteBTree(this);
}

template <class TElement, class TType>
void BTree<TElement, TType>::DeleteBTree(BTree<TElement, TType>* tree)
{
	if (tree)
	{
		for (int i = 0; i < tree->key_amount; ++i)
		{
			DeleteBTree(tree->child[i]); 
			free(tree->KeyData[i]);
		}
		DeleteBTree(tree->child[tree->key_amount]);  
		free(tree);
	}
}

template <class TElement, class TType>
TElement BTree<TElement, TType>::Get()
{
	return this->KeyData[0]->data;
}