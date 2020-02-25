/* Lily Tran. 989558404. CS163 Prog 5. This Program is the header file and contains the prototypes
 * of the functions.
 * This file also contains the structs and class of the program.
*/

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int SIZE = 30;

struct node 
{
	~node();
	struct vertex *adjacent;
	node *next;
	struct edge *data;
};



struct edge
{
	int edge_length; //the length of trail from one vertext to the next.
	char edge_name[SIZE]; //the name of the trailhead.
	char edge_info[SIZE]; //whether it is dog friendly, good for walking, running, etc...
};



struct vertex
{
	vertex();
	char vertex_name[SIZE];
	node *head;
};
	


class graph
{
	public:
		graph(int size);
		~graph();
		int insert_vertex(char *vertexName);
		int insert_edge(char *vertex1, char *vertex2, int edgeLength, char *edgeName, char *edgeInfo);
		int display_path(char *vertexName);
		int display_connecting(char *vertexName);
		vertex * vertex_match(char *vertexName);

	private:
		vertex ** vertices; //adjacency list
		int num_vertices; //number of vertices specificed by the user in the client program.
};
