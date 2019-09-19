Heesang Mark Whang

CSCI440: Artificial Intelligence

Assignment #1

09/18/2019



1.  **(5 points)** You get the full points if either 

   * all the rest of the assignment elements work or  

   * you spend a considerable amount of time working on trying to get the assignment working    
     * Record the approximate amount of time working on the assignment 
     * Detail the parts you struggled with and your attempts to get them working
       
   
2.  Missionaries and Cannibals problem
    a)  **(2 points)** 3 M / 3 C / boat_cap 3
    
    ```C++
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
            if ((new_m < new_c) || ((ot_m) < (ot_c))) { 
                // False if cannibals overnumbers missionaries on either side
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
    ```
    
    b) **(1 point)** 5 M / 5 C / boat_cap 5
    
    ```C++
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
            if ((new_m < new_c) || ((ot_m) < (ot_c))) { 
                // False if cannibals overnumbers missionaries on either side
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
    ```
    
3. **(2 points)** Navigation problem

```C++
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
```

