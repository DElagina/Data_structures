
template <class TElement>
BinaryTree<TElement>::BinaryTree() {}

template <class TElement>
BinaryTree<TElement>::~BinaryTree() {}

template <class TElement>
BinaryTree<TElement>* BinaryTree<TElement>::Right()
{
	return this->right;
}

template <class TElement>
BinaryTree<TElement>* BinaryTree<TElement>::Left()
{
	return this->left;
}

template <class TElement>
TElement BinaryTree<TElement>::Get()
{
	if (this->busy)
		return this->data;
	else
	{
		int errcode = 1;
		throw new Exception(errcode, "Дерево пусто!");
	}
}

template <class TElement>
int BinaryTree<TElement>::Busy()
{
	return this->busy;
}

template <class TElement>
void BinaryTree<TElement>::Add(TElement & item)
{
	if (!this->busy)
	{
		this->data = item;
		busy = 1;
	}
	else
	{
		BinaryTree<TElement>* tmp = new BinaryTree<TElement>();
		tmp->data = item;
		tmp->busy = 1;
		tmp->left = nullptr;
		tmp->right = nullptr;
		BinaryTree<TElement>* ptr = this;
		while (ptr)
		{
			if (ptr->data < item)
			{
				if (ptr->left)
					ptr = ptr->left;
				else
				{
					ptr->left = tmp;
					break;
				}
			}
			else
			{
				if (ptr->right)
					ptr = ptr->right;
				else
				{
					ptr->right = tmp;
					break;
				}
			}
		}
	}
}

template <class TElement>
int BinaryTree<TElement>::IndexOf(TElement element)
{
	int i = 0;
	BinaryTree<TElement>* ptr = this;
	Stack<BinaryTree<TElement>*> *stack = new Stack<BinaryTree<TElement>*>();
	while (stack->Size() != 0 || ptr != NULL)
	{
		if (ptr != NULL)
		{
			stack->Push(ptr);
			ptr = ptr->Right();
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

			if (ptr->data == element)
				return i;
			i++;

			ptr = ptr->Left();
		}
	}
	stack->FreeStack();
	return -1;
}

template <class TElement>
BinaryTree<TElement>* BinaryTree<TElement>::GetSubsequence(int start, int end)
{
	int flag = 0;
	if (!this->busy)
	{
		int errcode = 1;
		throw new Exception(errcode, "Дерево пусто!");
	};
	/*if (start < 0 || start >= this->length)
	{
		int errcode = 2;
		throw new Exception(errcode, "Не существует элемента с таким индексом!");
	}
	if (end < 0 || end >= this->length)
	{
		int errcode = 2;
		throw new Exception(errcode, "Не существует элемента с таким индексом!");
	}*/
	if (start < 0)
	{
		int errcode = 2;
		throw new Exception(errcode, "Ошибка: отрицательный индекс!");
	}
	if (end < 0)
	{
		int errcode = 2;
		throw new Exception(errcode, "Ошибка: отрицательный индекс!");
	}
	if (end < start)
	{
		int s = start;
		start = end;
		end = s;
	}
	int i = 0;
	BinaryTree<TElement>* ptr = this;
	BinaryTree<TElement>* newtree = new BinaryTree<TElement>();
	TElement a;
	Stack<BinaryTree<TElement>*> *stack = new Stack<BinaryTree<TElement>*>();
	while (stack->Size() != 0 || ptr != NULL)
	{
		if (ptr != NULL)
		{
			stack->Push(ptr);
			ptr = ptr->Right();
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
				newtree->Add(ptr->data);
			if (i == start)
				flag = 0;
			i++;
			ptr = ptr->Left();
		}
	}
	stack->FreeStack();
	i--;
	if (i < end)
	{
		newtree->DeleteTree(newtree);
		int errcode = 2;
		throw new Exception(errcode, "Ошибка: индекс больше длины последовальности!");
	}
	return newtree;
}

template <class TElement>
void BinaryTree<TElement>::DeleteTree(BinaryTree<TElement>* tree)
{
	if (tree && tree->busy)
	{
		if (tree->left && tree->left->busy)
			tree->left->DeleteTree(tree->left);
		if (tree->right && tree->right->busy)
			tree->right->DeleteTree(tree->right);
		free(tree);
	}
}

template <class TElement>
void BinaryTree<TElement>::Show()
{
	int i = 0;
	BinaryTree<TElement>* ptr = this;
	TElement a;
	Stack<BinaryTree<TElement>*> *stack = new Stack<BinaryTree<TElement>*>();
	while (stack->Size() != 0 || ptr != NULL)
	{
		if (ptr != NULL)
		{
			stack->Push(ptr);
			ptr = ptr->Right();
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

			cout << ptr->data << "  ";

			ptr = ptr->Left();
		}
	}
	cout << endl;
	stack->FreeStack();
}
