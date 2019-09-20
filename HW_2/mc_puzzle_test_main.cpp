#include <iostream>   //cin,cout
#include <queue>     
#include <vector>
#include <stack>
#include <map>
#include <iomanip>


using namespace std;

struct mcNode    //structure of each node in the tree
{
	int state;
	//state of the node
	// x =1 if boat is on the original side of the river, x=0 otherwise
	// y = "number of missionaries on the original side of the river"
	// z = "number of cannibals on the original side of the river"
	//state=x*100+y*10+z
	int parent;         //the state of the parent node
	double costG;       //g(n), cost (1 per step) from start to present
	int action;   //1=one cannibal on the boat; 2=two cannibals; 10=one missionary; 20=two missionaries; 11=one missionary+one cannibal 
};



vector<mcNode> getSuccesors(mcNode curr);
vector<mcNode> getSuccesors35(mcNode curr);
vector<mcNode> breadth_first_search_MC();
vector<mcNode> breadth_first_search_MC35();

void display(bool boat, int m, int c, int M = 3, int C = 3, int B = 2);




int main()
{


	vector<mcNode> path = breadth_first_search_MC();
	int n = path.size();
	if (n > 0)
	{

		cout << "Pathsize=" << n << endl;
		for (int i = n - 1; i >= 0; i--)
		{
			system("cls");
			int z = path[i].state;
			int boat = z / 100;
			z = z % 100;
			int x = z / 10;
			int y = z % 10;
			cout << "Testing 3 couples, boat capacity 2 case....\n";
			display(boat > 0, x, y);
			system("pause");
		}
	}
	else
	{
		cout << "No solution!!!" << endl;
	}
	system("pause");

	vector<mcNode> path2 = breadth_first_search_MC35();
	int n2 = path2.size();
	if (n2 > 0)
	{

		cout << "Pathsize=" << n2 << endl;
		for (int i = n2 - 1; i >= 0; i--)
		{
			system("cls");
			int z = path2[i].state;
			int boat = z / 100;
			z = z % 100;
			int x = z / 10;
			int y = z % 10;
			cout << "Testing 5 couples, boat capacity  case....\n";
			display(boat > 0, x, y, 5, 5, 3);
			system("pause");
		}
	}
	else
	{
		cout << "No solution!!!" << endl;
	}
	system("pause");
	return 0;
}
/////////////////////////////////////////////////////////////////////
void display(bool boat, int m, int c, int M , int C , int B )
{
	string Sm = "MMMMMMMMMMMMMMMMMMMM", Sc = "CCCCCCCCCCCCCCCCCCC", Sb = "___________", Ss = "         ";

	if (boat)
		cout << "\n\\" << Sb.substr(0, B) << "/  ";
	else
		cout << "\n      " << Ss.substr(0, B);
	cout << Sm.substr(0, m) << " " << Sc.substr(0, c) << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	if (!boat)
		cout << "\\" << Sb.substr(0, B) << "/  ";
	else
		cout << "      " << Ss.substr(0, B);
	cout << Sm.substr(0, M - m) << " " << Sc.substr(0, C - c) << endl;

}



//Put here your function implementations, including getSuccessors functions
vector<mcNode> getSuccesors(mcNode curr) {

	// Initialize current state variables
	int boat_origin = curr.state / 100; // 1= origin 0= other
	int m = (curr.state % 100) / 10;
	int c = (curr.state % 100) % 10;
	vector<int> actions; // vector of possible node actions (disregard validity)

	// Add actions according to state
	if (boat_origin) { // boat on the original side
		if (c >= 1) 
			actions.push_back(1);
		if (c >= 2) 
			actions.push_back(2);
		if (m >= 1) 
			actions.push_back(10);
		if (m >= 2) 
			actions.push_back(20);
		if (m >= 1 && c >= 1)
			actions.push_back(11);
	} else { //boat on the other side
		if (3 - c >= 1)
			actions.push_back(1);
		if (3 - c >= 2)
			actions.push_back(2);
		if (3 - m >= 1)
			actions.push_back(10);
		if (3 - m >= 2)
			actions.push_back(20);
		if ((3 - m >= 1) && (3 - c >= 1))
			actions.push_back(11);
	}

	// Initialize new node and vector of children nodes, validity boolean
	mcNode newNode; vector<mcNode> children; bool valid;

	// Set base node for reset purpose
	mcNode baseNode = curr;
	baseNode.costG += 1;
	baseNode.parent = curr.state;

	// Update state for child node
	for (int action: actions) {

		// Reset baseNode each iteration
		newNode = baseNode;
		valid = true;
		newNode.action = action;

		// Update state according to given action
		if (boat_origin) {
			newNode.state -= (100 + action);
		} else {
			newNode.state += (100 + action);
		}

		// Parse newNode state
		int new_b = newNode.state / 100;
		int new_m = (newNode.state % 100) / 10;
		int new_c = (newNode.state % 100) % 10;

		int ot_m = 3 - new_m;
		int ot_c = 3 - new_c;

		// Check Validity
		if ((new_m < new_c) || ((ot_m) < (ot_c))) { // False if cannibals overnumbers missionaries on either side
			if (new_m == 0 || ot_m == 0) {
				valid = true; 
			} else {
			valid = false;
			}
		}

		if (valid) // If valid, push newNode into children vector
			children.push_back(newNode);
	}

	return children;
}

