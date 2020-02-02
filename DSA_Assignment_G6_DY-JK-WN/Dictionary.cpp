#include "pch.h"
#include "Dictionary.h"

Dictionary::Dictionary()
{
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		items[i] = NULL; // setting all items to NULL on init so that lines like if (currentNode->next != NULL) work
}


Dictionary::~Dictionary()
{
}

int Dictionary::hash(KeyType key)
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

bool Dictionary::add(KeyType newKey, string stationID, int distance) // key is station name eg Jurong East, Item is Station info
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

void Dictionary::remove(KeyType key)
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

Station Dictionary::get(KeyType key)
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

bool Dictionary::isEmpty()
{
	if (size > 0)
		return false;
	else
		return true;
}

int Dictionary::getLength()
{
	return size;
}

void Dictionary::print() //update this function
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

int Dictionary::charvalue(char c)
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
