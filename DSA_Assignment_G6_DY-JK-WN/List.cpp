#include "pch.h"
#include "List.h"  

// constructor
List::List() 
{ 
	size = 0; 
}

// add an item to the back of the list (append)
bool List::add(ItemType item)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		//cout << "size = " << size;
		items[size] = item;
		size++;
	}
	return success;
}

// add an item at a specified position in the list (insert)
bool List::add(int index, ItemType item)
{
	bool success = (index >= 0) && (index <= size) && (size < MAX_SIZE);
	if (success)
	{
		for (int pos = size; pos >= index; pos--)
			items[pos] = items[pos - 1];
		items[index] = item;
		size++;  
	}
	return success;
}

// remove an item at a specified position in the list
void List::remove(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{
		for (int pos = index; pos < size; pos++)
			items[pos] = items[pos + 1];
		size--;
	}

}

// get an item at a specified position of the list (retrieve)
ItemType List::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return "rip";
}

// check if the list is empty
bool List::isEmpty() { return size == 0; }

// check the size of the list
int List::getLength() { return size; }

// display the items in the list
void List::print()
{
	for (int i = 0; i < getLength(); i++)
	{
		std::cout << items[i] << endl;
	}
}

// replace the  item in the specified index in the list
void List::replace(int index, ItemType item)
{

}

bool List::resizeList(int newSize)
{
	if (newSize >= this->size)
	{
		items->resize(newSize);
		return true;
	}
	return false;
}