/* Lily Tran 989558404 CS163 HW3gt
 * This file contains structs, classes, and constant variables
*/ 
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

using namespace std;



const int SIZE = 9;
const int SIZE2 = 60;



struct node 
{
	node();
	node(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount); //constructor that copies the temp data.
	struct event *data; //pointer to struct event.
	node *next;
};



struct event //information included in the event.
{
	event();
	event(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount); //constructor that copies the temp data into event data.
	bool match(char *keyword2); //determines whether or not the keywords match.
	int set_data(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount); //sets the data as the temp variables.
	char name[SIZE2]; //name of event.
	char location[SIZE2]; //location of event.
	int date; //date of the event.
	char time[SIZE]; //time of the event.
	char description[SIZE2]; // description of the event.
	char *keyword[5]; //keywords the event has.
	int count; //how many keywords.
};



class Table
{
	public:

		Table(int size); //constructor
		~Table(); //destructor
		int insert(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char *tempKeyword[], int tempCount); //this function adds an event.
		int retrieve(char *event_to_find, char *name[], int & tempCount); //this function retrieves an event that matches the keyword passed in.
		int remove(int tempDate); //removes events older than a specific date.
		bool display(char *tempKeyword); //displays a specific event and its information depeding on the keyword.
		void display_all(); //this function displays all of the events available. this is recursive.
		void readin(char *filename); //read in function
	
	private:
		node **head; //dynamically allocted array of head pointers.
		node *list_head;
		int hash_table_size; //the size of the table.
		int hash(char *keyword) const; // to design the hash table.
};
