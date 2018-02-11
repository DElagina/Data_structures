#pragma once

#include "IDictionary.h"
#include "ListData.h"

template <class TKey, class TElement>
class IDictionarySeparateChanging: public IDictionary<TKey, TElement>
{
public:
	IDictionarySeparateChanging(int _n);
	~IDictionarySeparateChanging();
	TElement Get(TKey key);
	int ContainsKey(TKey key);
	void Add(TKey key, TElement element);
	void Remove(TKey key);
	void Show();
	void DeleteTable();
	//char* ShowString();
private:
	ListData<TKey, TElement>** data;
};

template <class TKey, class TElement>
IDictionarySeparateChanging<TKey, TElement>::IDictionarySeparateChanging(int _n)
{
	n = _n;
	data = new ListData<TKey, TElement>*[_n];
	for (int i = 0; i < n; ++i)
		data[i] = nullptr;
}

template <class TKey, class TElement>
IDictionarySeparateChanging<TKey, TElement>::~IDictionarySeparateChanging() {}

template <class TKey, class TElement>
TElement IDictionarySeparateChanging<TKey, TElement>::Get(TKey key)
{
	int j = Hash(GetHashCode(key), 0);
	try
	{
		return data[j]->Get(key);
	}
	catch (Exception* e)
	{
		int errcode = 11;
		throw new Exception(errcode, "Элемент с таким ключом не найден!");
	}
}

template <class TKey, class TElement>
int IDictionarySeparateChanging<TKey, TElement>::ContainsKey(TKey key)
{
	int j = Hash(GetHashCode(key), 0);
	return data[j]->Search(key);
}

template <class TKey, class TElement>
void IDictionarySeparateChanging<TKey, TElement>::Add(TKey key, TElement element)
{
	int j = Hash(GetHashCode(key), 0);
	if (!ContainsKey(key))
	{
		data[j] = data[j]->Add(key, element);
	}
	else
	{
		int errcode = 12;
		throw new Exception(errcode, "Элемент с таким ключом уже существует!");
	}
}

template <class TKey, class TElement>
void IDictionarySeparateChanging<TKey, TElement>::Remove(TKey key)
{
	int j = Hash(GetHashCode(key), 0);
	try
	{
		data[j] = data[j]->Delete(key);
	}
	catch (Exception* e)
	{
		int errcode = 11;
		throw new Exception(errcode, "Элемент с таким ключом не найден!");
	}
}

template <class TKey, class TElement>
void IDictionarySeparateChanging<TKey, TElement>::Show()
{
	cout << "Таблица:" << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << i << ":";
		if (!data[i])
			cout << " пустo";
		else
		{
			ListData<TKey, TElement>* ptr = data[i];
			while (ptr)
			{
				cout << " --> " << "(" << ptr->key << ";" << ptr->element << ")";
				ptr = ptr->next;
			}
		}
		cout << endl;
	}
}

template <class TKey, class TElement>
void IDictionarySeparateChanging<TKey, TElement>::DeleteTable()
{
	for (int i = 0; i < n; ++i)
		data[i]->DeleteList();
	delete[] data;
}

//template <class TKey, class TElement>
//char* IDictionarySeparateChanging<TKey, TElement>::ShowString()
//{
//	char* dest = new char[strlen("Таблица:\n")];
//	//for (int i = 0; i < n; ++i) //   \r\n
//	//{
//	//	if (this->data[i].isBusy)
//	//	{
//	//		char* source = data[i].key;
//	//		dest = strcat(dest, source);
//	//		dest = strcat(dest, "   ");
//	//		source = data[i].element;
//	//		dest = strcat(dest, source);
//	//		dest = strcat(dest, "\n");
//	//	}
//	//	else
//	//		dest = strcat(dest, "пусто");
//	//}
//	return dest;
//}