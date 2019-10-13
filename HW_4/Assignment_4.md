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
int getAttackScore(int Q[])
{	// Compute number of conflicts

	int conflicts = 0; // number of conflicts

	// Refer to Note.md
	int QCount_in_row[8] = {}; // number of queens in row [index]
	int QCount_in_diagA[15] = {}; // number of queens in diagonalA [index] [0] ~ [14]
	int QCount_in_diagB[15] = {}; // number of queens in diagonalB [index] [0] ~ [14]

	for (int i = 0; i < 8; i++) { // Increment for number of queens in the same row
		int row_id = Q[i]; // Row ID
		int diagA_id = Q[i] + i; // Diagonal Line (A) ID
		int diagB_id = (8 - Q[i] + 1) + i; // Diagonal Line (B) ID: flip the row_id for diagB_id

		// Increment, each time there are queens in the same row/diagonal
		QCount_in_row[row_id]++;
		QCount_in_diagA[diagA_id]++;
		QCount_in_diagB[diagB_id]++;
	}

	for (int i = 0; i < 15; i++) { // Same number of 'n' queens in a row or a diagonal line A or B makes (n*(n-1)/2) conflicts
		if (i <= 8) { // Row conflict computation
			int queen_num_row = QCount_in_row[i];
			conflicts += (queen_num_row * (queen_num_row - 1) / 2);
		}
		int queen_num_dA = QCount_in_diagA[i];
		int queen_num_dB = QCount_in_diagB[i];
		conflicts += (queen_num_dA * (queen_num_dA - 1) / 2);
		conflicts += (queen_num_dB * (queen_num_dB - 1) / 2);
	}

	return conflicts;
}
```

  b) **(1 points)** Implement a function that given a queen position, will return a neighbor position obtained by randomly moving one of the queens to a different row on the same column. Implement a function that given a *∆E* and a temperature *T*, will return true with probability *e^(∆E/T)*.

```C++
void nextPosition(int Q[], int nextQ[])
{
	for (int i = 0; i < 8; i++) // Copy Q[] into nextQ[]
			nextQ[i] = Q[i];

	int pickColumn = rand() % 8; // Select a column for a queen to be moved
	int possibleMoves[7]; // Array of possible queen moves in the selected column (0~7 except current position)
	int curr_pos = Q[pickColumn]; // Current row position of the queen in selected column

	for (int i = 0; i < 7; i++) { // Populate the possible moves array with 0~7 except current position
		if (i >= curr_pos)
			possibleMoves[i] = i + 1;
		else
			possibleMoves[i] = i;
	}

	int nextMove_idx = rand() % 7; // Select next possible move index
	int nextMove = possibleMoves[nextMove_idx]; // Select next move

	nextQ[pickColumn] = nextMove; // Move nextQ[] into selected position
}

bool acceptNext(double dE, double T)
{
	double randProb = ((double) rand() / (RAND_MAX)); // Save random double from 0~1
	double actProb = exp(dE / T); // Actual probability

	if (randProb <= actProb) // return true if double is <= actual probability
		return true;
	else // otherwise return false
		return false;
}
```

  c) **(1 points)**  Using the functions from part a and b, implement ***simulated annealing*** using a linear temperature schedule, with *T0* and maximum number of steps *N* (i.e, decrease temperature each time step by a *∆T*, such that after *N* steps *T=0*). The function should take a random state *Q*, *T0* and *N* as argument. After each fun the function should return true if solution is found and false if it is not. At the completion of the run Q should contain the value of the solution (or the last attempt if the solution is not found).

``` c++
bool solveSimulatedAnnealing(int Sol[], double T0, int maxSteps)
{
	double dE; // initialize energy difference
	double dT = T0 / maxSteps; // T steps should be that of T / N, so that after N runs, T = 0
	int nextQ[8];
	for (int i = 0; i <8; i++) // Copy given random queen position to nextQ
		nextQ[i] = Sol[i];

	for (int i = maxSteps; i >= 0; i--) { // Repeat for maxSteps times
		if (getAttackScore(Sol) == 0) // if solution is found, return true
			return true;

		nextPosition(Sol, nextQ); // get random next move
		dE = getAttackScore(Sol) - getAttackScore(nextQ); // compute energy difference

		if (dE > 0) { // if energy difference is positive, pick the move
			for (int i = 0; i < 8; i ++) // copy nextQ into Sol
				Sol[i] = nextQ[i];
		}
		else { // else, check the probability and determine whether to pick the move
			if (acceptNext(dE, T0)) {
				for (int i = 0; i < 8; i ++) // copy nextQ into Sol
					Sol[i] = nextQ[i];
			}
		}

		T0 -= dT; // Decrement temperature by dT
	}
	return false; // solution not found
}
```

  d) **(1 points)** Using the functions from part a and b, implement ***first choice hill annealing*** with maximum number of steps *N*. The function should take a random state *Q* and *N* as argument. After each run the function should return true if solution is found and  false if it is not. At the completion of the run *Q* should contain the value of the solution (or the last attempt if the solution is not found).

[^Hint]: First Choice Hill climbing is basically simulated annealing with a much simpler acceptNext function.

``` C++
bool solveHillClimbingFC(int Sol[], int maxSteps)
{
	double dE; // initialize energy difference
	int nextQ[8];
	for (int i = 0; i <8; i++) // Copy given random queen position to nextQ
		nextQ[i] = Sol[i];

	for (int i = maxSteps; i >= 0; i--) { // Repeat for maxSteps times
		if (getAttackScore(Sol) == 0) // if solution is found, return true
			return true;

		nextPosition(Sol, nextQ); // get random next move
		dE = getAttackScore(Sol) - getAttackScore(nextQ); // compute energy difference

		if (dE > 0) { // if energy difference is positive, pick the move
			for (int i = 0; i < 8; i ++) // copy nextQ into Sol
				Sol[i] = nextQ[i];
		}
	}
	return false; // solution not found
}
```

  e) **(1 points)** Run the simulation 100 times with *T0=4*, *N=5000* and record the number of times the solution is found each of the above algorithms (simulated annealing and first choice). Make sure you use the same starting queen position for both algorithms. Repeat with *N=50000*. Fill in the table below with the success rate percentage.

​	**Success Rate Table**

|                            | N=5000 | N=50000 |
| :------------------------: | :----: | :-----: |
|    Simulated Annealing     |  81 %  |  100 %  |
| First Choice Hill Climbing |  91 %  |  95 %  |
