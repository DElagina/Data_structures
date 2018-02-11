#include "Sort.h"
#include "Stack.h"

template <class TElement>
Sort<TElement>::Sort() {}

template <class TElement>
Sort<TElement>::~Sort() {}

template <class TElement>
void Sort<TElement>::QuickSort(Sequence<TElement>* seq, int start, int end, int up)
{
	if (start < 0 || start >= seq->Length())
	{
		int errcode = 2;
		throw new Exception(errcode, "Не существует элемента с таким индексом!");
	}
	if (end < 0 || end >= seq->Length())
	{
		int errcode = 2;
		throw new Exception(errcode, "Не существует элемента с таким индексом!");
	}
	if (up != 0 && up != 1)
	{
		int errcode = 4;
		throw new Exception(errcode, "Неверное значение направления сортировки!");
	}
	if (end < start)
	{
		int s = start;
		start = end;
		end = s;
	}
	int l = start;
	int r = end;
	TElement m = seq->Get(l + (r - l) / 2);
	while (l < r)
	{
		if (up)
		{
			while (seq->Get(l) < m) l++;
			while (seq->Get(r) > m) r--;
		}
		else
		{
			while (seq->Get(l) > m) l++;
			while (seq->Get(r) < m) r--;
		}
		if (l <= r)
		{
			try
			{
				seq->Swap(l, r);
			}
			catch (Exception *e)
			{
				e->Show();
			}
			l++;
			r--;
		}
	}
	if (l < end)
		QuickSort(seq, l, end, up);
	if (start < r)
		QuickSort(seq, start, r, up);
}

template <class TElement>
void Sort<TElement>::EasyChoice(Sequence<TElement>* seq, int up)
{
	if (up != 0 && up != 1)
	{
		int errcode = 4;
		throw new Exception(errcode, "Неверное значение направления сортировки!");
	}
	for (int i = 0; i < seq->Length(); i++)
	{
		int extr = i;
		for (int j = i + 1; j < seq->Length(); j++)
		{
			if (up)
			{
				if (seq->Get(j) < seq->Get(extr))
					extr = j;
			}
			else
			{
				if (seq->Get(j) > seq->Get(extr))
					extr = j;
			}
		}
		if (extr != i)
		{
			try
			{
				seq->Swap(i, extr);
			}
			catch (Exception *e)
			{
				e->Show();
			}
		}
	}
}

template <class TElement>
void Sort<TElement>::TreeVisit(BinaryTree<TElement>* root, Sequence<TElement>* seq, int up)
{
	int i = 0;
	TElement a;
	Stack<TElement> *ps = new Stack<TElement>();
	while (ps->Size() != 0 || root != NULL) 
	{
		if (root != NULL) 
		{
			ps->Push(root);
			if (up)
				root = root->Right();
			else
				root = root->Left();
		}
		else
		{
			try
			{
				root = ps->Pop();
			}
			catch (Exception* e)
			{
				e->Show();
			}
			a = root->Get();
			seq->Change(i, a);
			i++;
			if (up)
				root = root->Left();
			else
				root = root->Right();
		}
	}
	ps->FreeStack();
}

template <class TElement>
void Sort<TElement>::TreeChoice(Sequence<TElement>* seq, int up)
{
	if (up != 0 && up != 1)
	{
		int errcode = 4;
		throw new Exception(errcode, "Неверное значение направления сортировки!");
	}
	Tree<TElement>* tree = new Tree<TElement>();
	TElement a;
	for (int i = 0; i < seq->Length(); i++)
	{
		a = seq->Get(i);
		tree->Add(a);
	}
	int i = 0;
	this->TreeVisit(tree, seq, up);
}