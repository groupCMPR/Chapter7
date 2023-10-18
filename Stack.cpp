#include "Stack.h"
Stack::Stack()
{
	container.clear();
}

//ACCESSORS
bool Stack::isEmpty() const
{
	return container.empty();
}
char Stack::top() const
{
	if (isEmpty())
	{
		return -1;
	}
	return container.back();
}

//MUTATORS
void Stack::push(char value)
{
	container.push_back(value);
}
void Stack::pop()
{
	if (isEmpty())
	{
		return;
	}
	return container.pop_back();
}