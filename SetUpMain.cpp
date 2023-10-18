//Names: Alexis Martinez, Angie Campos, Neidy Malaga, & Vivian Huynh
//Date: 10/4/2023
//Description: Chapter 7 Assignments - Applications using Stacks

#include <iostream> //For cout
#include <iomanip>  //For formatting output

//HEADER FILES
#include "input.h" //For input validation
using namespace std;

//PROTOTYPES
int mainMenu();

//Option 1 - Simple Calculator
void option1();

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
	string arithExpression = "";
	double solution = 0.0;
	cout << "\n\t1> Simple Calculator";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\tType a fully parenthesized arithmetic expression: ";
	//cout << "\n\tERROR: Parentheses don't match.\n";
	//cout << "\n\tERROR: ERROR: Invalid arithmetic expression.\n";
	cout << "\n\tIt evaluates to " << solution << ".\n";
}

//Precondition : Called from main
//Postcondition: Output the converted infix expression into postfix expression
void option2()
{
	Stack expression;
	string infix = "";
	string postFix = "";
	string operatorPrecendence = "^/*+-"; //Trying out the operators
	char choice = 'N';
	int parenthesesCount = 0;
	cout << "\n\t2> Translation of Arithmetic Expression";
	cout << "\n\t" << string(100, char(196));
	do
	{
		postFix = "";
		infix = inputString("\n\tEnter an infix expression: ", true);

		for (int i = 0; i < infix.length() + 1; i++)
		{
			infix[i]; //To see the current character
			//For values or variables
			if ((isdigit(infix[i])) || (isalpha(infix[i])))
			{
				postFix += infix[i];
			}
			else if(infix[i] == '(')
			{
				expression.push(infix[i]);
				parenthesesCount++;
			}
			else if (infix[i] == ')')
			{
				if(parenthesesCount == 0)
				{
					cout << "\n\tInfix expression  : " << infix;
					cout << "\n\tPostfix expression: ERROR: inbalanced parentheses";
					return;
				}
				parenthesesCount--;
				expression.pop();
			}
			else 
			{

				/*while (!expression.isEmpty() && prec(infix[i]) <= prec(expression.top())) 
				{
					postFix += expression.top();
					expression.pop();
				}
				expression.push(infix[i]);*/
			}
		}
		if (parenthesesCount > 0 || parenthesesCount < 0)
		{
			cout << "\n\tInfix expression  : " << infix;
			cout << "\n\tPostfix expression: ERROR: inbalanced parentheses";
			return;
		}
		cout << "\n\tInfix expression  : " << infix;
		cout << "\n\tPostfix expression: " << postFix << '\n';

		choice = inputChar("\n\tContinue a new expression? (Y-yes or N-no) ", static_cast<string>("YN"));

	} while (choice != 'N');
}

//Precondition : Called from main
//Postcondition:
void option3()
{
	cout << "\n\t3> n-Queens Problem";
	int numberOfQueens = 0;
	numberOfQueens = inputInteger("\n\tEnter a number(1...100) of queens: ", 1, 100);
	
	int column = 0;
	column = inputInteger("\n\tEnter the column(1.." + to_string(numberOfQueens) + ") to place the first queen : ", 1, numberOfQueens);
}
