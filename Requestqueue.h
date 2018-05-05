#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
// define default capacity of the request_queue
#define SIZE 100000

// Class for request_queue
template <class X>
class request_queue
{
	X *arr;			// array to store request_queue elements
	int capacity;	// maximum capacity of the request_queue
	int front;		// front points to front element in the request_queue (if any)
	int rear;		// rear points to last element in the request_queue
	int count;		// current size of the request_queue

public:
	request_queue(int size = SIZE);		// constructor

	void dequeue();
	void enqueue(X x);
	X peek();
	int size();
	bool isEmpty();
	bool isFull();
};

// Constructor to initialize request_queue
template <class X>
request_queue<X>::request_queue(int size)
{
	arr = new X[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
}

// Utility function to remove front element from the request_queue
template <class X>
void request_queue<X>::dequeue()
{
	// check for request_queue underflow
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}


	front = (front + 1) % capacity;
	count--;
}

// Utility function to add an item to the request_queue
template <class X>
void request_queue<X>::enqueue(X item)
{
	// check for request_queue overflow
	if (isFull())
	{
		cout << "OverFlow\nProgram Terminated\n";
		exit(3);
	}


	rear = (rear + 1) % capacity;
	arr[rear] = item;
	count++;
}

// Utility function to return front element in the request_queue
template <class X>
X request_queue<X>::peek()
{
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	return arr[front];
}

// Utility function to return the size of the request_queue
template <class X>
int request_queue<X>::size()
{
	return count;
}

// Utility function to check if the request_queue is empty or not
template <class X>
bool request_queue<X>::isEmpty()
{
	return (size() == 0);
}

// Utility function to check if the request_queue is full or not
template <class X>
bool request_queue<X>::isFull()
{
	return (size() == capacity);
}
