#include "pch.h"
#include "ListDictionary.h"

// Lee Jia Keat
// 10177804G
// Group 6
// Constructor for ListDictionary
template <class ItemType>
ListDictionary<ItemType>::ListDictionary()
{
	size = 0;
	for (int i = 0; i < LIST_DIC_MAX_SIZE; i++)
		items[i] = NULL; // setting all items to NULL on init so that lines like if (currentNode->next != NULL) work
}


template <class ItemType>
ListDictionary<ItemType>::~ListDictionary()
{
}

// Lee Jia Keat
// 10177804G
// Group 6
// Hash function to calculate which index the object should be assigned to
template <class ItemType>
int ListDictionary<ItemType>::hash(KeyType key)
{
	//horner's rule
	int sum = 0;
	for (int i = 0; i < key.length(); i++)
	{
		int currentChar = charvalue(key[i]);
		if (charvalue(key[i]) < 0) //not an alphabet
			continue;
		sum += (currentChar * 52 + charvalue(key[i + 1]));
	}
	sum %= LIST_DIC_MAX_SIZE;
	return sum;
}

// Lee Jia Keat
// 10177804G
// Group 6
// Add vector of string into dictionary using the station prefix as the key
template <class ItemType>
bool ListDictionary<ItemType>::add(KeyType newKey, std::vector<ItemType> item)
{
	Node* newNode = new Node();
	newNode->item = item;
	newNode->next = NULL;
	newNode->key = newKey;

	int index = hash(newKey);
	if (items[index] == NULL)
	{
		items[index] = newNode;
	}
	else
	{
		Node* currentNode = items[index];
		while (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
			if (currentNode->key == newKey)
				return false;
		}
		currentNode->next = newNode;
	}
	size++;
	return true;
}

// Lee Jia Keat
// 10177804G
// Group 6
// Remove vector from the dictionary using the key to locate the vector
template <class ItemType>
void ListDictionary<ItemType>::remove(KeyType key)
{
	int index = hash(key);
	Node* currentNode = NULL;
	Node* deleteNode = NULL;

	if (items[index] != NULL)
	{
		currentNode = items[index];
		if (currentNode->next == NULL && currentNode->key == key)
		{
			delete currentNode;
			items[index] = NULL;
			size--;
			return;
		}

		while (currentNode->next != NULL)
		{
			if (currentNode->next->key == key)
			{
				deleteNode = currentNode->next;
				currentNode->next = currentNode->next->next;
				delete deleteNode;
				size--;
			}
			currentNode = currentNode->next;
		}
	}
}

// Lee Jia Keat
// 10177804G
// Group 6
// Get a pointer to the vector specified using the key
//Station Dictionary::getStation(KeyType key)
template <class ItemType>
vector<ItemType>* ListDictionary<ItemType>::get(KeyType key)
{
	int index = hash(key);
	//Station returnItem;
	Node* currentNode = NULL;

	if (items[index] != NULL)
	{
		currentNode = items[index];
		if (currentNode->key == key)
		{
			return &currentNode->item;
		}

		while (currentNode->next != NULL)
		{
			if (currentNode->key == key)
			{
				return &currentNode->item;
			}
			else
			{
				currentNode = currentNode->next;
			}

		}
		
	}
	return NULL;
}

// Lee Jia Keat
// 10177804G
// Group 6
// Get all stations of a specified key and name.
template <class ItemType>
bool ListDictionary<ItemType>::isEmpty()
{
	if (size > 0)
		return false;
	else
		return true;
}

// Lee Jia Keat
// 10177804G
// Group 6
// Get current number of objects in this dictionary
template <class ItemType>
int ListDictionary<ItemType>::getLength()
{
	return size;
}

// Lee Jia Keat
// 10177804G
// Group 6
// Determine the char alphabet integer value
//int Dictionary::charvalue(char c)
template <class ItemType>
int ListDictionary<ItemType>::charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int) 'A';
		else
			return (int)c - (int) 'a' + 26;
	}
	else
		return -1;
}

//Doesn't work with string
//template class Dictionary<string>;
template class ListDictionary<string>;

