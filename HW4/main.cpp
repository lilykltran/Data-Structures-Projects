//Lily Tran. 989558404. CS163 Prog 4. This file contains prompting, error messages, and interactions with the user
//fucntion calls, temp variables. This is the client program.

#include "HW4.h"

int main()
{
	char tempName[SIZE2];
	char tempName2[SIZE2];
	char tempLocation[SIZE2];
	int tempDate;
	char tempTime[SIZE];
	char tempDescription[SIZE2];
	char *tempKeyword[5];
	char tempKeyword2[SIZE2];

	for (int i = 0; i < 5; ++i)
	{
		tempKeyword[i] = new char[SIZE2];

	}


	char ans;
	
	BST BST_Object;


	do 
	{
		cout << "Enter a command." << endl;
		cout << endl;
		cout << "1. Insert a new event. (insert)" << endl;
		cout << endl;
		cout << "2. Retrieve an event with a certain name. (retrieve & display)" << endl;
		cout << endl;
		cout << "3. Remove events with a cetain name. (remove_name)" << endl;
		cout << endl;
		cout << "4. Display all events. (display all)" << endl;
		cout << endl;
		cout << "5. Quit." << endl;
		cout << endl;
		
		cin >> ans;
		cin.ignore();


		if (ans == '1')
		{
			cout << "What is the event name?" << endl;
			cin.get(tempName, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;
	
			cout << "Where is the event located?" << endl;
			cin.get(tempLocation, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			cout << "What time does the event start? (e.g; 2:30 pm as 1430)" << endl;
			cin.get(tempTime, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			cout << "Enter in the date. (e.g; May 20 2017 as 05202017)" << endl;
			cin >> tempDate;
			cin.ignore();
			cout << endl;

			cout << "Enter a brief description for the event." << endl;
			cin.get(tempDescription, SIZE2, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			int count = 0;

			do {
				cout << endl;
				cout << "Enter a keyword for this event. Enter q to stop entering more keywords." << endl;
				cin.get(tempKeyword[count], SIZE, '\n');
				cin.ignore(100, '\n');
				cout << endl;
				++count;
		
			} while (count <= 4 && strcmp(tempKeyword[count -1], "q") != 0);
			

			BST_Object.insert(tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, count); //insert new event and its information.
		}


		if (ans == '2')
		{
			cout << endl;
			cout << "Enter a name you want to be searched." << endl;
			cin.get(tempName2, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			BST_Object.retrieve(tempName2, tempName);

			cout << endl;
			cout << "Event with this name: " << endl;
			cout << endl;

			cout << tempName << endl;

		cout << endl;

		}


		if (ans == '3')
		{
			cout << endl;
			cout << "Enter the event name to remove. (e.g; Portland Rose Festival)." << endl;
			cin.get(tempName, SIZE, '\n');
			cin.ignore();
			cout << endl;

			BST_Object.remove_name(tempName);
		}
		

		if (ans == '4')
		{
			cout << endl;
			BST_Object.display();
			cout << endl;
		}
	

	} while (ans != '5');

	return 0;
}

