#include "pch.h"
#include "Queue.h"


Queue::Queue()
{
}


Queue::~Queue()
{
	delete this;
}

bool Queue::enqueue(ItemType item)
{
	Node* newNode = new Node();
	newNode->item = item;
	newNode->next = NULL;
	if (isEmpty())
	{
		frontNode = newNode;
		backNode = frontNode;
	}
	else
	{
		backNode->next = newNode;
		backNode = newNode;
	}
	return true;
}

bool Queue::dequeue()
{
	if (!isEmpty())
	{
		Node* tempNode = frontNode;
		frontNode = frontNode->next;
		delete tempNode;
		return true;
	}
	else
		return false;
}

bool Queue::dequeue(ItemType &item)
{
	if (!isEmpty())
	{
		Node* tempNode = frontNode;
		frontNode = frontNode->next;
		item = tempNode->item;
		delete tempNode;
		return true;
	}
	else
		return false;
}

void Queue::getFront(ItemType &item)
{
	item = frontNode->item;
}

bool Queue::isEmpty()
{
	if (frontNode == NULL)
		return true;
	else
		return false;
}

void Queue::displayItems()
{
	if (!isEmpty())
	{
		Node* currentNode = frontNode;
		while (true)
		{
			cout << currentNode->item << endl;
			if (currentNode->next != NULL)
				currentNode = currentNode->next;
			else
				break;
		}
	}
}