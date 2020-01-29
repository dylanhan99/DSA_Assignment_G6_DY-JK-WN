// Dictionary.h - - Specification of Dictionary ADT
#include<string>
#include<iostream>
using namespace std;

#include "Station.h"

//const int MAX_SIZE = 101;

//struct Station
//{
//	bool isInterchange;
//	List stationIDs;
//};

//typedef Station ItemType;
typedef string KeyType;

class Dictionary
{
private:
	int MAX_SIZE;
	struct Node
	{
		KeyType  key;   // search key
		Station item;	// data item
		Node     *next;	// pointer pointing to next item
	};

	Node *items[1];
	int  size;			// number of items in the Dictionary

public:
	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	int hash(KeyType key);

	// add a new item with the specified key to the Dictionary
	bool add(KeyType newKey, Station newItem);

	// remove an item with the specified key in the Dictionary
	void remove(KeyType key);

	// get an item with the specified key in the Dictionary (retrieve)
	Station get(KeyType key);

	// check if the Dictionary is empty
	bool isEmpty();

	// check the size of the Dictionary
	int getLength();

	//------------------- Other useful functions -----------------
	// display the items in the Dictionary
	void print();

	int charvalue(char c);
};
