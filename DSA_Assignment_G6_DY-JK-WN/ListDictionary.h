// Dictionary.h - - Specification of Dictionary ADT
#pragma once
#include<string>
#include<iostream>
#include <vector>

using namespace std;

typedef string KeyType;
const int LIST_DIC_MAX_SIZE = 600;

template <class ItemType>
class ListDictionary
{
	struct Node
	{
		KeyType  key;   // search key
		vector<ItemType> item;	// data item
		Node     *next;	// pointer pointing to next item
	};

	Node *items[LIST_DIC_MAX_SIZE];
	int  size;			// number of items in the Dictionary

public:
	ListDictionary();
	~ListDictionary();

	int hash(KeyType key);

	// add a new item with the specified key to the Dictionary
	bool add(KeyType newKey, vector<ItemType> item);

	// remove an item with the specified key in the Dictionary
	void remove(KeyType key);
	
	// get list
	vector<ItemType>* get(KeyType key);

	// check if the Dictionary is empty
	bool isEmpty();

	// check the size of the Dictionary
	int getLength();


	int charvalue(char c);
};


