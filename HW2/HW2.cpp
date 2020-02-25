// Lily Tran 989558404 CS163 HW2. This file contains the implementation of the member functions.
#include "HW2.h"

Queue::Queue() //constructor
{
	rear = NULL;
	boarding_num = 0;

}



Queue::~Queue() //destructor
{

	Queue_Node *head = rear -> next; //hold on to first node
	rear -> next = NULL; //make CLL a LLL

	while (head)
	{
		Queue_Node *current = head;
		head = head -> next;
		delete current; //delete list.
	}
	//goes until list is NULL.
}



Stack::Stack() //constructor
{

	head = NULL;
	top_index = 0;

}



Stack::~Stack() //destructor to delete the rows.
{
	Stack_Node *head;

	if (!head)
		return;
	
	while (head)
	{
		Stack_Node *current = head;
		head = head -> next;
		delete current;
	}
}

Stack_Node::~Stack_Node() //destructor to delete the seats.
{

	if (!data)
		return;

	delete [] data; //delete the new data at each index until full.

	data = NULL; //set data to NULL.
}



int Queue::enqueue(char *name, int num_of_seats) //adds passengers at the end of the list.
{
	Queue_Node *temp;
	

		if (!rear) //if no previous node.
		{
			rear = new Queue_Node; //create new node.
			rear -> data = new char[strlen(name) +1]; //of size name that's going to be put in.
			strcpy(rear -> data, name); //copy name passed in into the data.
			rear -> next = rear; //point next to point to itself.
			++boarding_num; //boarding number is now 1.
			return boarding_num;
		}
		

		if (rear == rear -> next) //one passenger in list.
		{
			temp = new Queue_Node; //new node.
			rear -> next = temp; 
			temp -> next = rear;
			temp -> data = new char[strlen(name) + 1];
			strcpy(temp -> data, name); //copy name into data.
			rear = temp; //new end of list is now temp. adding passengers at the end (rear).
			++boarding_num; //boarding number is 2.
			return boarding_num;
		}
		
	
		else //if there are multiple passengers.
		{
			temp = new Queue_Node;
			temp -> next = rear -> next; //have temp be the node before th elast.
			rear -> next = temp;
			temp -> data = new char[strlen(name) +1];
			strcpy(temp -> data, name); //copy name into temp's data.
			rear = rear -> next; //it is now the new rear.
			++boarding_num; //boarding number is incremented after each new passenger is added.
		}

	return boarding_num;
}



char* Queue::dequeue() //removes passengers starting at the rear.
{
	Queue_Node *temp;
	char *name;

	if (!rear) //empty;
		return NULL;

	if (rear == rear -> next) //if 1 item
	{
		
		name = new char[strlen(rear -> data) +1]; //hold on to the name that we are going to delete.
		strcpy(name, rear -> data);  //copy it into name before we delete it.
		delete rear;
		rear =  NULL;	
		return name; //return name to be passed into Stack's push.
	}

	else
	{
		name = new char[strlen(rear -> data) +1];
		strcpy(name, rear -> data);
		temp = rear -> next -> next;
		delete rear -> next;
		rear -> next = temp; //the second item is now the first.
		return name; //return name to be passed into Stack's push.
	}
}



int Queue::peek() //grabs first data in the list without modifying the CLL.
{

	if (!rear)

		return 0;

	if (rear == rear -> next)
		cout << "The next passenger to board is: " << rear -> data << endl;
	else //more than 1 item.
	{
		cout << "The next passenger to board is: " << rear -> next -> data << endl; //displaying the head in a CLL.
	
	}

}



int Queue::display(Queue_Node *head, Queue_Node *rear) //wrapper function for display.
{

	if (!rear)
		return 0;

	cout << head -> data << endl;

	if (head == rear)
		return 0;

	return display(head -> next, rear); //display each node.

}



int Queue::display() //displays all the passengers in the CLL.
{

	display(rear -> next, rear);

}



int Stack::display_all(int num_of_seats, int num_of_rows)  //displays all of the rows and seats.
{

	int max = num_of_seats/num_of_rows; //max number of seats in a row.

	if (!head)
		return 0;
	
	else	

	while (head)
	{
		for (int i = 0; i < top_index; ++i)
			cout << head -> data[i] << endl;

		head = head -> next; //traverse to the next node when the previous node's index is the top. 
	}


}



int Stack::peek() //pulls first data in the LLL of arrays without modiyfing it.
{
	if (!head)
		return 0;
	
	else
	{
		cout << "The passenger next to board is: " << head -> data[0] << endl; //always going to display the first passenger, which is index 0.
	}
	

}



int Stack::push(char *name, int num_of_seats, int num_of_rows) //pushes passenger to the top of the plane. 
{
	int max = num_of_seats/num_of_rows;
	Stack_Node *temp;

	if (!head)
	{
		head = new Stack_Node; //create new node to ad to.
		head -> data = new char*[max]; //make the number of seats that can be in each row.
		head -> next = NULL; //the next row is NULL.
	}
	
	else if (top_index == max) //if the index we are at is the max, create a new node.
	{
		top_index = 0;
		temp = new Stack_Node; //new row.
		temp -> data = new char*[max]; //new row with seats.
		temp -> next = head; //now there are 2 rows.
		head = temp;
	}

	head -> data[top_index] = new char[strlen(name) +1]; //copy the names passed in from dequeue.
	strcpy(head -> data[top_index], name);
	++top_index; //pass names into each index of the array.
	return 1;
}



int Stack::pop(int num_of_seats, int num_of_rows) //removes passengers from the top of the plane.
{
	int max = num_of_seats/num_of_rows; //max number of seats in each row.

	Stack_Node *temp;

	if (!head)
		return 0;
	
	if (top_index == 0) //when there is no passengers in the seats.
	{
		temp = head -> next; //hold on to the next rows.
		delete [] head -> data; //delete the set.
		delete head; //delete the row.
		top_index = max -1; //make the new top index size max.
		head = temp; //make the second row the first row.
	}

	else
	{
		--top_index; //decrement top index if top index is not 0.

	}
}
