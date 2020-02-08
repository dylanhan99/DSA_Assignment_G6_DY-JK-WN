// Stack.h (Pointer-based implementation)
#include <iostream>
using namespace std;
typedef int StackItemType;

class Stack
{
private:
	struct Node
	{
		int item;
		Node *next;
	};

	Node *topNode;

public:
	//Default constructor
	Stack();
	//Destructor
	~Stack();

	//check if the stack is empty
	bool isEmpty();

	//push item on top of the stack
	bool push(StackItemType item);

	//pop item from top of stack
	bool pop();

	//retrieve and pop item from top of stack
	bool pop(StackItemType &item);

	//retrieve item from top of stack
	void getTop(StackItemType &item);

	//display items in stack in order
	void displayInOrder();

	//display items in stack in order of insertion
	void displayInOrderOfInsertion();

};