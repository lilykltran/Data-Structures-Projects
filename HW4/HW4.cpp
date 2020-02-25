//Lily Tran. 989558404. CS163 HW4. This file contains the implentation of all of the member functions in structs and class.
#include "HW4.h"

BST::BST() //constructor
{
	root = NULL;
}



BST::~BST() //destructor
{
	destructor(root);	
}



void BST::destructor(node *& root) //deletes the nodes in the BST.
{
	if (!root)
		return;

	destructor(root -> left); //go to the last node in left subtree.
	destructor(root -> right); //go the last node in right subtree.
	
	for (int i = 0; i < 5; ++i)
	{
		delete [] root -> data -> keyword[i]; //delete the keyword first because it is dynamically allocated.
	}
	
	delete root;
}



event::event() //this event constructor sets all the variables of the event to NULL.
{
	name[0] = '\n';
	location[0] = '\n';
	time[0] = '\n';
	description[0] = '\n';

	for(int i = 0; i < 5; ++i) //because there can be up to 5 keywords, we need a for loop.
	{
		keyword[i] = NULL;
	}

	date = 0;
}



event::event(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount) //constructor
{ //this constructor copies variables passed in from the user into the actual variables of the structure.
	strcpy(name, tempName); //copies the variable passed in from the user into the event's variables.
	strcpy(location, tempLocation);
	strcpy(time, tempTime);
	date = tempDate;
	strcpy(description, tempDescription);
	count = tempCount;

	for (int i = 0; i < count; ++i) //because there can be up to 5 keywords, or count, which is how many the user puts in, we need for loop.
	{
		keyword[i] = new char[strlen(tempKeyword[i]) +1]; //because keyword is a pointer, we need to allocate memory for it first.

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
		delete [] keyword[i]; //delete memory for keyword so that inorder successor can override the root's data.
		keyword[i] = new char[strlen(tempKeyword[i]) +1]; //allocate memory for the pointer
		strcpy(keyword[i], tempKeyword[i]); //copies every keyword into a temporary keyword array. 
		++num_keywords; //increment num_keywords to get the number of keywords the user entered.
	}
	return num_keywords; //returns num_keywords, which is the count we will use later.
}



node::node() //constructor for node.
{
	data = NULL; //set everything to NULL.
	left = NULL;
	right = NULL;
}



node::node(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount) //constructor for node.
{
	data = new event(tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, tempCount); //adds all variables into data. call 
	//the set data function.
	left = NULL; //sets the next pointers to NULL.
	right = NULL;
}



int BST::insert(char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount)
//inserts all variables of the struct, organized alphabetically by the event's name.
{
//the wrapper function for insert.
	return insert(root, tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, tempCount); 
}



int BST::insert(node *& root, char *tempName, char *tempLocation, char *tempTime, int tempDate, char *tempDescription, char * tempKeyword[], int tempCount) //this function adds an event.
{
	if (!root) //if there is no event to start with, add a new event.
	{
		root = new node(tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, tempCount); //call node constructor that stores these variables as the data.
		root -> left = NULL; //set next pointers to NULL.
		root -> right = NULL;
		return 1;
	}
	
	if (strcmp(tempName, root -> data -> name) < 0 ) //if the name trying to be stored's value is less than the value of the name already stored
	{
		insert(root -> left, tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, tempCount); //traverse left,
		//because that means that name being stored is a smaller value, and belongs to the left of the tree.
		return 1;
	}
	
	if (strcmp(tempName, root -> data -> name) >= 0 ) //if name being stored's value is greater than value of name already stored
	{
		insert(root -> right, tempName, tempLocation, tempTime, tempDate, tempDescription, tempKeyword, tempCount); //insert in the right.
		return 1;
	}
}



int BST::retrieve(char *event_to_find, char *name) //wrapper function for retrieve function
{
	return retrieve(root, event_to_find, name);
}



int BST::retrieve(node * root, char *event_to_find, char *tempName2) //this function retrieves an event that matches the keyword passed in.
{
	if (!root)
		return 0;

	if(root -> data -> match(event_to_find)) //call match function that compares the keyword to keyword passed in.
	{
		strcpy(tempName2, root -> data -> name); //copy the name that matches into a temporary name pointer.
	}

		retrieve(root -> left, event_to_find, tempName2); //traverse to the left subtree to find the match.
		retrieve(root -> right, event_to_find, tempName2); //traverse to the right subtree to find the match.

	return 0;
}



bool event::match(char *tempName2) //This is the match function for name.
{
		if (strcmp(tempName2, name) == 0) //compares the name passed in to the name already in the tree.
			return true;

	return false;
}




