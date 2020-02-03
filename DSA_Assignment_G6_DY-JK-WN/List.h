#pragma once
#include <iostream>
using namespace std;
#include <string>;

//const int MAX_SIZE = 100;
typedef string ItemType;
const int MAX_SIZE = 101;

class List
{
private:
	struct Node
	{
		ItemType item;	// item
		Node*     next;	// pointer pointing to next item
	};

	Node* firstNode;
	Node* lastNode;
	Node* workingNode;

	int  size;		// number of items in the list

public:

	List();
	~List();

	// add an item to the back of the list (append)
	bool add(ItemType item);

	// add an item at a specified position in the list (insert)
	bool add(int index, ItemType item);

	ItemType get(int index);

	// remove an item at a specified position in the list
	void remove(int index);

	int getSize();

	// display all the items in the list
	void print();
};