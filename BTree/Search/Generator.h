#pragma once
#include "Sequence.h"

template <class TElement>
class Generator
{
public:
	Generator();
	~Generator();
	Sequence<TElement>* RandGenerate(Sequence<TElement>* seq, int n, int max, int min);
	Sequence<TElement>* GenerateIncreaseSequence(Sequence<TElement>* seq, int n);
	Sequence<TElement>* GenerateDecreaseSequence(Sequence<TElement>* seq, int n);
};

template <class TElement>
Generator<TElement>::Generator()
{
}

template <class TElement>
Generator<TElement>::~Generator()
{
}

template <class TElement>
Sequence<TElement>* Generator<TElement>::GenerateIncreaseSequence(Sequence<TElement>* seq, int n)
{
	for (int i = n; i > 0; i--)
		seq->Prepend(i);
	return seq;
}

template <class TElement>
Sequence<TElement>* Generator<TElement>::GenerateDecreaseSequence(Sequence<TElement>* seq, int n)
{
	for (int i = 0; i < n; i++)
		seq->Prepend(i);
	return seq;
}

template <class TElement>
Sequence<TElement>* Generator<TElement>::RandGenerate(Sequence<TElement>* seq, int n, int max, int min)
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
