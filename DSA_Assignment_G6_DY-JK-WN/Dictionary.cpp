#include "pch.h"
#include "Dictionary.h"

// Han Wei Dylan
// 10178483G
// Group 6
// Dictionary constructor
template <class ItemType>
Dictionary<ItemType>::Dictionary()
{
	size = 0;
	for (int i = 0; i < DIC_MAX_SIZE; i++)
		items[i] = NULL; // setting all items to NULL on init so that lines like if (currentNode->next != NULL) work
}

// Han Wei Dylan
// 10178483G
// Group 6
// Dictionary destructor
template <class ItemType>
Dictionary<ItemType>::~Dictionary()
{
}

// Han Wei Dylan
// 10178483G
// Group 6
// Hash function to calculate which index the object should be assigned to
template <class ItemType>
int Dictionary<ItemType>::hash(KeyType key)
{
	trimAll(&key);

	//horner's rule
	int sum = 0;
	for (int i = 0; i < key.length(); i++)
	{
		int currentChar = charvalue(key[i]);
		if (charvalue(key[i]) < 0) //not an alphabet
			continue;
		sum += (currentChar * 52 + charvalue(key[i + 1]));
	}
	//sum %= MAX_SIZE;
	return sum;
}

// Han Wei Dylan
// 10178483G
// Group 6
// Add new stations into dictionary
template <class ItemType>
bool Dictionary<ItemType>::add(KeyType newKey, string stationID, int distance) // key is station name eg Jurong East, Item is Station info
{
	Node* newNode = new Node();
	newNode->item = Station(newKey, stationID/*, distance*/);
	newNode->item.SetDistance(distance);
	newNode->next = NULL;
	//trimAll(&newKey);
	int index = hash(newKey) % DIC_MAX_SIZE;
	newNode->key = newKey;
	if (items[index] == NULL)
	{
		items[index] = newNode;
	}
	else
	{
		Node* currentNode = items[index];
		//if (currentNode->key == newKey)
		//	return false;
		int x = 0;
		while (currentNode->key != newKey)
		{
			x += 1;
			index = (hash(newKey) + x) % DIC_MAX_SIZE;

			if (items[index] == NULL)
			{
				items[index] = newNode;
				size++;
				return true;
			}
			currentNode = items[index];

		}

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
// Get all the stations in the dictionary into the dictionary
template <class ItemType>
vector<ItemType> Dictionary<ItemType>::getAll()
{
	vector<ItemType> stationsList;
	for (int i = 0; i < DIC_MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			Node* node = items[i];
			stationsList.push_back(node->item);
		}
	}
	return stationsList;
}

// Han Wei Dylan
// 10178483G
// Group 6
// Remove staitons from the dictionary using the key to locate the staiton
template <class ItemType>
void Dictionary<ItemType>::remove(KeyType key)
{
	int index = hash(key) % DIC_MAX_SIZE;
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
// Get a pointer to the station object specified using the key
//Station Dictionary::getStation(KeyType key)
template <class ItemType>
ItemType* Dictionary<ItemType>::get(KeyType key)
{
	int index = hash(key) % DIC_MAX_SIZE;
	//Station returnItem;
	Node* currentNode = NULL;

	if (items[index] != NULL)
	{
		currentNode = items[index];
		if (currentNode->key == key)
		{
			return &currentNode->item;
		}

		int x = 0;
		while (currentNode->key != key)
		{
			x += 1;
			index = (hash(key) + x) % DIC_MAX_SIZE;
			if (items[index != NULL])
			{
				currentNode = items[index];

				if (currentNode->key == key)
				{
					return &currentNode->item;
				}
			}

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

		//currentNode = items[index];
		//while (currentNode->next != NULL)
		//{
		//	if (currentNode->key == key)
		//	{
		//		return &currentNode->item;
		//	}
		//	else
		//	{
		//		currentNode = currentNode->next;
		//	}
		//}
	}
	return NULL;
}

// Lee Jia Keat
// 10177804G
// Group 6
// Get a pointer to the station object specified using the key
template <class ItemType>
bool Dictionary<ItemType>::get(KeyType key, ItemType* item)
{
	int index = hash(key) % DIC_MAX_SIZE;
	//Station returnItem;
	Node* currentNode = NULL;

	if (items[index] != NULL)
	{
		currentNode = items[index];
		if (currentNode->key == key)
		{
			item = &currentNode->item;
			return true;
		}

		while (currentNode->next != NULL)
		{
			if (currentNode->key == key)
			{
				item = &currentNode->item;
				return true;
			}
			else
			{
				currentNode = currentNode->next;
			}

		}
	}
	return false;
}

// Lee Jia Keat
// 10177804G
// Group 6
// Check if dictionary contains the station specified
template <class ItemType>
bool Dictionary<ItemType>::contains(KeyType key)
{
	int index = hash(key) % DIC_MAX_SIZE;
	//Station returnItem;
	Node* currentNode = NULL;

	if (items[index] != NULL)
	{
		currentNode = items[index];
		if (currentNode->key == key)
		{
			return true;
		}

		int x = 0;
		while (currentNode->key != key)
		{
			x += 1;
			index = (hash(key) + x) % DIC_MAX_SIZE;
			if (items[index != NULL])
			{
				currentNode = items[index];

				if (currentNode->key == key)
				{
					return true;
				}
			}

		}

		while (currentNode->next != NULL)
		{
			if (currentNode->key == key)
			{
				return true;
			}
			else
			{
				currentNode = currentNode->next;
			}

		}
	}
	return false;
}

// Han Wei Dylan
// 10178483G
// Group 6
// Get all stations of a specified key and name.
template <class ItemType>
vector<Station>* Dictionary<ItemType>::getStations(KeyType key)
{
	//trimAll(&key);
	int index = hash(key) % DIC_MAX_SIZE;
	Node* currentNode = NULL;
	vector<Station>* stationsList = new vector<Station>();

	if (items[index] != NULL)
	{
		currentNode = items[index];
		while (currentNode/*->next*/ != NULL)
		{
			if (currentNode->key == key)
				stationsList->push_back(currentNode->item);
			currentNode = currentNode->next;
		}
		//return stationsList;
	}
	return stationsList;
}

// Lee Jia Keat
// 10177804G
// Group 6
// Find station object in dictionary with the entered id
template <class ItemType>
ItemType Dictionary<ItemType>::getByID(string id)
{
	for (int i = 0; i < DIC_MAX_SIZE; i++)
	{
		Node* currentNode = NULL;
		if (items[i] != NULL)
		{
			currentNode = items[i];
			while (currentNode != NULL)
			{
				ItemType item = currentNode->item;
				if (item.getStationID() == id)
					return item;
				currentNode = currentNode->next;
			}
			//return stationsList;
		}

	}
}

// Han Wei Dylan
// 10178483G
// Group 6
// Get all stations of a specified key and name.
template <class ItemType>
bool Dictionary<ItemType>::isEmpty()
{
	if (size > 0)
		return false;
	else
		return true;
}

// Han Wei Dylan
// 10178483G
// Group 6
// Get current number of objects in this dictionary
template <class ItemType>
int Dictionary<ItemType>::getLength()
{
	return size;
}

// Han Wei Dylan
// 10178483G
// Group 6
// Print station information of specified station
template <class ItemType>
void Dictionary<ItemType>::printStationInformation(KeyType stationName)
{
	vector<Station>* stationsList = this->getStations(stationName);

	if (stationsList->size() >= 1)
	{
		cout << endl;
		cout << "\t" << "Line\t" << "StationID\t" << "StationName\t" << "Distance to next" << endl;
		for (int i = 0; i < stationsList->size(); i++)
		{
			cout << "\t" << stationsList->at(i).getLine()
				<< "\t" << stationsList->at(i).getStationID()
				<< "\t\t" << stationsList->at(i).getStationName()
				<< "\t\t" << stationsList->at(i).getDistance();
		}
		cout << endl;
		//return;
	}
	else
		cout << "No station named - " << stationName << endl;
}

// Han Wei Dylan
// 10178483G
// Group 6
// Determine the char alphabet integer value
//int Dictionary::charvalue(char c)
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
