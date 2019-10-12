#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <iomanip>

using namespace std;


/*Helper functions ******************************************/
void getRandomPlacement(int Q[]);
//returns a random placement of 8 queens, 1 queen per file (column)



/*Helper functions to be implemented by students ******************************************/
int getAttackScore(int Q[]);
//given an 8 queen placement (1 queen per file), return the number of pairs of attacking queens

void nextPosition(int Q[], int nextQ[]);
//given an 8 queen placement Q (1 queen per file), 
//return the next placement nextQ, by changing the position of one of the queens

bool acceptNext(double dE, double T);
//given a change in "energy" dE and a "temperature" T, return
// true with probability e^(dE/T)

/*End of helper functions to be implemented by students ***************************************/

/*Algorithm implementations to be implemented by students *************************************/

bool solveHillClimbingFC(int Sol[], int maxSteps = 5000);
//solves the 8 queens program using hill climbing first choice (pick a random direction that improves score)

bool solveSimulatedAnnealing(int Sol[], double T0 = 4, int maxSteps = 5000);
//solves the 8 queens program using simulated annealing
//current version uses a linear schedulling T with a max of maxSteps  from T=T0 to T=0.



/*drawing functions*******************************************************/
void getBoard(string B[]);
//returns B, a 24x40  array of characters containing the chess board layout. 

void placeQueens(string B[], int Q[]);
//given a board layout B, place the queens on the board.

void printBoard(string B[]);
//given a board layout B, print it on screen
/*************************************************************************/


int main()
{
	int Q[8], Qs[8], Qf[8];
	srand(time(NULL));

	string B[24];   //drawing board

	/*Testing attack score*/
	for (int i = 0; i < 5; i++)
	{
		cout << "Testing attack score...\n";
		getRandomPlacement(Q);   //get a random queen placement
		getBoard(B);
		placeQueens(B, Q);
		printBoard(B);
		cout << "Attack Score : " << getAttackScore(Q) << endl;
		system("pause");
		system("cls");
	}

	/*Testing  nextPosition*/
	getRandomPlacement(Q);   //get a random queen placement

	for (int i = 0; i < 5; i++)
	{
		cout << "Testing nextPostion...\n";
		cout << "Current position:\n";
		getBoard(B);
		placeQueens(B, Q);
		printBoard(B);
		nextPosition(Q, Qs);
		cout << "\nNext random position:\n";

		getBoard(B);
		placeQueens(B, Qs);
		printBoard(B);
		system("pause");
		system("cls");
	}

	/*testing acceptNext*/
	cout << "Testing nextPostion...\n";
	double dE, T;
	for (int j = 0; j < 2; j++)
	{
		cout << "Enter dE (dE<0) : ";
		cin >> dE;
		cout << "Enter T (T>0) : ";
		cin >> T;
		int count = 0;
		for (int i = 0; i < 1000; i++)
			if (acceptNext(dE, T))
				count++;
		cout << "Probaility p=e^(dE/T) : " << exp(dE / T) << endl;
		cout << "Empirically calculated : " << count / 1000.0 << endl;
	}
	system("pause");
	system("cls");

	/*Testing the algorithm implementations*/

	getRandomPlacement(Q);   //get a random queen placement
	for (int i = 0; i < 8; i++)
		Qs[i] = Qf[i] = Q[i];  //copy the initial placement to the eventual solutions


	cout << "Initial position.\n";
	cout << "Attack Score : " << getAttackScore(Q) << endl;
	getBoard(B);
	placeQueens(B, Q);
	printBoard(B);

	/*Testing SA*/
	cout << "\n\nTesting Simulated Annealing .....\n";
	bool foundS = solveSimulatedAnnealing(Qs, 4, 10000);
	if (foundS)
		cout << "SA solution found. \n";
	else
		cout << "No SA solution found.  Here is the last position tried : \n";
	cout << "Attack Score : " << getAttackScore(Qs) << endl;
	getBoard(B);
	placeQueens(B, Qs);
	printBoard(B);
	system("pause");

	/*Testing FCHC*/
	cout << "\n\nTesting First Choice Hill Climbing .....\n";
	bool foundF = solveHillClimbingFC(Qf, 10000);
	if (foundF)
		cout << "FC solution found. \n";
	else
		cout << "No FC solution found.  Here is the last position tried : \n";
	cout << "Attack Score : " << getAttackScore(Qf) << endl;
	getBoard(B);
	placeQueens(B, Qf);
	printBoard(B);
	system("pause");


	system("pause");
	return 0;
}


/*Helper functions ******************************************/
void getRandomPlacement(int Q[])
{
	for (int i = 0; i < 8; i++)
		Q[i] = rand() % 8;

}

/*drawing functions*******************************************************/

void getBoard(string B[])
{
	char chw = 219, chb = ' ';
	string so = "", se = "";
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++)
		{
			if (i % 2)
			{
				so = so + chb;
				se = se + chw;
			}
			else
			{
				so = so + chw;
				se = se + chb;
			}
		}

	for (int i = 0; i < 8; i++)
	{
		if (i % 2)
		{
			B[3 * i] = B[3 * i + 1] = B[3 * i + 2] = so;
		}
		else
		{
			B[3 * i] = B[3 * i + 1] = B[3 * i + 2] = se;
		}

	}
}

void placeQueens(string B[], int Q[])
{
	char ch = 177;
	for (int i = 0; i < 8; i++)
	{
		B[3 * Q[i] + 1][5 * i + 2] = ch;
		B[3 * Q[i] + 1][5 * i + 1] = ch;
		B[3 * Q[i] + 1][5 * i + 3] = ch;
	}
}

void printBoard(string B[])
{
	char cv = 176, ch1 = 176, ch2 = 176;
	cout << " ";
	for (int i = 0; i < 42; i++)
		cout << ch1;
	cout << endl;
	for (int i = 23; i >= 0; i--)
	{
		if (i % 3 == 1)
		{
			char ch = i / 3 + '1';
			cout << ch;
		}
		else
			cout << " ";
		cout << cv << B[i] << cv << endl;

	}
	cout << " ";
	for (int i = 0; i < 42; i++)
		cout << ch1;
	cout << endl;

	for (int i = 0; i < 43; i++)
		if (i % 5 == 4)
		{
			char ch = i / 5 + 'a';
			cout << ch;
		}
		else
			cout << " ";
	cout << endl;

}
/*end drawing functions*******************************************************/


/*Functions to be implemented by students ******************************************/
int getAttackScore(int Q[])
{	// Compute number of conflicts

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

	for (int i = 0; i < 8; i++) { // Increment for number of queens in the same diagonal line (A) and (B)
		int diagA_id = Q[i] + i;
		int diagB_id = (8 - Q[i] + 1) + i; // flip the row_id for diagB_id
		QCount_in_diagA[diagA_id]++;
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

void nextPosition(int Q[], int nextQ[])
{
}

bool acceptNext(double dE, double T)
{
	return false;
}


bool solveSimulatedAnnealing(int Sol[], double T0, int maxSteps)
{
	return false;
}


bool solveHillClimbingFC(int Sol[], int maxSteps)
{
	return false;
}
