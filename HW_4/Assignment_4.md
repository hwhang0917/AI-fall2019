Heesang Mark Whang

CSCI 440: Artificial Intelligence

Assignment #4

10/14/2019

1. **(5 points)** You get full points if either
   * all the rest of the assignment elements work or ...
   * you spend a considerable amount of time working on trying to get the assignment working
     * Record the approximate amount of time working on the assignment
     * Detail the parts you struggled with and your attempts to get them working
   
2. Solve the 8-queens problem using Simulated Annealing and First Choice Hill Climbing.

  a) **(1 points)** Implement a function that given a random placement of the queens, will return the # of conflicts (as discussed in the book and in class (a conflicts occur anytime two queens can attack each other).

```C++
int getAttackScore(int Q[]);
```

  b) **(1 points)** Implement a function that given a queen position, will return a neighbor position obtained by randomly moving one of the queens to a different row on the same column. Implement a function that given a *∆E* and a temperature *T*, will return true with probability *e^(∆E/T)*.
    
```C++
void nextPosition(int Q[], int nextQ[]);
bool acceptNext (double dE, double T);
```

  c) **(1 points)**  Using the functions from part a and b, implement ***simulated annealing*** using a linear temperature schedule, with *T0* and maximum number of steps *N* (i.e, decrease temperature each time step by a *∆T*, such that after *N* steps *T=0*). The function should take a random state *Q*, *T0* and *N* as argument. After each fun the function should return true if solution is found and false if it is not. At the completion of the run Q should contain the value of the solution (or the last attempt if the solution is not found).

``` c++
bool solveSimulatedAnnealing(int Sol[], double T0 = 4, int maxSteps = 5000);
```

  d) **(1 points)** Using the functions from part a and b, implement ***first choice hill annealing*** with maximum number of steps *N*. The function should take a random state *Q* and *N* as argument. After each run the function should return true if solution is found and  false if it is not. At the completion of the run *Q* should contain the value of the solution (or the last attempt if the solution is not found).

[^Hint]: First Choice Hill climbing is basically simulated annealing with a much simpler acceptNext function.

``` C++
bool solveHillClimbingFC(int Sol[], int maxSteps = 5000);
```

  e) **(1 points)** Run the simulation 100 times with *T0=4*, *N=5000* and record the number of times the solution is found each of the above algorithms (simulated annealing and first choice). Make sure you use the same starting queen position for both algorithms. Repeat with *N=50000*. Fill in the table below with the success rate percentage.

​	**Success Rate Table**

|                            | N=5000 | N=50000 |
| :------------------------: | :----: | :-----: |
|    Simulated Annealing     |        |         |
| First Choice Hill Climbing |        |         |

