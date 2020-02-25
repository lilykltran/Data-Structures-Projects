#include "HW1.h"
//Lily Tran. 989558404. CS163 HW1. 
//This HW1.cpp file contains all of the member functions in my classes and structs.

CS_Chat::CS_Chat() //constructer
{
	head = NULL;
}

CS_Chat::~CS_Chat() //destructer
{

	room_node *current_room = head; 
	message_node *current_message = NULL;

	if (!head) //if list is empty return nothing. 
		return;

	while (current_room) //while node we are at is not NULL
	{
		current_message = current_room -> head;
	
		while (current_message)
		{
			delete [] current_message -> data2.text; //deallocate memory of the data in the node.
			message_node *temp = current_message -> next; //create a temporary pointer that is current -> next so that when we delete current it doesn't delete whole thing.
			delete current_message; //delete current, which is the node before.
			current_message = temp; //now make temp, which is the current -> next, the first node. (current).
			current_message = NULL; //set current to NULL. 
		}
		
		delete [] current_room -> data;
		room_node *temp2 = current_room -> next;
		delete current_room;
		current_room = temp2;
		current_room = NULL;
		
	}
}

chat_room::chat_room(char*roomName, char* userName, char* Email, char* Description) //constructor of struct chat_room that 
//copies the variables passed in by the client program, and copies it into the variables of chat_room.
{

	strcpy(room_name, roomName); //strcpy(struct variable, client variable)
	strcpy(username, userName);
	strcpy(email, Email);
	strcpy(description, Description);


}

int chat_room::set_data(char*roomName, char* userName, char* Email, char* Description) //copies the variables passed in by 
//client program, and copies it into the variables of structure chat_room.
{

	strcpy(room_name, roomName); //strcpy(struct variable, client variable)
	strcpy(username, userName);
	strcpy(email, Email);
	strcpy(description, Description);

}

room_node::room_node(char*roomName, char* userName, char* Email, char* Description) //constructor or struct room_node
//that creates a new node for data, a pointer to struct chat_room, and creates a new node for all variables in the chat_room struct, 
//then copies variables from client program into chat_room struct.
{

	data = new chat_room(roomName, userName, Email, Description);

}
int CS_Chat::add_room(char*roomName, char* userName, char* Email, char* Description)
{
	
	room_node * current = head;

	if (!head) //if the room list is empty
	{
		head = new room_node(roomName, userName, Email, Description); //call fucntion that creates new node that calls function 
//that copies client variables into struct variables.
		head -> next = NULL; //set the next node equal to NULL.
	}

	else //if the list is not empty,
	{
		
		while (current -> next)
		{
			current = current -> next; //add at the end of the room list.
		}

		current -> next = new room_node(roomName, userName, Email, Description); ///call function that creates new node that calls function
//that copies client variables into struct variables.
		current -> next -> next = NULL; //set the next node to NULL.
	}
}
	
int CS_Chat::post_message(char *msg, char *tempRoom, int timeStamp) 
{

	room_node *current = head;

	if (!head)
	{
		cout << "No chat room to post message to." << endl;
		return 0;
	}

	while (current)
	{
		if (strcmp(tempRoom, current->data->room_name) == 0) //if room name of the struct matches the one user wants,
		{
			current -> insert_message(msg, timeStamp); //insert the message into its data. calls function insert_message.
			return 1;
		}
	current = current -> next; //if it's not the match, go to next room.
	}
}

bool CS_Chat::display_messages(char *room_name)
{

	room_node *current_room = head; //pointer to first msg of first room.
	message_node *current_message = NULL;
	
	while (current_room)
	{
		if (strcmp(room_name, current_room -> data -> room_name) == 0) //if the room name of the list matches room name user wants.
		{
			current_message = current_room -> head; //link up first message to first room.

			while (current_message)
			{
				cout << "The messages of this room are: " << current_message -> data2.text << endl; //display messages.
				current_message = current_message -> next; //go to next message.
			}
			return true;
		}	
		else
		{
			current_room = current_room -> next; //go to next room if it's not the one the user wants.
		}
	}
}

bool CS_Chat::display_keyword_message(char *keyword)
{

	room_node *current_room = head; //pointer to first msg of first room.
	message_node *current_message = head -> head;

	cout << "Messages with this keyword are: " << endl;

	while (current_room) //while node we are at is not NULL.
	{
		current_message = current_room -> head;
		
		while (current_message)
		{
			if (strstr(current_message -> data2.text, keyword) != NULL) //if data2 contains the keyword
			{
				cout << current_message -> data2.text << endl; //display that node's contents.
			}
			current_message = current_message -> next; //traverse to the next message if it doesn't contain the keyword.
		}
		current_room = current_room -> next; //traverse to the next room.
	}
}

int CS_Chat::remove(int timeStamp) //removes messages before a certain time stamp.
{
	room_node *current_room = head; //pointer to first msg of first room.
	message_node *current_message = head -> head;
	message_node *temp;
	message_node *previous = NULL; //previous pointer to current_message.

	while (current_room) //while node we are at is not NULL.
	{
		previous = NULL;
		current_message = current_room -> head; //match up first message to first room.
		
		while (current_message)
		{
			if (current_message -> data2.timeStamp < timeStamp) //if the time stamp of the message is less than the time stamp user sent in.
			{
				if (previous) //if previous not NULL
				{
					previous -> next = current_message -> next; //set it equal.
					delete current_message; //delete this node.
					current_message = previous -> next; //link up nodes.
				}
					
				else //previous is NULL
				{
					current_room -> head = current_message -> next;
					delete current_message;
					current_message = current_room -> head;
				}
			}

			else //if it's not less than time stamp, traverse through node.
			{
				previous = current_message;
				current_message = current_message -> next;
			}
		}
		current_room = current_room -> next;
	}
}

int room_node::insert_message(char * msg, int timeStamp) //function that will insert messages into message_node.
{

	message_node *temp; //temporary pointer to message_node

	temp = new message_node; //allocate new node.	
	temp -> data2.text = new char[strlen(msg) +1]; //data2 for insert message. size of msg plus 1 for NULL.
	strcpy(temp -> data2.text, msg); //copy the message the user wanted into data2

	temp -> data2.timeStamp = timeStamp; //copy timeStamp user put in in the data2.
	temp -> next = NULL; //set the next pointer to NULL. this is if it's only one in the list.

	if (!head) //if the list is empty
	{
		head = temp; //add it as head.
	}

	else  //if the list is not empty.
	{
		temp -> next = head;
		head = temp;
	}
	
}
