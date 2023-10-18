#pragma once
#include <iostream>
#include <stack> //for 2d vectors
#include <string> //for string
using namespace std;
class Queen {
private:
	stack<char> board;
	int size;
public:
	Queen(); //constructor

	//mutators
	void set_Size(const int&);
	void set_Line(const int&);
	void set_Board();

	//accessors
	friend ostream& operator<< (ostream&, const Queen&);
	
};
