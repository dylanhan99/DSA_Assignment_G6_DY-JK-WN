#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;

class Queue
{
private:
	struct Node
	{
		ItemType item;	// item
		Node     *next;	// pointer pointing to next item
	};

	Node *frontNode;	// point to the first item
	Node *backNode;	// point to the first item


public:
	// constructor
	Queue();

	~Queue();

	// enqueue (add) item at the back of queue
	bool enqueue(ItemType item);

	// dequeue (remove) item from front of queue
	bool dequeue();

	// dequeue (remove) and retrieve item from front of queue
	bool dequeue(ItemType &item);

	// retrieve (get) item from front of queue
	void getFront(ItemType &item);

	// check if the queue is empty
	bool isEmpty();

	// display items in queue from front to back
	void displayItems();
};

