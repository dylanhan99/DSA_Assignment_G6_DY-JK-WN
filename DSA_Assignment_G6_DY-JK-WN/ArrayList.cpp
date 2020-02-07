#include "pch.h"
#include "ArrayList.h"


ArrayList::ArrayList()
{
	size = 0;
}


ArrayList::~ArrayList()
{
}

bool ArrayList::add(ItemType item)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		items[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// add an item at a specified position in the list (insert)
bool ArrayList::add(int index, ItemType item)
{
	bool success = (index >= 0) && (index <= size) && (size < MAX_SIZE);
	if (success)
	{  // make room for the item by shifting all items at
	   // positions >= index toward the end of the
	   // List (no shift if index == size + 1)
		for (int pos = size; pos >= index; pos--)
			items[pos] = items[pos - 1];
		// insert the item
		items[index] = item;
		size++;  // increase the size by 1
	}
	return success;
}

// remove an item at a specified position in the list
void ArrayList::remove(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{  // delete item by shifting all items at positions >
	   // index toward the beginning of the list
	   // (no shift if index == size)
		for (int pos = index; pos < size; pos++)
			items[pos] = items[pos + 1];
		size--;  // decrease the size by 1
	}

}

// get an item at a specified position of the list (retrieve)
ItemType ArrayList::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];

}

// check if the list is empty
bool ArrayList::isEmpty() { return size == 0; }

// check the size of the list
int ArrayList::getLength() { return size; }

// display the items in the list
void ArrayList::print()
{
	if (size <= 0)
	{
		cout << "No stations found." << endl;
	}

	for (int pos = 0; pos < size; pos++)
	{
		cout << items[pos] << endl;
	}
}

// replace the  item in the specified index in the list
void ArrayList::replace(int index, ItemType item)
{
	items[index] = item;
}

//ItemType List::search(string name)
//{
//	for (int pos = 0; pos < size; pos++)
//	{
//		if (items[pos].getName() == name)
//		{
//			return items[pos];
//		}
//		else
//			continue;
//	}
//
//	cout << "No results found" << endl;
//}

ArrayList ArrayList::search(string name)
{
	ArrayList results;
	int x = 0;
	for (int pos = 0; pos < size; pos++)
	{
		if (items[pos] == name)
		{
			results.add(items[pos]);
			x++;
		}
		else
			continue;
	}

	if (x <= 0)
		cout << "No results found." << endl;
	else
		cout << x << " results found for " << name << ":" << endl;

	return results;

}

int ArrayList::getIndex(string name)
{
	for (int pos = 0; pos < size; pos++)
	{
		if (items[pos] == name)
		{
			return pos;
		}
		else
			continue;
	}
}
