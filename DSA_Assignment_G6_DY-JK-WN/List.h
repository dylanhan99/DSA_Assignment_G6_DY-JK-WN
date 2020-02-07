#pragma once
#include <iostream>
using namespace std;
#include <string>;

//typedef string ItemType;
const int MAX_SIZE = 101;

template <class ListTemplate>
class List
{
private:
	struct Node
	{
		ListTemplate item;	// item
		Node*		 next;	// pointer pointing to next item
	};

	Node* firstNode;
	Node* lastNode;
	Node* workingNode;

	int  size;		// number of items in the list

public:

	List();
	~List();

	int getSize();

	void setSize(int i);

	// add an item to the back of the list (append)
	bool add(ListTemplate item);

	// add an item at a specified position in the list (insert)
	bool add(int index, ListTemplate item);

	ListTemplate get(int index);

	// remove an item at a specified position in the list
	void remove(int index);

	// display all the items in the list
	void print();
};