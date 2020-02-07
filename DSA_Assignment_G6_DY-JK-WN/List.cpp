#include "pch.h"
#include "List.h"

template <class ListTemplate>
List<ListTemplate>::List()
{
	size = 0;
}


template <class ListTemplate>
List<ListTemplate>::~List()
{
}

template <class ListTemplate>
int List<ListTemplate>::getSize()
{
	return size;
}

template <class ListTemplate>
void List<ListTemplate>::setSize(int i)
{
	size = i;
}

template <class ListTemplate>
bool List<ListTemplate>::add(ListTemplate item)
{
	bool success = size < MAX_SIZE;

	Node* newNode = new Node();
	newNode->item = item;
	newNode->next = NULL;

	if (success)
	{
		if (size == 0)
		{
			firstNode = newNode;
		}
		else
		{
			lastNode->next = newNode;
		}
		lastNode = newNode;
		workingNode = newNode;
		size++;
	}
	return success;
}

template <class ListTemplate>
bool List<ListTemplate>::add(int index, ListTemplate item)
{
	bool success = (index <= size) && (index <= MAX_SIZE) && (index >= 0);
	if (success)
	{
		Node* newNode = new Node();
		newNode->item = item;
		newNode->next = NULL;
		if (index == 1)
		{
			newNode->next = firstNode;
			firstNode = newNode;
		}
		else
		{
			for (int i = 0; i < index - 1; i++)
			{
				if (i == 0)
					workingNode = firstNode;
				else
					workingNode = workingNode->next;
			}
			newNode->next = workingNode->next;
			workingNode->next = newNode;
			workingNode = newNode;
		}

		if (newNode->next == NULL)
		{
			lastNode = newNode;
		}
		size++;
	}
	return success;
}

template <class ListTemplate>
ListTemplate* List<ListTemplate>::get(int index)
{
	bool success = (index >= 0) && (index <= size);

	if (success)
	{
		workingNode = firstNode;
		for (int i = 0; i < index; i++)
		{
			workingNode = workingNode->next;
		}
		return &workingNode->item;
	}

	return NULL; //error
}

template <class ListTemplate>
void List<ListTemplate>::remove(int index)
{
	bool success = (index >= 0) && (index <= size);

	if (success)
	{
		Node* deleteNode = new Node;
		for (int i = 0; i < index - 1; i++)
		{
			if (i <= 0)
				workingNode = firstNode;
			else
				workingNode = workingNode->next;

			deleteNode = workingNode->next;
			workingNode->next = workingNode->next->next;
		}
		if (index <= 1)
		{
			workingNode = firstNode;
			firstNode = firstNode->next;
		}
		delete deleteNode;
		size--;
	}
}

template <class ListTemplate>
void List<ListTemplate>::print()
{
	int index = 0;
	workingNode = firstNode;
	while (workingNode != NULL)
	{
		cout << index + 1 << ": " << &workingNode->item << endl;
		workingNode = workingNode->next;
		index++;
	}
}

template class List<Station>;
template class List<string>;
template class List<int>;
template class List<char>;