#include <iostream>   //cin,cout
#include <fstream>   //files
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#include <math>

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

// Necessary Functions declaration
bool readGraphFromFile(string filename, navigationGraph& g1);  //given a file, populate the graph
void printNode(nodeType curr);  //given a node, it prints out it's information
void printHeatmap(double** M, int n); //prints the adjacency (connections) matrix

vector<nodeType> getSuccesors(nodeType curr, navigationGraph g1);  //given a current node curr and the graph, return the nodes you can reach from curr.
vector<int> uniform_cost_search_Nav(navigationGraph g1, int start, int goal);  //uniform cost search between two nodes, returns a path
vector<int> astar_SLD_Nav(navigationGraphg1, int start, int goal); //astar cost search between two nodes, returns a path

int main(int argc, char const *argv[]) {
  string filename = "P4x6.txt";
	navigationGraph g1;
	cout << "Enter graph data filename :\n";
	cin >> filename;
	if (!readGraphFromFile(filename, g1))
		exit(1);
	int start = 0, goal = g1.size - 1;
	cout << "\nA heatmap representation of the adjacency matrix of the graph:\n";
	printHeatmap(g1.adjM, g1.size);

	vector<int> USC_path = uniform_cost_search_Nav(g1, start, goal);

	cout << "Uniform Cost Search Solution  : ";
	for (int i = USC_path.size() - 1; i >= 0; i--)
		cout << USC_path[i] << ", ";
	cout << endl;

	vector<int> ASLD_path = astar_SLD_Nav(g1, start, goal);

	cout << "A* Search Solution  : ";
	for (int i = ASLD_path.size() - 1; i >= 0; i--)
		cout << ASLD_path[i] << ", ";
	cout << endl;

	system("pause");

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void printNode(nodeType curr)
{
	cout << "State: " << curr.state << ", Parent: " << curr.parent << ", costG: " << curr.costG << ", costH: " << curr.costH << endl;
}

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
				cout << char(219) << char(219);
			else
				cout << char(176) << char(176);
		}
		cout << endl;
	}
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
vector<int> uniform_cost_search_Nav(navigationGraph g1, int start, int goal) {
	nodeType root = {start, -1, 0, 0};
	vector<nodeType> frontier;
	map<int, nodeType> explored;
	vector<int> solution;

	frontier.push_back(root);

	while (!frontier.empty()) {

		nodeType curr;
		for (int i = 0; i <= frontier.size(); i ++) {
			for (int j = i + 1; j <= frontier.size(); j ++) {
				if (frontier[i].costG < frontier[j].costG) {
					curr = frontier[i];
					frontier.erase(frontier.begin() + (i-1));
				} else {
					curr = frontier[j];
					frontier.erase(frontier.begin() + (j-1));
				}
			}
		}

		if (explored.find(curr.state) != explored.end())
			continue;
		if (curr.state == goal) { //goal reached
			while(curr.state != root.state) {
				solution.push_back(curr.state);
				curr = explored[curr.parent];
			}
			solution.push_back(curr.state);
			cout << endl;
			return solution;
		}
		explored[curr.state] = curr;
		for (nodeType child: getSuccesors(curr, g1)) {
			if(explored.find(child.state) == explored.end()) {
				frontier.push_back(child);
			}
		}
	}

	return solution;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
