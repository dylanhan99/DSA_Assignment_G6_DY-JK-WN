#include "pch.h"
#include "List.h"


List::List()
{
	size = 0;
}


List::~List()
{
}

bool List::add(ItemType item)
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

bool List::add(int index, ItemType item)
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

ItemType List::get(int index)
{
	bool success = (index >= 0) && (index <= size);

	if (success)
	{
		workingNode = firstNode;
		for (int i = 0; i < index; i++)
		{
			workingNode = workingNode->next;
		}
		return workingNode->item;
	}

	return NULL; //error
}

void List::remove(int index)
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

int List::getSize()
{
	return size;
}

void List::print()
{
	int index = 0;
	workingNode = firstNode;
	while (workingNode != NULL)
	{
		cout << index + 1 << ": " << workingNode->item << endl;
		workingNode = workingNode->next;
		index++;
	}
}