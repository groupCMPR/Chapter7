//Name: Vivian Huynh
//Date: 10/14/2023
//Description: Header file for class Stack

#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Stack
{
private:
	vector<char> container;

public:
	//CONSTRUCTOR
	Stack();

	//ACCESSORS
	bool isEmpty() const;
	char top() const;

	//MUTATORS
	void push(char);
	void pop();
};

