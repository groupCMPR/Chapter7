//Names: Alexis Martinez, Angie Campos, Neidy Malaga, & Vivian Huynh
//Date: 10/4/2023
//Description: Chapter 7 Assignments - Stack

#include <iostream> //For cout

//HEADER FILES
#include "input.h" //For input validation
using namespace std;

//PROTOTYPES
int mainMenu();

//Option 1 - 
void option1();

//Option 2 - 
void option2();

//Option 3 - 
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
	cout << "\n\tCMPR131 Chapter 7: Stacks by Group 5 () 10/12/2023";
	cout << "\n\t" << string(100, char(205));
	cout << "\n\t\t1>";
	cout << "\n\t\t2>";
	cout << "\n\t\t3>";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\t0. Exit";
	cout << "\n\t" << string(100, char(205));

	return inputInteger("\n\t\tOption: ", 0, 3);
}
