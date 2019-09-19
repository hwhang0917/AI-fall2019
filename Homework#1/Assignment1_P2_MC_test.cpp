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

void printNode(mcNode x)
{
	cout << "State: " << x.state << "; Parent:" << x.parent << "; Cost: " << x.costG << "; Action: " << x.action << endl;
}

int main()
{
	mcNode curr = { 133,-1, 0, 0 };
	vector<mcNode> children;
	cout << "Testing 3 couples and boat capacity 2....\n\n";
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors(curr);
	cout << "Possible child nodes :\n";
	int n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	cout << "Enter a node (apace separated: state parent cost action)\n";
	cin >> curr.state >> curr.parent >> curr.costG >> curr.action;
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	system("pause");
	cout << "\nTesting 5 couples and boat capacity 3....\n\n";
	curr = { 155,-1, 0, 0 };
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors35(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	cout << "Enter a node (space separated: state parent cost action)\n";
	cin >> curr.state >> curr.parent >> curr.costG >> curr.action;
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors35(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);


	return 0;
}

//To test your functions, place them below
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