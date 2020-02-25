/* Lily Tran. 989558404. CS163 Prog 5. This file contains the implementation 
 * of all of the member functions.
*/

#include "HW5.h"

graph::graph(int size) //allocate the adjacency list and set each head pointer to NULL
{
	num_vertices = size; //set size to the number of vertices passed in by user.
	vertices = new vertex*[num_vertices]; //allocate memory for the adjacency list.
	
	for (int i =0; i < num_vertices; ++i) //for loop because array. up to the size it can be, which is the number of 
	//vertices passed in by user.
	{
		vertices[i] = NULL;
	}
}



graph::~graph() //destructor
{

	for (int i = 0; i < num_vertices; ++i) //up until the size of the graph.
	{
		if (vertices[i] != NULL) //if it's null, there is no list to delete, so we need this condition.
		{
			node *current = vertices[i] -> head; //set urrent to the first index.

			while (current) //while current is not NULL.
			{
				node *temp = current -> next; //hold on to the list.
				delete current; //delete the head.
				current = temp; //set head to temp.
			}
		
		delete vertices[i]; //delete that index.

		}
	}

	delete [] vertices; //delete the entire array.
}



vertex::vertex() //constructor for vertex.
{
	head = NULL; //set head to NULL.
	vertex_name[0] = '\0'; //set name to NULL.

}	



node::~node() //destructor for node.
{
	delete data; //dynamically allocated, so need to delete.
}



int graph::insert_vertex(char *vertexName) //insert a vertex called vertexName that is the trailhead.
{
	int i;

	for (i = 0; i < num_vertices; ++i)	
	{
		if (vertices[i] == NULL) //if this index of the array is empty, stay at that index so data can be added.
			break;
	}

	if (i >= num_vertices) //if we never found an open slot and we've reached num_vertices, the array is full, so do nothing.
		return 0;

	vertices[i] = new vertex; //allocate memory at that index that is empty.
	strcpy(vertices[i] -> vertex_name, vertexName); //copy the name passed in by user into the struct's name.
	return 1;
}



int graph::insert_edge(char *vertex1, char *vertex2, int edgeLength, char *edgeName, char *edgeInfo) //insert a trail by connecting two trailheads.
{
	vertex *temp1; //pointer to vertex to store the first vertex's name.
	vertex *temp2; //ponter to vertex to store the second vertex's name.

	temp1 = vertex_match(vertex1); //call vertex_match function to check if the vertex we have  matches the name passed in.
	temp2 = vertex_match(vertex2);

	if (temp1 == NULL || temp2 == NULL) //if we do not find a match, error.
	{
		return 0;
	}

	node * edge1 = new node; //allocate memory for first edge, which is the same as second, but pointing a different direction.
	node * edge2 = new node; //the second edge.
	
	edge1 -> data = new edge;
	edge2 -> data = new edge;
	
	edge1 -> adjacent = temp2; //point the first edge to the second vertex.
	edge2 -> adjacent = temp1; //point the second edge to the first vertex. Now these vertexes point to each other.

	edge1 -> next = temp1 -> head; //point edge to the head of the list. this is connecting it up.
	temp1 -> head = edge1;

	edge2 -> next = temp2 -> head;
	temp2 -> head = edge2;

	strcpy(edge1 -> data -> edge_name, edgeName); //copy the name passed in to the struct's name.
	strcpy(edge2 -> data -> edge_name, edgeName); //doing the same for edge1 and edge2 because it is actually the same edge, it just has different 
																         //directions.
	edge1 -> data -> edge_length = edgeLength; //copy the length passed in to the struct's length.
	edge2 -> data -> edge_length = edgeLength;

	strcpy(edge1 -> data -> edge_info, edgeInfo); //copy the info passed in to the struct's length. 
	strcpy(edge2 -> data -> edge_info, edgeInfo);

	return 1;
}



vertex* graph::vertex_match(char *vertexName) //this function checks to see if the trailheads passed in matches the trailhead in the array.
{
	for (int i = 0; i < num_vertices; ++i)
	{
		if (vertices[i] != NULL) //if the index we are at is not null
		{
			if (strcmp(vertices[i] -> vertex_name, vertexName) == 0) //compare vertex name passed in with vertex name in list.
				return vertices[i]; //return that vertex.
		}
	}

	return NULL; //if there is no match, just return NULL.
}



int graph::display_connecting(char *vertexName) //displays connecting trailheads to a trailhead.
{
	cout << "trails available from this trailhead: " << endl;
	cout << endl;

	vertex *result = vertex_match(vertexName); //call match function with name passed in by user.

	if (result) //if the match succeeded,
	{
		node *current = result -> head; //set current to that vertex.
		while (current) 
		{
			cout << "Trailhead name: " << current -> adjacent -> vertex_name << endl; //display the adjacents that were stored in that node.
			current = current -> next; //traverse
		}
	}

	cout << endl;
	return 0;
}



int graph::display_path(char *vertexName) //displays the connecting trails of a specific trailhead.
{
	cout << endl;
	cout << "Paths connected to this trailhead: " << endl;
	cout << endl;

	vertex *result = vertex_match(vertexName); //call match function with vertex name passed in.

	if (result) //if there was a match.
	{
		node *current = result -> head; //set a current pointer equal to that vertex.

		while (current)
		{
			cout << "Trail name: " <<  current -> data -> edge_name << endl; //display all of that edge's data.
			cout << "Trail length in miles: " << current -> data -> edge_length << endl;
			cout << "Trail description: " << current -> data -> edge_info << endl;
			current = current -> next;
		}
	}
	
	cout << endl;
	return 0;
}
