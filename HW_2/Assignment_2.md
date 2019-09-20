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
   vector<mcNode> breadth_first_searchMC();
   ```

   b) Implement the function for the 5 couples , boat capacity 3 scenario

   ```C++
   vector<mcNode> breadth_frist_searchMC35();
   ```

3. **(3 points)** Navigation problem

   a) Implement the Breadth-First search function with the prototype.
   	This algorithm will return a path with the shortest number of jumps possible from start to
   	goal.

   ``` C++
   vector<int> breadth_fist_search_Nav(navigationGraph g1, int start, int goal);
   ```

   b) Implement the Uniform-cost search function with the prototype.

   ```C++
   vector<int> uniform_cost_search_Nav(navigationGraph g1, int start, int goal);
   ```

   c) Implement the Depth-First search function with the prototype.

   ```C++
   vector<int> depth_first_search_Nav(navigationGraph g1, int start, int goal);
   ```

   