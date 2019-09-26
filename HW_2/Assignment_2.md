Heesang Mark Whang

CSCI 440: Artificial Intelligence

Assignment #2

09/25/2019

1. **(5 points)** You get full points if either
   * all the rest of the assignment elements work or ...
   * you spend a considerable amount of time working on trying to get the assignment working
     * Record the approximate amount of time working on the assignment
     * Detail the parts you struggled with and your attempts to get them working
   
2. **(2 points)** Missionaries and Cannibals Problem

   a) Implement the function for the 3 couples scenario

   ```C++
   vector<mcNode> breadth_first_searchMC() {
       mcNode start = {133,-1,0,0};
   	queue<mcNode> frontier;
   	map<int, mcNode> explored;
   	vector<mcNode> solution;
   	frontier.push(start);
   
   	while (!frontier.empty()) {
   		mcNode curr = frontier.front(); frontier.pop();
   		if (explored.find(curr.state) != explored.end())
   			continue;
   		if (curr.state == 0) { //goal reached
   			while(curr.state != start.state) {
   				solution.push_back(curr);
   				curr = explored[curr.parent];
   			}
   			solution.push_back(curr);
   			return solution;
   		}
   		explored[curr.state] = curr;
   		for (mcNode child: getSuccesors(curr)) {
   			if(explored.find(child.state) == explored.end()) {
   				frontier.push(child);
   			}
   		}
   	}
   
   	return solution;
   }
   ```

   b) Implement the function for the 5 couples , boat capacity 3 scenario

   ```C++
   vector<mcNode> breadth_frist_searchMC35() {
      	mcNode start = {155,-1,0,0};
   	queue<mcNode> frontier;
   	map<int, mcNode> explored;
   	vector<mcNode> solution;
   	frontier.push(start);
   
   	while (!frontier.empty()) {
   		mcNode curr = frontier.front(); frontier.pop();
   		if (explored.find(curr.state) != explored.end())
   			continue;
   		if (curr.state == 0) { //goal reached
   			while(curr.state != start.state) {
   				solution.push_back(curr);
   				curr = explored[curr.parent];
   			}
   			solution.push_back(curr);
   			return solution;
   		}
   		explored[curr.state] = curr;
   		for (mcNode child: getSuccesors35(curr)) {
   			if(explored.find(child.state) == explored.end()) {
   				frontier.push(child);
   			}
   		}
   	}
   
   	return solution;
   }
   ```

3. **(3 points)** Navigation problem

   a) Implement the Breadth-First search function with the prototype.
   	This algorithm will return a path with the shortest number of jumps possible from start to
   	goal.

   ``` C++
   vector<int> breadth_fist_search_Nav(navigationGraph g1, int start, int goal) {
       nodeType root ={start, -1, 0, 0};
	queue<nodeType> frontier;
   	map<int, nodeType> explored;
	vector<int> solution;
   
   	frontier.push(root);
   
	while (!frontier.empty()) {
   		nodeType curr = frontier.front(); frontier.pop();
		if (explored.find(curr.state) != explored.end())
   			continue;
   		if (curr.state == goal) { //goal reached
   			while(curr.state != root.state) {
				solution.push_back(curr.state);
   				curr = explored[curr.parent];
   			}
   			solution.push_back(curr.state);
   			return solution;
   		}
   		explored[curr.state] = curr;
   		for (nodeType child: getSuccesors(curr, g1)) {
   			if(explored.find(child.state) == explored.end()) {
   				frontier.push(child);
   			}
   		}
   	}
   
   	return solution;
   }
   ```
   
   b) Implement the Uniform-cost search function with the prototype.
   
   ```C++
   vector<int> uniform_cost_search_Nav(navigationGraph g1, int start, int goal) {
      	nodeType root ={start, -1, 0, 0};
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
   ```
   
   c) Implement the Depth-First search function with the prototype.
   
   ```C++
   vector<int> depth_first_search_Nav(navigationGraph g1, int start, int goal) {
       nodeType root ={start, -1, 0, 0};
   	stack<nodeType> frontier;
   	map<int, nodeType> explored;
   	vector<int> solution;
   
   	frontier.push(root);
   
   	while (!frontier.empty()) {
   		nodeType curr = frontier.top(); frontier.pop();
   		if (explored.find(curr.state) != explored.end())
   			continue;
   		if (curr.state == goal) { //goal reached
   			while(curr.state != root.state) {
   				solution.push_back(curr.state);
   				curr = explored[curr.parent];
   			}
   			solution.push_back(curr.state);
   			return solution;
   		}
   		explored[curr.state] = curr;
   		for (nodeType child: getSuccesors(curr, g1)) {
   			if(explored.find(child.state) == explored.end()) {
   				frontier.push(child);
   			}
   		}
   	}
   	
   	return solution;
   }
   ```
   
   