int event::copy(event & info) //copies some node's data into another node's data. this is used for copying the inorder successor 
{
	return set_data(info.name, info.location, info.time, info.date, info.description, info.keyword, info.count); //call the set data function.
}



int BST::remove_name(char *tempName) //wrapper function for remove events with a certain name.
{
	return remove_name(root, tempName);
}



int BST::remove_name(node *& root, char *tempName) //removes an event with a certain name.
{

	if (!root) //if there is no tree, return 0.
		return 0;
	
	if (root -> data -> match(tempName)) //if the root's name matches the name passed in,
	{
		if (!root -> left && !root -> right) //if it is a leaf.
		{	
			delete root; //delete it.
			root = NULL;
		}

		else if (!root -> left) //there is a right child, but no left child.
		{
			node *temp = root -> right; //hold on to that child.
			delete root; //delete the parent.
			root = temp; //make the child the parent.
		}

		else if (!root -> right) //if there is a left child, but no right child.
		{
			node *temp = root -> left; //hold on to that child.
			delete root; //delete the parent.
			root = temp; //make the child the parent (root).
		}
		
		else //if that node to delete has both right and left children.
		{
			node *temp = root -> left; //hold on to the left child.
			node *current = temp; //sent current to that left child.
			node *previous = NULL;
	
			while (current -> right) //while there is a right subtree.
			{
				previous = current; //set previous to current.
				current = current -> right; //traverse to the end of the tree where the inorder successor lies.
			}	
			
			if (!previous) //if there isn't a current -> left.
				root -> left = current -> left; //make root's left link up to current's left, because we are going to delete current.

			else //if previous is not NULL.
			{
				previous -> right = current -> left; //link up that dragged previous pointer to current's left.
			}

			root -> data -> copy(*current -> data); //copy the inorder successor into root node.
			delete current; //delete inorder successor.
		}
	}

	else //if there is no match, traverse until there is.
	{
		remove_name(root -> left, tempName);
		remove_name(root -> right, tempName);
	}

	return 0;
}



bool event::match_keyword(char *tempKeyword2) //to find the keyword matches. called in remove_keyword.
{
	for (int i = 0; i < count; ++i)
	{
		if (strcmp(tempKeyword2, keyword[i]) == 0) //if the keyword passed in by user matches keyword of the struct event.
			return true;
	}

	return false;
}	



int BST::remove_keyword(char *tempKeyword2) //wrapper function that removes events with a certain keyword.
{
	return remove_keyword(root, tempKeyword2);
}



int BST::remove_keyword(node *& root, char *tempKeyword2) //removes events that have matching keywords wtih ones send it by user. same as remove name 
//except for we compare the keywords instead of the event name
{
	if (!root)
		return 0;
	
	if (root -> data -> match_keyword(tempKeyword2)) //call match_keyword function that compares the keywords.
	{
		if (!root -> left && !root -> right) //if it is a leaf.
		{	
			delete root;	
			root = NULL;
		}

		else if (!root -> left) //there is a right child.
		{
			node *temp = root -> right;
			delete root;
			root = temp;
		}

		else if (!root -> right) //if there is a left.
		{
			node *temp = root -> left;
			delete root;
			root = temp;
		}
		
		else
		{
			node *temp = root -> left;
			node *current = temp;
			node *previous = NULL;
	
			while (current -> right) 
			{
				previous = current;
				current = current -> right; //get to the inorder successor.
			}	
			
			if (!previous)
				root -> left = current -> left;

			else
			{
				previous -> right = current -> left;
			}

			root -> data -> copy(*current -> data); //copy the inorder successor into the root node.
			delete current; //delete the inorder successor.
		}

	remove_name(root -> left, tempKeyword2); //search through the whole tree for matching keyword
	remove_name(root -> right, tempKeyword2);

	}
}



void BST::display() //wrapper function to display the entire tree.
{
	display(root);
}



void BST::display(node *root) //this function displays all of the events available.
{

	node *current = root;

	if (!root) //if there is no tree, do nothing.
		return;

	display(root -> left); //call function with root left to display everything on left subtree first.

	cout << endl;
	cout << "Events: " << endl;
	cout << endl;
	cout << "Name: " << current -> data -> name << endl;
	cout << "Location: " << current -> data -> location << endl; //display all variables in the struct.
	cout << "Time: " << current -> data -> time << endl;
	cout << "Date: " << current -> data -> date << endl;
	cout << "Description: " << current -> data -> description << endl;
	

	for (int i = 0; i < current -> data -> count; ++i)
	{
		cout << current -> data -> keyword[i]  << endl; //display every keyword because there can be up to 5.
	}

	cout << endl;
	

	display(root -> right); //then, display everything on right subtree.
}