vector<mcNode> getSuccesors35(mcNode curr) {
	/* 
		Valid Actions 
		| Actions | Missionary | Cannibals | Valid |
		| ------- | ---------- | --------- | ----- |
		| 01      | 0          | 1         | TRUE  |
		| 02      | 0          | 2         | TRUE  |
		| 03      | 0          | 3         | TRUE  |
		| 10      | 1          | 0         | TRUE  |
		| 20      | 2          | 0         | TRUE  |
		| 30      | 3          | 0         | TRUE  |
		| 11      | 1          | 1         | TRUE  |
		| 12      | 1          | 2         | FALSE |
		| 21      | 2          | 1         | TRUE  |
	*/

	// Initialize current state variables
	int boat_origin = curr.state / 100; // 1= origin 0= other
	int m = (curr.state % 100) / 10;
	int c = (curr.state % 100) % 10;

	vector<int> actions; // vector of possible node actions (disregard validity)

	// Add actions according to state
	// * Note: action 12 is invalid because cannibals outnumbers missionaries on the boat
	if (boat_origin) { // boat on the original side
		if (c >= 1) 
			actions.push_back(1);
		if (c >= 2) 
			actions.push_back(2);
		if (c >= 3)
			actions.push_back(3);
		if (m >= 1) 
			actions.push_back(10);
		if (m >= 2) 
			actions.push_back(20);
		if (m >= 3)
			actions.push_back(30);
		if (m >= 1 && c >= 1)
			actions.push_back(11);
		if (m >= 2 && c >= 1)
			actions.push_back(21);
	} else { //boat on the other side
		if (5 - c >= 1)
			actions.push_back(1);
		if (5 - c >= 2)
			actions.push_back(2);
		if (5 - c >= 3)
			actions.push_back(3);
		if (5 - m >= 1)
			actions.push_back(10);
		if (5 - m >= 2)
			actions.push_back(20);
		if (5 - m >= 3)
			actions.push_back(30);
		if ((5 - m >= 1) && (5 - c >= 1))
			actions.push_back(11);
		if ((5 - m >= 2) && (5 - c >= 1))
			actions.push_back(21);
	}

	// Initialize new node and vector of children nodes, validity boolean
	mcNode newNode; vector<mcNode> children; bool valid;

	// Set base node for reset purpose
	mcNode baseNode = curr;
	baseNode.costG += 1;
	baseNode.parent = curr.state;

	// Update state for child node
	for (int action: actions) {

		// Reset baseNode each iteration
		newNode = baseNode;
		valid = true;
		newNode.action = action;

		// Update state according to given action
		if (boat_origin) {
			newNode.state -= (100 + action);
		} else {
			newNode.state += (100 + action);
		}

		// Parse newNode state
		int new_b = newNode.state / 100;
		int new_m = (newNode.state % 100) / 10;
		int new_c = (newNode.state % 100) % 10;

		int ot_m = 5 - new_m;
		int ot_c = 5 - new_c;

		// Check Validity
		if ((new_m < new_c) || ((ot_m) < (ot_c))) { // False if cannibals overnumbers missionaries on either side
			if (new_m == 0 || ot_m == 0) {
				valid = true; 
			} else {
			valid = false;
			}
		}

		if (valid) // If valid, push newNode into children vector
			children.push_back(newNode);
	}

	return children;
}

// TODO: Breadth First Search Function Implementation
vector<mcNode> breadth_first_search_MC() {
	
}

vector<mcNode> breadth_first_search_MC35() {
	vector<mcNode> sample;
	return sample;
}