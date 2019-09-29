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
    vector<int> astar_SLD_Nav(navigationGraph g1, int start, int goal);
    ```

    

  * **(1 point)** Modify your A* and uniform-cost functions to count the number of nodes visited. Submit both modified functions, marking in **bold** font the changes you made.

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
    
    