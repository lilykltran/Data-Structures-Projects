//Lily Tran 989558404 CS163 HW2. This file contains the client program, which includes function calls, error messages, and prompting the user.
#include "HW2.h"

int main()
{

	Queue Queue_Object_Pass; //object for getting the boarding pass.
	Queue Queue_Object_Board; //object for boarding the plane.
	Stack Stack_Object; //object for the seats and rows in which passengesr are seated.
	Stack_Node Stack_Node_Object;

	int num_of_rows; //to determine...
	int num_of_seats; //the boarding number

	char ans; 
	char tempName[SIZE];

	cout << "How many rows are there?" << endl;
	cin >> num_of_rows;
	cin.ignore();

	cout << "How many seats total?" << endl;
	cin >> num_of_seats;
	cin.ignore();

	do 
	{
		cout << "Enter a command." << endl;
		cout << "1. Add a passenger. (enqueue)" << endl;
		cout << "2. Display list of passngers in order. (display)" << endl;
		cout << "3. Display the next passenger to board. (peek)" << endl;
		cout << "4. Remove the next passenger to board and put them on the plane. (dequeue and push)" << endl;
		cout << "5. Remove a passenger from the plane. (pop)" << endl;
		cout << "6. Display who is next to leave the plane. (peek)" << endl;
		cout << "7. Quit." << endl;
		
		cin >> ans;
		cin.ignore();

		if (ans == '1')
		{

		int result = 0;

			//do {

			cout << "Enter the passenger's name." << endl;
			cin.get(tempName, SIZE, '\n');
			cin.ignore(100, '\n');
				
			result = Queue_Object_Pass.enqueue(tempName, num_of_seats);	
			cout << "That passenger's boarding number is: " << result << endl; //adds passengers at the end of the list.

			//} while (result <= num_of_seats);
			
		}
		
		if (ans == '2')
		{

			Queue_Object_Pass.display(); //displays all the passengers in the CLL.

		}
		
		if (ans == '3') //display next person in line to board the plane.
		{
			Queue_Object_Pass.peek();

		}


		if (ans == '4')
		{

			char *name = Queue_Object_Pass.dequeue(); //pass in the name that was removed from the line.

			if (name == NULL) //if there was no passenger removed from line to board the plane.
			{
				cerr << "no passenger to add to plane!" << endl;
			}

			else
			{
				Stack_Object.push(name, num_of_seats, num_of_rows); //pushes passenger removed from line to the top of the plane. 
				delete [] name; 
			}

		}

		if (ans == '5') //remove the passenger at the top of the plane.
		{
			int popresult = Stack_Object.pop(num_of_seats, num_of_rows);

			if (popresult)
				cout << "removed passenger at top of the plane." << endl;
			else
				cerr << "No more passengers to remove.";

		}
		
		if (ans == '6')
		{
			Stack_Object.peek(); //displays next passenger to leave the plane. it is always first person in the list.

			
		}


	} while (ans != '7');


	Queue_Object_Pass.~Queue(); //call desctructors.
	Stack_Node_Object.~Stack_Node();
	Stack_Object.~Stack(); 


	return 0;
}
