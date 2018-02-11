#pragma once

template <class TKey, class TElement>
class ListData
{
public:
	ListData();
	~ListData();
	int Search(TKey key);
	ListData<TKey, TElement>* Add(TKey key, TElement element);
	ListData<TKey, TElement>* Delete(TKey key);
	void DeleteList();
	TElement Get(TKey key);
	TKey key;
	TElement element;
	ListData<TKey, TElement>* next;
};

template <class TKey, class TElement>
ListData<TKey, TElement>::ListData() {}

template <class TKey, class TElement>
ListData<TKey, TElement>::~ListData() {}

template <class TKey, class TElement>
int ListData<TKey, TElement>::Search(TKey key)
{
	ListData<TKey, TElement>* ptr = this;
	while (ptr)
	{
		if (ptr->key == key)
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

template <class TKey, class TElement>
ListData<TKey, TElement>* ListData<TKey, TElement>::Add(TKey key, TElement element)
{
	ListData<TKey, TElement>* item = new ListData<TKey, TElement>();
	item->key = key;
	item->element = element;
	item->next = this;
	return item;
}

template <class TKey, class TElement>
ListData<TKey, TElement>* ListData<TKey, TElement>::Delete(TKey key)
{
	ListData<TKey, TElement>* ptr = this;
	if (ptr)
	{
		while (ptr->next)
		{
			if (ptr->next->key == key)
			{
				ListData<TKey, TElement>* tmp = ptr->next;
				ptr->next = ptr->next->next;
				free(tmp);
				return this;
			}
			ptr = ptr->next;
		}
		if (ptr && (ptr->key == key))
		{
			free(ptr);
			return nullptr;
		}
	}
	int errcode = 11;
	throw new Exception(errcode, "Элемент с таким ключом не найден!");
}

template <class TKey, class TElement>
void ListData<TKey, TElement>::DeleteList()
{
	ListData<TKey, TElement>* ptr = this;
	while (ptr)
	{
		ListData<TKey, TElement>* tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
}

template <class TKey, class TElement>
TElement ListData<TKey, TElement>::Get(TKey key)
{
	ListData<TKey, TElement>* ptr = this;
	while (ptr)
	{
		if (ptr->key == key)
			return ptr->element;
		ptr = ptr->next;
	}
	int errcode = 11;
	throw new Exception(errcode, "Элемент с таким ключом не найден!");
}
