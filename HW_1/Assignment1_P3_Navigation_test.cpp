/*
Consider the problem of finding the shortest path between two points on a plane that has convex polygonal obstacles.
This is an idealization of the problem that a robot has to solve to navigate in a crowded environment.
he vertices of the graph are the vertices of the polygons and the starting and goal positions.
The shortest path from one polygon vertex to any other in the scene must consist of straight-line segments joining
some of the vertices of the polygons.
You are given a file representing a graph. The vertices of the graph are the vertices of the polygons and the starting and goal positions.
The edges of the graph are all the above pairs of vertices that can be connected by a straight line without going through an obstacle.

File format:
Line 1:
two integers m, n (tab separated) representing the numer of vertices and the number of edges.
Lines 2 to m+1 (list of vertices):
each line has 3 numbers i, x, y (tab separated) : i is an integer, the vertex id; x, y are real numbers, the 'x' and 'y' coordinates of the vertex .
Lines m+2 to m+n+1 (list of edges):
each line has two integers (tab separated) representing the id's of the two nodes connected by the edge.
Example: Here is the file for a graph with 6 vertices and 9 edges
					6	9
					0	0.0	0.0
					1	76.75792122307887	162.26001485048116
					2	11.935677016534685	100.82187428764182
					3	58.69782922720505	14.222944063582222
					4	98.64308647185301	57.25001252255944
					5	100.0	200.0
					0	2
					0	3
					1	2
					1	4
					1	5
					2	3
					2	5
					3	4
					4	5
*/

#include <iostream>   //cin,cout
#include <fstream>   //files
#include <queue>     
#include <vector>
#include <stack>
#include <map>
#include <iomanip>


using namespace std;

struct nodeType    //structure of each node in the tree
{
	int state;          //the index of the vertex
	int parent;         //the state of the parent node
	double costG;          //g(n), cost from start to present
	double costH;          //h(n), estimated cost by heuristic from present to goal
						//overload the < operator so we can use it for the priority queue
	friend bool operator<(nodeType x, nodeType y)
	{
		return x.costG + x.costH > y.costG + y.costH;
	};
};

struct navigationGraph
{
	int size; //number of vertices
	double** adjM;  //adjacency matrix 
	vector<double> xloc;
	vector<double> yloc;
};


bool readGraphFromFile(string filename, navigationGraph& g1);  //given a file, populate the graph
void printNode(nodeType curr); //print node information


//given a current node and a set of explored nodes (given as a map), return the path from curr to the node with state "startId"
void printHeatmap(double** M, int n); //prints the adjacency (connections) matrix 

vector<nodeType> getSuccesors(nodeType curr, navigationGraph g1);  //given a current node curr and the graph, return the nodes you can reach from curr.

//////////////////////////////////////////////////////////////

int main()
{
	string filename = "P4x6.txt";
	navigationGraph g1;
	cout << "Enter graph data filename :\n";
	cin >> filename;
	readGraphFromFile(filename, g1);
	int start = 0, goal = g1.size - 1;
	vector<int> path;
	cout << "\nA heatmap representation of the adjacency matrix of the graph:\n";
	printHeatmap(g1.adjM, g1.size);


	nodeType curr = { 0,-1,0,0 };
	vector<nodeType> children;
	cout << "Current Node:\n";
	printNode(curr);
	cout << "The possible children states are : \n";
	children = getSuccesors(curr, g1);
	int n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	cout << "\nEnter a node (separated by space: state parent costG costH)\n";
	cin >> curr.state >> curr.parent >> curr.costG >> curr.costH;
	cout << "Current Node:\n";
	printNode(curr);
	cout << "The possible children states are : \n";
	children = getSuccesors(curr, g1);
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	return 0;
}




/////////////////////////////////////////////////////////////////////////////////
bool readGraphFromFile(string filename, navigationGraph& g1)
{
	ifstream gfile(filename);

	if (!gfile)
	{
		cout << "Error opening file ..." << endl;
		return false;
	}

	int m, n;  //#of vertices, #of edges, 
	gfile >> m >> n;

	g1.size = m; //set the size of the graph

	//allocate memory for the adjacacy matrix
	g1.adjM = new double* [n];
	for (int i = 0; i < n; i++)
		g1.adjM[i] = new double[n] {0};

	int id; //vertex id
	double x, y;//x-y coordinates
	for (int i = 0; i < m; i++) //read the vertex information
	{
		gfile >> id >> x >> y;
		g1.xloc.push_back(x);
		g1.yloc.push_back(y);
	}

	int a, b; //read the edges and fill out the adjacency matrix

	for (int i = 0; i < n; i++)
	{
		gfile >> a >> b;
		g1.adjM[a][b] = 1;
		g1.adjM[b][a] = 1;
	}
	gfile.close();
	return true;
}


void printHeatmap(double** M, int n)
{
	cout << "   ";
	for (int i = 0; i < n; i++)
		cout << setw(2) << i;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] > 0)
				cout << char(176) << char(176);
			else
				cout << char(219) << char(219);
		}
		cout << endl;
	}
}

void printNode(nodeType curr)
{
	cout << "State: " << curr.state << ", Parent: " << curr.parent << ", costG: " << curr.costG << ", costH: " << curr.costH << endl;
}


// Implement Code
// Import cmath for distance calculation
#include <math.h>

vector<nodeType> getSuccesors(nodeType curr, navigationGraph g1) {
	// Initialize current state variables
	int curr_vertex = curr.state; //current vertex
	int parent = curr.parent; // parent vertex

	// Initialize new node and children vector
	nodeType newNode; vector<nodeType> children;
	newNode.parent = curr.state; // set parent state to current state

	vector<int> possible_dest; // vector of possible vertex from starting point
	for (int i = 0; i <= g1.size; i ++) { // Iterate through adjacency matrix to check if starting point is adjacent to other verticies
		if (g1.adjM[curr_vertex][i] == 1)
			possible_dest.push_back(i);
	}
	
	for (int child_vertex: possible_dest) { // loop through possible destination to compute cost
		double dist; // distance from parent to child -- sqrt((x2-x2)^2 + (y2-y1)^2)
		dist = sqrt(pow((g1.xloc[child_vertex] - g1.xloc[curr_vertex]),2) + pow((g1.yloc[child_vertex] - g1.yloc[curr_vertex]),2));

		newNode.state = child_vertex;
		newNode.costH = 0; // ** For now set Heuristic cost to 0
		newNode.costG = curr.costG + dist;  // costG of the parent + distance from parent to child 
		children.push_back(newNode); // Pushback newly created node into children vector
	}

	return children;
}