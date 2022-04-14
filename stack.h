#include <iostream>
#ifndef STACK_H
#define STACK_H

using namespace std;

#define MAX 100

template <typename T>
class Stack
{
	T *data;
	int head;
	int capacity;

public:
	Stack(int size = MAX);
	~Stack();

	void push(T data);
	void pop();
	T top();

	int size();
	bool empty();
};

template <typename T>
Stack<T>::Stack(int size)
{
	this->data = new T(size);
	this->capacity = size;
	this->head = -1;
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] this->data;
}

template <typename T>
void Stack<T>::push(T data)
{
	++this->head;
	if (head > this->capacity - 1)
	{
		this->capacity *= 2;
		T *newQueue = new T(capacity);
		copy(this->data, &this->data[capacity - 1], newQueue);
		delete[] this->data;
		this->data = newQueue;
	}
	this->data[head] = data;
}

template <typename T>
void Stack<T>::pop()
{
	if ( !this->empty() ) --this->head; 
}

template <typename T>
T Stack<T>::top()
{
	if ( this->empty() ) throw "[Error] Stack is empty"; 
	return this->data[head];
}

template <typename T>
int Stack<T>::size()
{
	return this->head + 1;
}

template <typename T>
bool Stack<T>::empty()
{
	if (this->head == -1) return true;
	return false;
}
#endif