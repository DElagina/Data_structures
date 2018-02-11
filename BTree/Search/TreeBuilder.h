#pragma once
#include "Sequence.h"
#include "BinaryTree.h"
#include "B-Tree.h"

template <class TElement, class TType>
class TreeBuilder
{
public:
	TreeBuilder();
	~TreeBuilder();
	BinaryTree<TElement, TType>* BinaryTreeBuilder(Sequence<TElement>* seq);
	BTree<TElement, TType>* BTreeBuilder(Sequence<TElement>* seq);
};

template <class TElement, class TType>
TreeBuilder<TElement, TType>::TreeBuilder() {}

template <class TElement, class TType>
TreeBuilder<TElement, TType>::~TreeBuilder() {}

template <class TElement, class TType>
BinaryTree<TElement, TType>* TreeBuilder<TElement, TType>::BinaryTreeBuilder(Sequence<TElement>* seq)
{
	BinaryTree<TElement, TType>* tree = new BinaryTree<TElement, TType>();
	TElement a;
	for (int i = 0; i < seq->Length(); i++)
	{
		a = seq->Get(i);
		tree->Add(a, a);
	}
	return tree;
}

template <class TElement, class TType>
BTree<TElement, TType>* TreeBuilder<TElement, TType>::BTreeBuilder(Sequence<TElement>* seq)
{
	BTree<TElement, TType>* tree = new BTree<TElement, TType>();
	TElement a;
	for (int i = 0; i < seq->Length(); i++)
	{
		a = seq->Get(i);
		tree->Add(&tree, a, a);
	}
	return tree;
}