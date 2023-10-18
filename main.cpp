#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include "input.h"

using namespace std;


int mainMenu();
void caseOne();
int precedence(char);
string infixToPostfix(const string&);
double evaluatePostfix(const string&);
bool areParenthesesBalanced(const string&);

int main() {
	do {
		system("cls");
		switch (mainMenu()) {
		case 0: return EXIT_SUCCESS;
		case 1: caseOne(); break;
			//case 2: caseTwo(); break;
			//case 3: caseThree(); break;
		}
		cout << "\n\n\t\t";
		system("pause");
	} while (true);

	return EXIT_SUCCESS;
}

//PreCondition: None
//PostConidtion: Displays menu to user and returns an integer
int mainMenu() {
	cout << "\n\t\tCMPR131 Chapter 7: Applications using Stacks by Prof Q (1/6/21)";
	cout << "\n\t\t" << string(100, char(205));
	cout << "\n\t\t1> Simple Calculator (problem 9, pg 391)";
	cout << "\n\t\t2> Translation of arithmetic expression (problem 10, pg 391)";
	cout << "\n\t\t3> n-Queens Problem (problem 11, pg 391-292)";
	cout << "\n\t\t" << string(100, char(196));
	cout << "\n\t\t0> Exit";
	cout << "\n\t\t" << string(100, char(205));

	return inputInteger("\n\t\tOption: ", 0, 3);
}

//PreCondition: accepts a char data type
//PostCondition: returns an integer symbolizing its precedence
int precedence(char symbol) {
	switch (symbol) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return 0;
	}
}
//PreCondition: Accepts a const string data type
//PostCondition: Converts this string into PostFix notation
string infixToPostfix(const string& infix) {
	stack<char> operators;
	stringstream output;
	bool mightBeUnary = true; // is it a negative number or is it subtracting 

	for (int i = 0; i < infix.size(); i++) {
		char character = infix[i];

		if (isdigit(character) || character == '.') {
			output << character;
			mightBeUnary = false;
		}
		else if (character == '(') {
			operators.push(character);
			mightBeUnary = true;
		}
		else if (character == ')') {
			while (!operators.empty() && operators.top() != '(') {
				output << ' ' << operators.top();
				operators.pop();
			}
			if (!operators.empty()) operators.pop(); 
			mightBeUnary = false;
		}
		else if (character == '+' || character == '-' || character == '*' || character == '/' || character == '^') {
			if (character == '-' && mightBeUnary) {
				i++;
				while (i < infix.size() && isspace(infix[i]))
					i++;
				while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
					output << '-' << infix[i];
					i++;
				}
				i--;
				mightBeUnary = false;
				continue;
			}
			output << ' ';
			while (!operators.empty() && precedence(character) <= precedence(operators.top())) {
				output << operators.top() << ' ';
				operators.pop();
			}
			operators.push(character);
			mightBeUnary = true;
		}
		else if (isspace(character)) {
			continue; 
		}
	}

	while (!operators.empty()) {
		output << ' ' << operators.top();
		operators.pop();
	}

	return output.str();
}

//PreCondition: Accepts a const string 
//PostCondition: evaluates the postFix and returns a double 
double evaluatePostfix(const string& postfix) {
	stack<double> values;
	stringstream postFixStream(postfix);
	string token;

	while (postFixStream >> token) {
		if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
			values.push(stod(token));
		}
		else {
			double val1 = values.top();
			values.pop();

			double val2 = 0;
			if (!values.empty()) {
				val2 = values.top();
				values.pop();
			}
			if (token == "+") 
				values.push(val2 + val1);
			else if (token == "-") 
				values.push(val2 - val1);
			else if (token == "*") 
				values.push(val2 * val1);
			else if (token == "/") 
				values.push(val2 / val1);
			else if (token == "^") 
				values.push(pow(val2, val1));
		}
	}

	return values.top();
}

//PreCondition: Accepts a const string 
//PostCondition: checks to see if the paranthesis are balanced in the expression
bool areParenthesesBalanced(const string& expression) {
	stack<char> characterStack;
	int count = 0;

	for (char letter : expression) {
		if (letter == '(') {
			characterStack.push(letter);
			count++;
		}
		else if (letter == ')') {
			if (characterStack.empty()) {
				return false;  
			}
			characterStack.pop();
			count++;
		}
	}
	if (count == 0) {  
		return false;
	}
	return characterStack.empty();
}

//PreCondition: None
//PostConidtion: Solves fully parenthesized arithmetic expressions
void caseOne() {
	system("cls");

	cout << "\n\t1> Simple Calculator";
	cout << '\n' << string(100, char(196));

	string infixExpression = inputString("\n\t\tType a fully parenthesized arithmetic expression: \n\n\t\t", true);

	if (!areParenthesesBalanced(infixExpression)) {
		cout << "\n\t\tERROR: Parentheses don't match.";
		return;
	}

	string postfixExpression = infixToPostfix(infixExpression);
	double result = evaluatePostfix(postfixExpression);
	cout << "\n\t\tIt evaluates to " << result << ".";
}

