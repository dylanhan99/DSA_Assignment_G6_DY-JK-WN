#include "pch.h"
#include "stack.h"

Stack::Stack()
{
	topNode = NULL;
}

Stack::~Stack()
{

}

bool Stack::push(StackItemType item)
{
	if (isEmpty())
	{
		Node *newNode = new Node;
		newNode->next = NULL;
		newNode->item = item;
		topNode = newNode;

		return true;
	}
	else
	{
		Node *newNode = new Node;
		newNode->next = topNode;
		newNode->item = item;
		topNode = newNode;

		return true;
	}

	return false;

}

bool Stack::pop()
{
	if (!isEmpty())
	{
		Node *current = topNode;
		topNode = topNode->next;
		current->next = NULL;

		delete current;
		return true;
	}
	return false;
}

bool Stack::pop(StackItemType & item)
{
	if (!isEmpty())
	{
		Node *current = topNode;
		topNode = topNode->next;
		current->next = NULL;
		item = current->item;

		delete current;
		return true;
	}
	return false;
}

void Stack::getTop(StackItemType & item)
{
	item = topNode->item;
}

bool Stack::isEmpty()
{
	if (topNode == NULL)
		return true;

	return false;
}

void Stack::displayInOrder()
{
	Node* currentNode = topNode;
	while (currentNode != NULL)
	{
		cout << currentNode->item << endl;
		currentNode = currentNode->next;
	}
}

void Stack::displayInOrderOfInsertion()
{
	Node* currentNode = topNode;
	Stack s;
	while (currentNode != NULL)
	{
		s.push(currentNode->item);
		currentNode = currentNode->next;
	}
	s.displayInOrder();

}
