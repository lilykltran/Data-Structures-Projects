/* Lily Tran. 989558404. CS163 Prog 5. This file contains prompting the user,
 * error messages, function calls, and temporary variables.
*/

#include "HW5.h"

int main()
{

	int num_vertices; //size of the graph.
	int ans;
	
	char vertexName[SIZE]; //temporary for vertex_name
	char edgeName[SIZE]; //temporary for edge_name
	int edgeLength; //temporary for edge_length
	char edgeInfo[SIZE]; //temporary for edge_info

	char vertex1[SIZE]; //first vertex user wants to connect
	char vertex2[SIZE]; //second vertex the user wants to connect the first vertex to.

	cout << "How many vertices are there?" << endl;
	cin >> num_vertices;
	cin.ignore();

	graph graph_object(num_vertices); //call the class.

	do{

		cout << "1. insert a trailhead. (insert_vertex)." << endl;
		cout << endl;
		cout << "2. insert an trail. (insert_edge)." << endl;
		cout << endl;
		cout << "3. display the connecting trailheads to a trailhead. (display_connecting)." << endl;
		cout << endl;
		cout << "4. display paths that can be taken. (display_path)." << endl; 	
		cout << endl;
		cout << "5. QUIT." << endl;
		cout << endl;

		cin >> ans;
		cin.ignore();

		if (ans == 1) 
		{
			cout << "What is the trailhead's name?" << endl;
			cin.get(vertexName, SIZE, '\n');
			cin.ignore(100, '\n');

			graph_object.insert_vertex(vertexName);
		}


		else if (ans == 2)
		{
			cout << endl;
			cout << "What is the first vertex you want to connect?" << endl;
			cin.get(vertex1, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			cout << "What is the second vertex you want to connect to the first?" << endl;
			cin.get(vertex2, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;
			
			cout << "What is that trail's name?" << endl;
			cin.get(edgeName, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;
	
			cout << "What is its length in miles? (e.g; 2.5)" << endl;
			cin >> edgeLength;
			cin.ignore();
			cout << endl;

			cout << "Describe the trail. (e.g; dog friendly, good for running, etc)." << endl;
			cin.get(edgeInfo, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			graph_object.insert_edge(vertex1, vertex2, edgeLength, edgeName, edgeInfo);
		}


		else if (ans == 3)
		{
			cout << endl;
			cout << "Which trailhead?" << endl;
			cin.get(vertexName, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			graph_object.display_connecting(vertexName);
		}
			
		else if (ans == 4)
		{
			cout << endl;
			cout << "Which trailhead?" << endl;
			cin.get(vertexName, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			graph_object.display_path(vertexName);
		}


	} while (ans != 5);

	return 0;
}
