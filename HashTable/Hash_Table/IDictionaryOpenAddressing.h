#pragma once
#include "IDictionary.h"

template <class TKey, class TElement>
struct Data
{
	int isBusy;
	TKey key;
	TElement element;
};

template <class TKey, class TElement>
class IDictionaryOpenAddressing: public IDictionary<TKey, TElement>
{
public:
	IDictionaryOpenAddressing(int _n);
	~IDictionaryOpenAddressing();
	TElement Get(TKey key);
	int ContainsKey(TKey key);
	void Add(TKey key, TElement element);
	void Remove(TKey key);
	void Show();
	void DeleteTable();
	//char* ShowString();
private:
	Data<TKey, TElement>* data;
};

template <class TKey, class TElement>
IDictionaryOpenAddressing<TKey,TElement> ::IDictionaryOpenAddressing(int _n)
{
	n = _n;
	data = new Data<TKey, TElement>[_n];
	for (int i = 0; i < n; ++i)
		data[i].isBusy = 0;
}

template <class TKey, class TElement>
IDictionaryOpenAddressing<TKey, TElement>::~IDictionaryOpenAddressing() {}

template <class TKey, class TElement>
TElement IDictionaryOpenAddressing<TKey, TElement>::Get(TKey key)
{
	int j;
	for (int i = 0; i < n; ++i)
	{
		j = Hash(GetHashCode(key), i);
		if (!data[j].isBusy)
		{
			int errcode = 11;
			throw new Exception(errcode, "Элемент с таким ключом не найден!");
		}
		if (data[j].key == key)
			return data[j].element;
	}
	int errcode = 11;
	throw new Exception(errcode, "Элемент с таким ключом не найден!");
}

template <class TKey, class TElement>
int IDictionaryOpenAddressing<TKey, TElement>::ContainsKey(TKey key)
{
	int j;
	for (int i = 0; i < n; ++i)
	{
		j = Hash(GetHashCode(key), i);
		if (!data[j].isBusy)
			return 0;
		if (data[j].key == key)
			return 1;
	}
	return 0;
}

template <class TKey, class TElement>
void IDictionaryOpenAddressing<TKey, TElement>::Add(TKey key, TElement element)
{
	int j, flag = 0;
	if (!ContainsKey(key))
	{
		for (int i = 0; i < n; ++i)
		{
			j = Hash(GetHashCode(key), i);
			if (!data[j].isBusy)
			{
				data[j].key = key;
				data[j].isBusy = 1;
				data[j].element = element;
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			int errcode = 10;
			throw new Exception(errcode, "Таблица переполнена!");
		}
	}
	else
	{
		int errcode = 12;
		throw new Exception(errcode, "Элемент с таким ключом уже существует!");
	}
}

template <class TKey, class TElement>
void IDictionaryOpenAddressing<TKey, TElement>::Remove(TKey key)
{
	int j, flag = 0;
	for (int i = 0; i < n; ++i)
	{
		j = Hash(GetHashCode(key), i);
		if (!data[j].isBusy)
		{
			int errcode = 11;
			throw new Exception(errcode, "Элемент с таким ключом не найден!");
		}
		if (data[j].key == key)
		{
			data[j].isBusy = 0;
			flag = 1;
			break;
		}
	}
	if (!flag)
	{
		int errcode = 11;
		throw new Exception(errcode, "Элемент с таким ключом не найден!");
	}
}

template <class TKey, class TElement>
void IDictionaryOpenAddressing<TKey, TElement>::Show()
{
	cout << "Таблица:" << endl;
	for (int i = 0; i < n; ++i) //   \r\n
	{
		if (data[i].isBusy)
			cout << data[i].key << "   " << data[i].element << endl;
		else
			cout << "пусто" << endl;
	}
}

//template <class TKey, class TElement>
//char* IDictionaryOpenAddressing<TKey, TElement>::ShowString()
//{
//	char* dest = new char[strlen("Таблица:\n")];
//	for (int i = 0; i < n; ++i) //   \r\n
//	{
//		if (data[i].isBusy)
//		{
//			//char* source = data[i].key;
//			//dest = strcat(dest, source);
//			dest = strcat(dest, "   ");
//			//source = data[i].element;
//			//dest = strcat(dest, source);
//			dest = strcat(dest, "\n");
//		}
//		else
//			dest = strcat(dest, "пусто");
//	}
//	return dest;
//}

template <class TKey, class TElement>
void IDictionaryOpenAddressing<TKey, TElement>::DeleteTable()
{
	delete[] data;
}