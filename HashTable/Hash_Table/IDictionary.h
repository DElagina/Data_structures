#pragma once

#include <cstring>
#include <iostream>
#include "Exception.h"

using namespace std;

template <class TKey, class TElement>
class IDictionary
{
public:
	virtual int GetCount();
	virtual TElement Get(TKey key) = 0;
	virtual int ContainsKey(TKey key) = 0;
	virtual void Add(TKey key, TElement element) = 0;
	virtual void Remove(TKey key) = 0;
	virtual void Show() = 0;
	virtual void DeleteTable() = 0;
	//virtual char* ShowString() = 0;
protected:
	int n; //размер
	virtual int Hash(int key, int i);
};

template <class TKey, class TElement>
int IDictionary<TKey, TElement>::GetCount()
{
	return n;
}

template <class TKey, class TElement>
int IDictionary<TKey, TElement>::Hash(int key, int i)
{
	return (key + i) % n;
}

int GetHashCode(string s)
{
	const int p = 31;
	long long Hash = 0, p_pow = 1;
	for (size_t i = 0; i < s.length(); ++i)
	{
		// желательно отнимать 'a' от кода буквы
		// единицу прибавляем, чтобы у строки вида 'aaaaa' хэш был ненулевой
		Hash += (s[i] - 'a' + 1) * p_pow;
		p_pow *= p;
	}
	return Hash;
}

int GetHashCode(int key)
{
	return key;
}