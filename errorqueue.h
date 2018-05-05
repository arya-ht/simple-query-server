#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
// define default capacity of the error_queue
#define SIZE 100000

// Class for error_queue
template <class X>
class error_queue
{
	X *arr;			// array to store error_queue elements
	int capacity;	// maximum capacity of the error_queue
	int front;		// front points to front element in the error_queue (if any)
	int rear;		// rear points to last element in the error_queue
	int count;		// current size of the error_queue

public:
	error_queue(int size = SIZE);		// constructor

	void dequeue();
	void enqueue(X x);
	X peek();
	int size();
	bool isEmpty();
	bool isFull();
};

// Constructor to initialize error_queue
template <class X>
error_queue<X>::error_queue(int size)
{
	arr = new X[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
}

// Utility function to remove front element from the error_queue
template <class X>
void error_queue<X>::dequeue()
{
	// check for error_queue underflow
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(2);
	}


	front = (front + 1) % capacity;
	count--;
}

// Utility function to add an item to the error_queue
template <class X>
void error_queue<X>::enqueue(X item)
{
	// check for error_queue overflow
	if (isFull())
	{
		cout << "OverFlow\nProgram Terminated\n";
		exit(1);
	}


	rear = (rear + 1) % capacity;
	arr[rear] = item;
	count++;
}

// Utility function to return front element in the error_queue
template <class X>
X error_queue<X>::peek()
{
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	return arr[front];
}

// Utility function to return the size of the error_queue
template <class X>
int error_queue<X>::size()
{
	return count;
}

// Utility function to check if the error_queue is empty or not
template <class X>
bool error_queue<X>::isEmpty()
{
	return (size() == 0);
}

// Utility function to check if the error_queue is full or not
template <class X>
bool error_queue<X>::isFull()
{
	return (size() == capacity);
}
