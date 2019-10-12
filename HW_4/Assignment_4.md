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
int getAttackScore(int Q[]) { // Compute number of conflicts
    	int row_conf = 0; // number of conflict horizontally (row)
	int diag_conf = 0; // number of conflict diagonally (diag)
	int total_conf = 0; // total conflict number

	///////////////////////////////////////////////////////////////////////////////////
	//							Row Conflict computation							 //
	///////////////////////////////////////////////////////////////////////////////////

	int QCount_in_row[8] = {}; // number of queens in row [index]

	for (int i = 0; i < 8; i++) { // Increment for number of queens in the same row
		int row_id = Q[i];
		QCount_in_row[row_id]++;
	}

	for (int i = 0; i < 8; i++) { // Same number of 'n' queens in a row makes (n*(n-1)/2) conflicts
		int queen_num = QCount_in_row[i];
		row_conf += (queen_num * (queen_num - 1) / 2);
	}

	///////////////////////////////////////////////////////////////////////////////////
	//						Diagonal Conflict computation							 //
	///////////////////////////////////////////////////////////////////////////////////
	// Refer to Note.md
	int QCount_in_diagA[15] = {}; // number of queens in diagonalA [index] [0] ~ [14]
	int QCount_in_diagB[15] = {}; // number of queens in diagonalB [index] [0] ~ [14]

	for (int i = 0; i < 8; i++) { // Increment for number of queens in the same diagonal line (A)
		int diagA_id = Q[i] + i;
		QCount_in_diagA[diagA_id]++;
	}

	for (int i = 0; i < 8; i++) { // Increment for number of queens in the same diagonal line (B)
		int diagB_id = (8 - Q[i] + 1) + i; // flip the row_id for diagB_id
		QCount_in_diagB[diagB_id]++;
	}

	for (int i = 0; i < 15; i++) { // Same number of 'n' queens in a diagonal line A or B makes (n*(n-1)/2) conflicts
		int queen_num_dA = QCount_in_diagA[i];
		int queen_num_dB = QCount_in_diagB[i];
		diag_conf += (queen_num_dA * (queen_num_dA - 1) / 2);
		diag_conf += (queen_num_dB * (queen_num_dB - 1) / 2);
	}

	// Add all conflicts
	total_conf = row_conf + diag_conf;

	return total_conf;
}
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

