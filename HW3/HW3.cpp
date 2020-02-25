/* Lily Tran 989558404 CS163 Prog 3
 * This file contains the implementation of member functions.
*/

#include "HW3.h"



Table::Table(int size) //constructor
{
	list_head = NULL;
	hash_table_size = size; //make the argument passed in to be the hash table size from private.
	head = new node *[hash_table_size]; //create a new node for head.
	
	for (int i = 0; i < hash_table_size; ++i)
	{
		head[i] = NULL; //set each index to NULL until the max size of the table.
	}
}



Table::~Table() //destructor
{
	for (int i = 0; i < hash_table_size; ++i)
	{
		delete head[i]; //delete head at each index.
		head[i] = NULL;
	}
}


event::event()
{
	name[0] = '\n';
	location[0] = '\n';
	time[0] = '\n';
	description[0] = '\n';

	for(int i = 0; i < 5; ++i)
	{
		
		keyword[i] = NULL;
	}

	date = 0;
}

event::event(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount) //constructor
{
	strcpy(name, tempName); //copies the variable passed in from the user into the event's variables.
	strcpy(location, tempLocation);
	strcpy(time, tempTime);
	date = tempDate;
	strcpy(description, tempDescription);
	count = tempCount;

	for (int i = 0; i < count; ++i)
	{
		keyword[i] = new char[strlen(tempKeyword[i]) +1];

		strcpy(keyword[i], tempKeyword[i]); //copies every keyword into a temporary keyword array.
	}
}



int event::set_data(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount) //copies client variables into struct variables.
{
	int num_keywords = 0;

	strcpy(name, tempName); //copies the variable passed in from the user into the event's variables.
	strcpy(location, tempLocation);
	strcpy(time, tempTime);
	date = tempDate;
	strcpy(description, tempDescription);
	count = tempCount;

	for (int i = 0; i < count; ++i)
	{
		strcpy(keyword[i], tempKeyword[i]); //copies every keyword into a temporary keyword array.
		++num_keywords;
	}
	return num_keywords;
}



node::node() //constructor for node.
{
	data = NULL;
	next = NULL;
}



node::node(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount) //constructor for node.
{
	data = new event(tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, tempCount); //adds all variables into data.
	next = NULL;
}



int Table::insert(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount) //this function adds an event.
{
	node *temp;
	temp = new node(tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, tempCount); //call node function that sets data.
	temp -> next = list_head; //link up to the head.
	list_head = temp; //temp is now the head of the list.
	
	for (int i = 0; i < tempCount; ++i)
	{

		int index = hash(tempKeyword[i]); //because there are multiple keywords, the indexes will change for each keyword.


		if (index == -1) //if there is no index. 
			return 0;

		node *new_node = new node(); //call node function that sets data.
		new_node -> next = head[index]; //link up to the head.
		head[index] = new_node; //temp is now the head of the list.
		new_node -> data = temp -> data;
	}

	return 1;
}




int Table::retrieve(char *event_to_find, char *name[], int &tempCount) //this function retrieves an event that matches the keyword passed in.
{
	int index = hash(event_to_find); //call hash function.
	int counter = 0; //however many keywords.

	node *current;

	if (index == -1) //if there is no list.
		return 0;
	

	if (head[index])
	{
		current = head[index]; //set current equal to head.
		while (current && counter < tempCount) //while there is a list and the amount of keywords deos not exceed the amount there is.
		{
			if(current -> data -> match(event_to_find)) //call match function that compares the keyword to keyword passed in.
			{
				strcpy(name[counter], current -> data -> name);
				++counter; //increment counter.
			}
			current = current -> next; //go to the next node, check its keywords.
		}

	}

	tempCount = counter; //the amount of events found with this keyword. Set it to the argument variable.
	return 0;
}



bool event::match(char *keyword2) //keyword2 is what the user entered in. 
{
	for (int i = 0; i < count; ++i)
	{
		if (strcmp(keyword2, keyword[i]) == 0) 
			return true;
	}
	return false;
}

	

int Table::remove(int tempDate) //removes events before a certain date.
{

	node *current = list_head;
	node *previous;

	if (!list_head)
		return 0;
	
	while (current)
	{
		if (current -> data -> date < tempDate)
		{
			if (previous) //if previous not NULL
			{
				previous -> next = current -> next; //set it equal.
				delete current; //delete this node.
				current = previous -> next; //link up nodes.
			}
		}

		else //if it's not less than the date, traverse through node until it finds one that is.
		{
			previous = current;
			current = current -> next;
		}
	}
	return 0;
}



void Table::display_all() //this function displays all of the events available.
{
	if (!list_head)
		return;

	if (list_head)
	{
		node *current = list_head;
		cout << endl;
		cout << "Events: " << endl;
		cout << endl;

		while (current)
		{
			cout << "Name: " << current -> data -> name << endl;
			cout << "Location: " << current -> data -> location << endl; //display all variables in the struct.
			cout << "Time: " << current -> data -> time << endl;
			cout << "Date: " << current -> data -> date << endl;
			cout << "Description: " << current -> data -> description << endl;

			for (int i = 0; i < current -> data -> count; ++i)
			{
				cout << current -> data -> keyword[i]  << endl; //display every keyword.
			}
			cout << endl;
			current = current -> next; //traverse to the next node to display.
		}
		cout << endl;
	}
}



int Table::hash(char *keyword) const
{

	int length = strlen(keyword);
	int sum = 0;

	if (!keyword)
		return -1;

	for (int i = 0; i < length; ++i)
	{
		sum += keyword[i];
	}

	return sum % hash_table_size;

}



void Table::readin(char *filename)
{

	ifstream read;
	read.open(filename); //connect to file. 
	
	event info; //call struct event

	if (!read) //makes sure connected fo file. 
		return;

	for (int i = 0; i < 5; ++i)
		info.keyword[i] = new char[100]; //allocate new memory for keyword because it's dynamically allocated.

	while(read && !read.eof()) //previous read is successful
	{
		char arr[100];
		char arr2[100];
		read.get(info.name, 100, '|');
		read.ignore(100,'|');

		read.get(info.location, 100, '|');
		read.ignore(100,'|');

		read.get(arr, 100, '|');
		read.ignore(100,'|');
		info.date = atoi(arr); //change date from an int to a char so can read in.
		read.get(info.time, 100, '|');
		read.ignore(100,'|');

		read.get(info.description, 100, '|');
		read.ignore(100,'|');

		for (int i = 0; i < 5; ++i)
		{
			read.get(info.keyword[i], 100, '|');
		}

		read.get(arr2, 100, '|');
		read.ignore(100,'|');
		info.count = atoi(arr2); //change count from int to char to read in.
	}
	read.ignore(100, '|');
	read.close();

	insert(info.name, info.location, info.time, info.date, info.description, info.keyword, info.count); //call insert function.
}
