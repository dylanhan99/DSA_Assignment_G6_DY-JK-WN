#pragma once
#include <iostream>
#include <string>;

using namespace std;
typedef string ItemType;
const int ARRAY_MAX_SIZE = 101;

class ArrayList
{
private:
	ItemType items[ARRAY_MAX_SIZE];
	int size;

public:
	ArrayList();
	~ArrayList();

	bool add(ItemType item);

	// add an item at a specified position in the list (insert)
	// pre : 0 <= index <= size && size < MAX_SIZE
	// post: item is added to the specified position in the list
	//       size of list is increased by 1
	bool add(int index, ItemType item);

	// remove an item at a specified position in the list
	// pre : 0 <= index < size
	// post: item is removed the specified position in the list
	//       size of list is decreased by 1
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	ItemType get(int index);

	// check if the list is empty
	// pre : none
	// post: none
	// return true if the list is empty; otherwise returns false
	bool isEmpty();

	// check the size of the list
	// pre : none
	// post: none
	// return the number of items in the list
	int getLength();

	void print();

	void replace(int index, ItemType item);

	//ItemType search(string name);
	ArrayList search(string name);

	int getIndex(string name);
};

