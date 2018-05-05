#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
// define default capacity of the reply_queue
#define SIZE 100000

// Class for reply_queue
template <class X>
class reply_queue
{
	X *arr;			// array to store reply_queue elements
	int capacity;	// maximum capacity of the reply_queue
	int front;		// front points to front element in the reply_queue (if any)
	int rear;		// rear points to last element in the reply_queue
	int count;		// current size of the reply_queue

public:
	reply_queue(int size = SIZE);		// constructor

	void dequeue();
	void enqueue(X x);
	X peek();
	int size();
	bool isEmpty();
	bool isFull();
};

// Constructor to initialize reply_queue
template <class X>
reply_queue<X>::reply_queue(int size)
{
	arr = new X[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
}

// Utility function to remove front element from the reply_queue
template <class X>
void reply_queue<X>::dequeue()
{
	// check for reply_queue underflow
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}


	front = (front + 1) % capacity;
	count--;
}

// Utility function to add an item to the reply_queue
template <class X>
void reply_queue<X>::enqueue(X item)
{
	// check for reply_queue overflow
	if (isFull())
	{
		cout << "OverFlow\nProgram Terminated\n";
		exit(2);
	}


	rear = (rear + 1) % capacity;
	arr[rear] = item;
	count++;
}

// Utility function to return front element in the reply_queue
template <class X>
X reply_queue<X>::peek()
{
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	return arr[front];
}

// Utility function to return the size of the reply_queue
template <class X>
int reply_queue<X>::size()
{
	return count;
}

// Utility function to check if the reply_queue is empty or not
template <class X>
bool reply_queue<X>::isEmpty()
{
	return (size() == 0);
}

// Utility function to check if the reply_queue is full or not
template <class X>
bool reply_queue<X>::isFull()
{
	return (size() == capacity);
}
