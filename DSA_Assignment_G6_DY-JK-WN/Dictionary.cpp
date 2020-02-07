#include "pch.h"
#include "Dictionary.h"

template <class ItemType>
Dictionary<ItemType>::Dictionary()
{
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		items[i] = NULL; // setting all items to NULL on init so that lines like if (currentNode->next != NULL) work
}


template <class ItemType>
Dictionary<ItemType>::~Dictionary()
{
}

template <class ItemType>
int Dictionary<ItemType>::hash(KeyType key)
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
	sum %= MAX_SIZE;
	return sum;
}

template <class ItemType>
bool Dictionary<ItemType>::add(KeyType newKey, string stationID, int distance) // key is station name eg Jurong East, Item is Station info
{
	Node* newNode = new Node();
	newNode->key = newKey;
	newNode->item = Station(newKey, stationID/*, distance*/);
	newNode->item.SetDistance(distance);
	newNode->next = NULL;

	int index = hash(newKey);
	if (items[index] == NULL)
	{
		items[index] = newNode;
		size++;
		return true;
	}
	else
	{
		Node* currentNode = items[index];
		if (currentNode->key == newKey)
			return false;
		while (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
			if (currentNode->key == newKey)
				return false;
		}
		currentNode->next = newNode;
		size++;
		return true;
	}
}

template <class ItemType>
void Dictionary<ItemType>::remove(KeyType key)
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

template <class ItemType>
ItemType Dictionary<ItemType>::get(KeyType key)
{
	int index = hash(key);
	Station returnItem;
	Node* currentNode = NULL;

	if (items[index] != NULL)
	{
		currentNode = items[index];
		while (currentNode->next != NULL)
			if (currentNode->key == key)
				return currentNode->item;
			else
				currentNode = currentNode->next;
	}
}

template <class ItemType>
bool Dictionary<ItemType>::isEmpty()
{
	if (size > 0)
		return false;
	else
		return true;
}

template <class ItemType>
int Dictionary<ItemType>::getLength()
{
	return size;
}

template <class ItemType>
void Dictionary<ItemType>::print() //update this function
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] == NULL)
			continue;
		else
		{
			Node* currentNode = items[i];
			while (true)
			{
				if (currentNode == NULL)
					break;
				else
				{
					cout << "Number: " << currentNode->item.getStationID() << endl;
					cout << "Number: " << currentNode->item.getStationName() << endl;
					cout << "Number: " << currentNode->item.getDistance() << endl;
					currentNode = currentNode->next;
				}
			}
		}
	}
	cout << "====================" << endl;
}

template <class ItemType>
int Dictionary<ItemType>::charvalue(char c)
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
template class Dictionary<Station>;
