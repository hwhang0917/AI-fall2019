Heesang Mark Whang

CSCI 440: Artificial Intelligence

Assignment #4

10/23/2019

1. **(5 points)** You get full points if either
   
   * all the rest of the assignment elements work or ...
   * you spend a considerable amount of time working on trying to get the assignment working
     * Record the approximate amount of time working on the assignment
  * Detail the parts you struggled with and your attempts to get them working

2. Sudoku can be viewed as CSP(Constraints Satisfaction Problem).
   * The **variables** are *the individual cells, numbers 0 to 80,* based on the location on the board. A cell located in row A (can be 0 to 8) and column B (can be 0 to 8), will have index 9*A+B.
   
   * The **constraints** are converted to binary constraints and given by the constraints graph, represented by a *boolean matrix C\[81]\[81]* where C\[X]\[Y]=true if and only if cells x and y must be different (i.e. x and y are in the same row, same column, or same 3x3 sub-grid).
   
   * The **domain** for each of the variables are the numbers 1 to 9 and represented by *an array of vectors, vector<int> domain\[81].* Each individual Sudoku puzzle comes with a predefined assignment of values for particular cells (unary constraints). We reflect these unary constraints immediately on the domain. For example, if cell (variable) indexed by 70 is defined by puzzle to be 4, then domain\[70]={4} (instead of {1,2,3,4,5,6,7,8,9}).
   
   * An **assignment** is the assigning of specific value to each cell (variable) and is represented by *a vector of integers, vector<int> assignment*.
   
   * Furthermore we define a structure for each binary constraint which is an arc in the constraint graph.
   
     ```C++
     struct arcType {
     	int source;
     	int destination;
     };
     ```
   
     So the *constraint that xi and xj must be different can be represented by arcType c={xi, xj}*. This representation will be useful when implementing the AC-3 algorithm.
     
   
   a) (**1 point**) Implement the revise function with pseudocode shown in Figure 6.3, page 209.
   
   ```C++
   bool revise(int xi, int xj, vector<int> domain[81], const bool C[81][81]);
   ```
   
   b) (**1 point**) Implement the arc-consistency algorithm AC-3 with pseudocode shown in Figure 6.3, page 209. A suggestion is to make the queue a queue of *arcType*, and initialize it by all the arcs {xi, xj} that satisfy *C\[xi]\[xj]==true*.
   
   ```C++
   bool AC3(vector<int> domain[81], const bool C[81][81]);
   ```
   
   c) (**1 point**) A basic implementation of the backtrack algorithm on Figure 6.5, page 215 is given to you (called *backtrackCSP*). It does not do any inference r use any heuristics. Implement the backtrack algorithm with the MRV heuristics built in. You can build the function from scratch, or you can make a simple modification the function provided. The variable count keeps track of how many variables have already been assigned.
   
   ```C++
   vector<int> backtrackCSP_MRV(vector<int> assignment, int count, vector<int> domain[81], const bool C[81][81]);
   ```
   
   d) (**2 points**) You are given a sets of puzzle in the main function.
   
   * Run the backtrackCSP and backtrackCSP_MRV algorithms on the puzzles. Record the average time to solve them.
   * Apply AC3 to each puzzle, then run backtrackCSP and backtrackCSP_MRV algorithms on them. Record the average time to solve them.
   
   Record the results in the table below:
   
   |                       | Backtrack | Backtrack+MRV | Backtrack+AC3 | Backtrack+AC3+MRV |
   | --------------------- | --------- | ------------- | ------------- | ----------------- |
   | Average Solution time |           |               |               |                   |
   
   

