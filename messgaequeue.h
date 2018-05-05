#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
// define default capacity of the message_queue
#define SIZE 100000

// Class for message_queue
template <class X>
class message_queue
{
	X *arr;			// array to store message_queue elements
	int capacity;	// maximum capacity of the message_queue
	int front;		// front points to front element in the message_queue (if any)
	int rear;		// rear points to last element in the message_queue
	int count;		// current size of the message_queue

public:
	message_queue(int size = SIZE);		// constructor

	void dequeue();
	void enqueue(X x);
	X peek();
	int size();
	bool isEmpty();
	bool isFull();
};

// Constructor to initialize message_queue
template <class X>
message_queue<X>::message_queue(int size)
{
	arr = new X[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
}

// Utility function to remove front element from the message_queue
template <class X>
void message_queue<X>::dequeue()
{
	// check for message_queue underflow
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}


	front = (front + 1) % capacity;
	count--;
}

// Utility function to add an item to the message_queue
template <class X>
void message_queue<X>::enqueue(X item)
{
	// check for message_queue overflow
	if (isFull())
	{
		cout << "OverFlow\nProgram Terminated\n";
		exit(4);
	}


	rear = (rear + 1) % capacity;
	arr[rear] = item;
	count++;
}

// Utility function to return front element in the message_queue
template <class X>
X message_queue<X>::peek()
{
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	return arr[front];
}

// Utility function to return the size of the message_queue
template <class X>
int message_queue<X>::size()
{
	return count;
}

// Utility function to check if the message_queue is empty or not
template <class X>
bool message_queue<X>::isEmpty()
{
	return (size() == 0);
}

// Utility function to check if the message_queue is full or not
template <class X>
bool message_queue<X>::isFull()
{
	return (size() == capacity);
}
