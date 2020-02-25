/*Lily Tran 989558404 CS163 HW4. This file is the header file,
 *containing structs and classes.
*/

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

const int SIZE = 60;
const int SIZE2 = 7;

struct node
{
	node(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount); //constructor
	node();
	struct event *data; //call the event struct.
	node *left;
	node *right;
};



struct event //the event variables.
{
	event();
	event(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount); //constructor
	int copy(event & info);
	int set_data(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount); //copies client variables into struct variables.
	bool match(char *tempName); //keyword2 is what the user entered in. 
	bool match_keyword(char *tempKeyword2);
	char name[SIZE];
	char location[SIZE];
	char time[SIZE2];
	int date;
	char description[SIZE];
	char *keyword[5];
	int count;
};



class BST
{
	public:
		BST(); //constructor
		~BST(); //destructor
		int insert(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount);
		int retrieve(char *event_to_find, char *tempName2); //this function retrieves an event that matches the keyword passed in.
		int remove_name(char *tempName); //remove a certain event depending on its name.
		int remove_keyword(char *tempKeyword2); //remove a certain event depending on its keyword.
		void display(); //display events in alphabetical order.
		void readin(char *filename);

	private:
		//contains private recursive functions.
		node *root;
		int insert(node *& root, char *tempName, char *tempLocation,
			char *tempTime, int tempDate, char *tempDescription, char *tempKeyword[], int tempCount);

		int retrieve(node *root, char *event_to_find, char *tempName2);
		int remove_name(node *& root, char *tempName);
		int remove_keyword(node *& root, char *tempKeyword2);
		void display(node * root);
		void destructor(node *& root); 
};
