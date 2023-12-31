//Names: Alexis Martinez, Angie Campos, Neidy Malaga, & Vivian Huynh
//Date: 10/4/2023
//Description: Chapter 7 Assignments - Applications using Stacks

#include <iostream> //For cout
#include <vector>   //For vector
#include <iomanip>  //For formatting output
#include <stack>    //For stack
#include <string>   //For string
#include <sstream>  //For stringstream
#include <cctype>   //For isdigit, isalpha, & isspace
#include <cmath>    //For math operators

//HEADER FILES
#include "input.h" //For input validation
#include "Queen.h" //For option 3
using namespace std;

//PROTOTYPES
int mainMenu();

//Option 1 - Simple Calculator
void option1();
int precedence(char);
string infixToPostfix(const string&);
double evaluatePostfix(const string&);
bool areParenthesesBalanced(const string&);

//Option 2 - Translation of arithmetic expression
void option2();

//Option 3 - n-Queens Problem
void option3();

//Precondition : N/A
//Posctondition: Calls option 1, 2, and 3
int main()
{
	do
	{
		system("cls");
		switch (mainMenu())
		{
		case 0: exit(0);
		case 1: system("cls"); option1(); break;
		case 2: system("cls"); option2(); break;
		case 3: system("cls"); option3(); break;
		default: cout << "\t\tERROR: - Invalid option. Please re-enter"; break;
		}
		cout << "\n";
		system("pause");
	} while (true);

	return 0;
}

//Precondition : Calls from main
//Posctondition: Returns integer choice
int mainMenu()
{
	cout << "\n\tCMPR131 Chapter 7: Applications using Stacks by Group 5 () 10/12/2023";
	cout << "\n\t" << string(100, char(205));
	cout << "\n\t\t1> Simple Calculator (problem 9, pg 391)";
	cout << "\n\t\t2> Translation of arithmetic expression(problem 10, pg 391)";
	cout << "\n\t\t3> n-Queens Problem(problem 11, pg 391-292)";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\t0. Exit";
	cout << "\n\t" << string(100, char(205));

	return inputInteger("\n\t\tOption: ", 0, 3);
}

//Precondition : Called from main
//Postcondition: Calculate the arithmetic expression and output the solution
void option1()
{
	string infixExpression = "";
	string postfixExpression = "";
	double result = 0.0;

	cout << "\n\t1> Simple Calculator";
	cout << "\n\t" << string(100, char(196));
	infixExpression = inputString("\n\t\tType a fully parenthesized arithmetic expression: \n\n\t\t", true);

	if (!areParenthesesBalanced(infixExpression)) {
		cout << "\n\t\tERROR: Parentheses don't match.\n";
		return;
	}

	for (char letter : infixExpression) {
		if (isalpha(letter)) {
			cout << "\n\t\tERROR: Invalid arithmetic expression.\n";
			return;
		}
	}

	postfixExpression = infixToPostfix(infixExpression);
	result = evaluatePostfix(postfixExpression);
	cout << "\n\t\tIt evaluates to " << result << ".";
}

//Precondition : accepts a char data type
//Postcondition: returns an integer symbolizing its precedence
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
//Precondition : Accepts a const string data type
//Postcondition: Converts this string into PostFix notation
string infixToPostfix(const string& infix) {
	stack<char> operators;
	stringstream output;
	bool mightBeUnary = true; // is it a negative number or is it subtracting 

	for (int i = 0; i < infix.size(); i++) {
		char character = infix[i];

		if ((isdigit(character)) || (character == '.') || (isalpha(character))) {
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

//Precondition : Accepts a const string 
//Postcondition: evaluates the postFix and returns a double 
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

//Precondition : Accepts a const string 
//Postcondition: checks to see if the parentheses are balanced in the expression
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

//Precondition : Called from main
//Postcondition: Output the converted infix expression into postfix expression
void option2()
{
	string infix = "";
	string postfix = "";
	char choice = 'N';
	cout << "\n\t2> Translation of Arithmetic Expression";
	cout << "\n\t" << string(100, char(196));
	do
	{
		postfix = "";
		infix = inputString("\n\tEnter an infix expression: ", true);

		//Checks if there is an extra or missing parentheses
		if (!areParenthesesBalanced(infix))
		{
			cout << "\n\tInfix expression  : " << infix;
			cout << "\n\tPostfix expression: ERROR: inbalanced parentheses\n";
			return;
		}

		postfix = infixToPostfix(infix);

		//Output the solved conversion of infix to postfix
		cout << "\n\tInfix expression  : " << infix;
		cout << "\n\tPostfix expression: " << postfix << '\n';

		choice = inputChar("\n\tContinue a new expression? (Y-yes or N-no) ", static_cast<string>("YN"));

	} while (choice != 'N');
}

//Precondition : Called from main
//Postcondition: lets user chose a part in N-Queens and then solves the game
void option3()
{
	Queen puzzle;
	int numberOfQueens = 0;
	int column = 0;

	cout << "\n\t3> n-Queens Problem";
	numberOfQueens = inputInteger("\n\tEnter a number(1...100) of queens: ", 1, 100);
	puzzle.set_Size(numberOfQueens);
	column = inputInteger("\n\tEnter the column(1.." + to_string(numberOfQueens) + ") to place the first queen : ", 1, numberOfQueens);
	puzzle.set_Line(column - 1);

	if (numberOfQueens == 2 || numberOfQueens == 3) {
		cout << "\n\tNo solution.";
		return;
	}

	puzzle.set_Board();
	cout << puzzle;
}
