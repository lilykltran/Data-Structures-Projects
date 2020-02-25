/*Lily Tran 989558404 CS163 HW1
 *This HW1.h file contains constant global variables, structs, my class, and its functions.
 *Program that creates a class called CS_chat that allows the user
 *to add chat rooms, post a message, display messages, 
 *display a specific message, display chat rooms, and remove
 *chat rooms.
*/


#include <iostream>
#include <cctype>
#include <cstring>
#include <ctime>
using namespace std;

const int SIZE = 15;
const int SIZE2 = 100;

struct chat_room
{
	
	chat_room(char*roomName, char* userName, char* Email, char* description); //constructor
	char room_name[SIZE]; //information that each chatroom will have.
	char description[SIZE2];
	char username[SIZE];
	char email[SIZE];
	int set_data(char*roomName, char* userName, char* Email, char* Description);//copies data

};


struct message
{
	char *text; //the data in the nodes.
	int timeStamp;
	//char username[SIZE];	
	//char email[SIZE];

};

struct message_node
{
	message data2; //nodes of struct message.
	message_node *next; //next pointer

};

struct room_node
{

	room_node(char*roomName, char* userName, char* email, char* description);
	int insert_message(char * msg, int timeStamp);	
	chat_room *data; //pointer to struct chat_room.
	room_node *next; //next pointer
	message_node *head; //pointer to struct message_node. This is the LLL of messages.
};

class CS_Chat
{
	public:
		CS_Chat(); //constructor
		~CS_Chat(); //destructor

		int add_room(char*roomName, char* userName, char* Email, char* Description); //adds chat rooms
		//int post_message(char * msg, char *room_name); //posts messages to a specific chat room
		int post_message(char *msg, char *roomName, int timeStamp);
		bool display_messages(char *room_name); //displays messages of a specific chat room
		bool display_keyword_message(char *keyword); //displays messages with a specific word in it.
		int remove(int timeStamp); //removes messages older than a specific time stamp.

	private:
		room_node *head; //pointer to struct room_node. This is the LLL of rooms.
};
