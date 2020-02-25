/* Lily Tran 989558404 CS163 Prog 3
 * This file is the client program, where prompting, error messages, and calling functions occur.
*/

#include "HW3.h"


int main()
{
	char tempName[SIZE2];
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
	int size = 100;
	
	Table Table_Object(size);


	char filename[] = "events.txt";
	Table_Object.readin(filename); //call read in function.

	do 
	{
		cout << "Enter a command." << endl;
		cout << endl;
		cout << "1. Insert a new event. (insert)" << endl;
		cout << endl;
		cout << "2. Display all events with a keyword. (retrieve & display)" << endl;
		cout << endl;
		cout << "3. Remove events older than a date. (remove)" << endl;
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
			

			Table_Object.insert(tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, count); //insert new event and its information.
		}


		if (ans == '2')
		{
			cout << endl;
			cout << "Enter a keyword you want to be searched." << endl;
			cin.get(tempKeyword2, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			int num_found = 5;

			Table_Object.retrieve(tempKeyword2, tempKeyword, num_found);

			cout << endl;
			cout << "Events with this keyword: " << endl;
			cout << endl;
	
			for (int i = 0; i < num_found; ++i)
			{
				cout << tempKeyword[i] << endl;
			}

		cout << endl;
		}


		if (ans == '3')
		{
			cout << endl;
			cout << "Enter a date. (e.g; 052117)." << endl;
			cin >> tempDate;
			cin.ignore();
			cout << endl;

			Table_Object.remove(tempDate);
		}
		
		
		if (ans == '4')
		{
			cout << endl;
			Table_Object.display_all();
			cout << endl;
		}
	

	} while (ans != '5');



	return 0;
}
