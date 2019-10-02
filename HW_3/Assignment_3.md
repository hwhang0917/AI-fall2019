Heesang Mark Whang

CSCI 440: Artificial Intelligence

Assignment #3

10/02/2019

1. **(5 points)** You get full points if either
   * all the rest of the assignment elements work or ...
   * you spend a considerable amount of time working on trying to get the assignment working
     * Record the approximate amount of time working on the assignment
     * Detail the parts you struggled with and your attempts to get them working
   
2. Robot Navigation

  * **(2 points)** Implement an A* search using the straight line distance (SLD) heuristic. The function prototype is given below. This algorithm will return the shortest path possible between start and goal state.

    ```C++
    vector<int> astar_SLD_Nav(navigationGraph g1, int start, int goal){
    	vector<int> path;
    	map<int, nodeType> explored; //The set of all nodes already explored
    	priority_queue<nodeType> frontier; //for BFS the frontier is a queue
    
    	double heuristic_dist; // heuristic distance && computer the heuristic distance of starting node
    	heuristic_dist = \
    		sqrt(pow((g1.xloc[start] - g1.xloc[goal]),2) + pow((g1.yloc[start] - g1.yloc[goal]),2));
    	nodeType startState = { start,-1,0, heuristic_dist}; //initialize the start node
    	frontier.push(startState); //initialize the frontier with the start node
    	int visit_count = 0; // Visted counter
    
    	while (!frontier.empty())
    	{
    		nodeType curr = frontier.top(); frontier.pop(); //take next node from the frontier
    		visit_count ++;
    		if (curr.state == goal)
    		{
    			explored[goal] = curr;
    			cout << "(A*)Node visited: " << visit_count << endl;
    			return getSolPath(goal, start, explored);
    		}
    		if (explored.find(curr.state) == explored.end()) //if the state has not been explored before, expand
    		{
    			explored[curr.state] = curr;
    			vector<nodeType> children = getSuccesors(curr, g1);
    			for (nodeType child: children) // Loop through children node
    			{
    				// Computer heuristic distance of each child nodes
    				child.costH = sqrt(pow((g1.xloc[child.state] - g1.xloc[goal]),2) + pow((g1.yloc[child.state] - g1.yloc[goal]),2));
    				if (explored.find(child.state) == explored.end())
    					frontier.push(child);
    			}
    		}
    	}
    
    	cout << "(A*)Node visited: " << visit_count << endl;
    	return path;
    }
    ```

    

  * **(1 point)** Modify your A* and uniform-cost functions to count the number of nodes visited. Submit both modified functions, marking in **bold** font the changes you made.

    Added, line[233], [238], [242], [259] to print node visit counter. Check Code: [a_star_nav.cc](./HW_3/a_star_nav.cc)

  * **(2 points)** Run both functions for each of the scenarios given, and complete the table below.
    
    | File Name  | Shortest path solution | #of nodes visited: uniform cost | #of nodes visited: A* |
    | ---------- | ---------------------- | ------------------------------- | --------------------- |
    | P1x1.txt   |                        |                                 |                       |
    | P1x1_2.txt |                        |                                 |                       |
    | P1x2.txt   |                        |                                 |                       |
    | P2x4s.txt  |                        |                                 |                       |
    | P3x4s.txt  |                        |                                 |                       |
    | P3x8s.txt  |                        |                                 |                       |
    | P4x6.txt   |                        |                                 |                       |
    
    