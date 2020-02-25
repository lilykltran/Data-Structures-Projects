#include "HW1.h"
//Lily Tran. 989558404. CS163 HW1.
//This main.cpp file contains my menu, prompting the user for information, objects, and temporary variables.


int main()
{

//	chat_room info;
	CS_Chat CS_Chat_Object; //object of class CS_Chat
	message_node message_node_object; //object of struct message_node
	
	char ans; //options for menu.

	//temporary variables for struct chat_room that is passed in as arguments for member functions.
	int timeStamp; //is struct variable timestamp
	char roomName[SIZE]; //room_name
	char userName[SIZE]; //username
	char Email[SIZE]; //email
	char Description[SIZE2]; //description

	char tempRoom[SIZE]; //a temporary variable of the title of a chat room that the user requests to be found. Is then passed in as argument.
	char tempMessage[SIZE2];//temp variable of the message the user wants to add into a chat room. passed in as argument in member functions.
	int tempTime;
	char keyword[SIZE]; //keyword that user requests to be searched.

	do {

	//menu:
		cout << "Enter a command." << endl;
		cout << "1. Add chat room." << endl;
		cout << "2. Post a message to a chat room." << endl;
		cout << "3. Display all messages from a particular chat room." << endl;
		cout << "4. Display all messages with a particular keyword." << endl;
		cout << "5. Delete information older than a timestamp." << endl;
		cout << "6. Quit." << endl;

		cin >> ans;
		cin.ignore();


			if (ans == '1')
			{
				{
			//Prompt user for information in client program.
					cout << "What is the chat room name?" << endl;
					cin.get(roomName, SIZE, '\n'); //store the room name into this temporary variable.
					cin.ignore(100, '\n');
				
					cout << "Enter a username." << endl;
					cin.get(userName, SIZE, '\n'); //store username into this temp variable.
					cin.ignore(100, '\n'); 
			
					cout << "Enter an email." << endl;
					cin.get(Email, SIZE, '\n');
					cin.ignore(100, '\n');

					cout << "Enter a description for this chat room." << endl;
					cin.get(Description, SIZE2, '\n');
					cin.ignore(100, '\n');
				
				}

				CS_Chat_Object.add_room(roomName, userName, Email, Description); //function call.
			}
	
			if (ans == '2') //post message to chat room
			{
				cout << "Which chat room would you like to post a message to?" << endl; //to search for that chat room.
				cin.get(tempRoom, 100, '\n');
				cin.ignore(100, '\n');
		
				cout << "Type in your message." << endl;
				cin.get(tempMessage, SIZE2, '\n');
				cin.ignore(100, '\n');

				cout << "Enter its timestamp. (e.g; 9:54 a.m. is 954, 2:00 p.m. is 1400)" << endl;
				cin >> timeStamp;
				cin.ignore();
			
				CS_Chat_Object.post_message(tempMessage, tempRoom, timeStamp);
			}
		
			if (ans == '3') //display message of a chatroom.
			{
				cout << "Which chat room would you like to see the messages of?" << endl;
				cin.get(tempRoom, 100, '\n');
				cin.ignore(100, '\n');

				CS_Chat_Object.display_messages(tempRoom);
			}
	
			if (ans == '4') //display message with the keyword.
			{
				cout << "Enter a keyword to be searched." << endl;
				cin.get(keyword, 100, '\n');
				cin.ignore(100, '\n');
			
				CS_Chat_Object.display_keyword_message(keyword);
			}

			if (ans == '5') //delete messages before a time.
			{
				cout << "Enter a timestamp." << endl;;
				cin >> tempTime;
				cin.ignore();
				
				CS_Chat_Object.remove(tempTime);
			}
	
	}while (ans != '6'); //user wants to quit-end loop.


	
	CS_Chat_Object.~CS_Chat(); //destructer

	return 0;
}
