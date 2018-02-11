#pragma once
#include "ArraySequence.h"

template <class TElement>
class Generator
{
public:
	Generator();
	~Generator();
	ArraySequence<TElement>* RandGenerate(ArraySequence<TElement>* seq, int n, int max, int min);
	ArraySequence<TElement>* GenerateIncreaseSequence(ArraySequence<TElement>* seq, int n);
	ArraySequence<TElement>* GenerateDecreaseSequence(ArraySequence<TElement>* seq, int n);
};

template <class TElement>
Generator<TElement>::Generator() {}

template <class TElement>
Generator<TElement>::~Generator() {}

template <class TElement>
ArraySequence<TElement>* Generator<TElement>::GenerateIncreaseSequence(ArraySequence<TElement>* seq, int n)
{
	for (int i = n; i > 0; i--)
		seq->Prepend(i);
	return seq;
}

template <class TElement>
ArraySequence<TElement>* Generator<TElement>::GenerateDecreaseSequence(ArraySequence<TElement>* seq, int n)
{
	for (int i = 0; i < n; i++)
		seq->Prepend(i);
	return seq;
}

template <class TElement>
ArraySequence<TElement>* Generator<TElement>::RandGenerate(ArraySequence<TElement>* seq, int n, int max, int min)
{
	srand(time(0));
	if (max < min)
	{
		int t = max;
		max = min;
		min = t;
	}
	TElement a;
	for (int i = 0; i < n; i++)
	{
		a = rand() % (max - min + 1) + min;
		seq->Prepend(a);
	}
	return seq;
}
