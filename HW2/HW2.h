/* Lily Tran 989558404 CS163 HW2. This file contains classes and structs.
 * Program that creates a LLL of arrays and CLL.
 * LLL of arrays represents the rows and seats of the flight. The lists are the seats and the array is the rows. 
 * CLL represents the passengers and who's next in line.
*/

const int SIZE = 15;


#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;



struct Queue_Node //node structure for Queue CLL
{
	Queue_Node *next;
	char *data;
};


struct Stack_Node //node structure for Stack LLL of Arrays.
{
	~Stack_Node();
	Stack_Node *next;
	char **data;
};


class Queue //gets boarding number and boards passengers according to their boarding number.
{
	public:
		Queue(); //constructor
		~Queue(); //destructor
		int enqueue(char *name, int num_of_seats); //adds passengers at the rear.
		char* dequeue(); //removes passengers starting at the rear.
		int peek(); 
		int display(); //displays all the passengers in the CLL.
		
	private:
		int display(Queue_Node *head, Queue_Node *rear);
		char name[SIZE]; //Name of the passenger.
		int seat_num; //the seat number of the passenger.
		int boarding_num; //the boarding number of the passenger. 
		Queue_Node *rear; //CLL of passengers.
		
};


class Stack //represents passengers in each row
{
	public:
		Stack(); //constructor
		~Stack(); //destructor
		int display_all(int num_of_seats, int num_of_rows);
		int peek();
		int push(char *name, int num_of_seats, int num_of_rows); //pushes passengers into each row
		int pop(int num_of_seats, int num_of_rows); //pulls passengesr out. 

	private:
		Stack_Node *head; //LLL of Arrays of rows.
		int top_index; //index of the array.
};
