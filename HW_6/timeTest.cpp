#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <chrono>
#include <queue>


using namespace std;
using namespace std::chrono;

///////////////////////////////////////////////////////
//functions for drawing the board//////////////////////
void getSudokuBoard(string table[]);
void displayBoard(string table[]);
void fillDisplayBoard(string board[], int sudokuM[][9]);
void fillDisplayBoard(string board[], vector<int> assignment);
void displayBoard(string table[], int T[][9]);
void displaySudokuCSP(vector<int> assignment, vector<int> domain[81]);
void displaySudokuSimple(vector<int> assignment);
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
///Helper functions and structures///////////////////////
void fillConst(bool C[81][81]);   //creates the constraint graph
void getSudokuCSP(string puzzle, vector<int>& assignment, vector<int> domain[81]);
//given a puzzle as a string of 81 characters 0-9 
//return the apropriate assigment and domain

struct arcType   //a structure for a binary constraint, i.e., an edge in the graph
{
	int source;
	int destination;
};




vector<int> backtrackCSP(vector<int> assignment, int count, vector<int> domain[81], const bool C[81][81]);
vector<int> backtrackCSP_MRV(vector<int> assignment, int count, vector<int> domain[81], const bool C[81][81]);

bool AC3(vector<int> domain[81], const bool C[81][81]);
bool revise(int xi, int xj, vector<int> domain[81], const bool C[81][81]);


int main()
{

	string puzzles[] = { "000500002700600800001000300076050000002000000080000700390072600020000090050018030",
		"800201040000000107709006003006340000003060000002000008020903000000080090000007080",
		"100003400000600020008005300001004070406800100000000005065080002802001600000000000",
		"809402037020090500360000800500000000080037000076008000000000093700300000900054000",
		"050800607000600520100509080040001700007006490000000000921000070000005100560000000",
		"001200000000047000789006000060008701070002400100000906036000000800090000400070000",
		"400070009008605070005000026000800704670000500000000000069000000000590010020010040",
		"080006070002407010003000000000010800201060037300000240106000000034070000000090000",
		"000000040000000906350100800510030400004910008060004000030000160200000059100000000",
		"000000007000050060057000824000005782090000600008070000400009050015068200009000408",
		"000639710000000340900000000603700008000081000000500000005370600009040800700000100",
		"000000030000004060000090400002006000106300500097500004001005900049200007070010040",
		"000000003029003500800900006600000190500009000001600057000300000080000020176200300",
		"300000000901000000004701000080020073003050092000008001490500000100300007008000109",
		"012060000900200860005400120670004000401000090000820040096100000000090000004000700",
		"400000805030000000000700000020000060000080400000010000000603070500200000104000000",
		"520006000000000701300000000000400800600000050000000000041800000000030020008700000",
		"600000803040700000000000000000504070300200000106000000020000050000080600000010000",
		"480300000000000071020000000705000060000200800000000000001076000300000400000050000",
		"000014000030000200070000000000900030601000000000000080200000104000050600000708000" };

	bool C[81][81];
	vector<int> assignment;
	vector <int> domain[81];
	string table[20];  //for display purposes
	fillConst(C);
	// getSudokuCSP(puzzles[0], assignment, domain);
	// getSudokuBoard(table);
	// fillDisplayBoard(table, assignment);
	// cout << "The puzzle:\n";
	// displayBoard(table);
	// cout << endl << "The CSP domain:\n";
	// displaySudokuCSP(assignment, domain);
    
	vector<long> BT, BT_MRV, BT_AC3, BT_MRV_AC3;

    // BackTrack computation
    cout << "==========Testing the BT...\n";
	for (int i = 0; i < 20; i++)
	{
		// system("cls");
		getSudokuCSP(puzzles[i], assignment, domain);
		getSudokuBoard(table);
		fillDisplayBoard(table, assignment);
		cout << "The puzzle#: " << i << "~~ took [";
		// displayBoard(table);
		int count = 0;
		for (int i = 0; i < 81; i++)
			if (assignment[i] > 0)
				count++;

        auto start = high_resolution_clock::now();
		vector<int> result = backtrackCSP(assignment, count, domain, C);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start); 
		BT.push_back(duration.count());
        cout << duration.count() << " ms] to solve" << endl;
		fillDisplayBoard(table, result);
		// displayBoard(table);
		// system("pause");
	}

	long sum = 0;
	double avg = 0.0;

	cout << "Backtrack average time: ";
	for (long ms: BT) sum += ms; avg = sum / 20.0;
	cout << avg << endl; sum = 0; avg = 0.0;

	// BackTrack_MRV computation
    cout << "==========Testing the BT_MRV...\n";
	for (int i = 0; i < 20; i++)
	{
		// system("cls");
		getSudokuCSP(puzzles[i], assignment, domain);
		getSudokuBoard(table);
		fillDisplayBoard(table, assignment);
		cout << "The puzzle#: " << i << "~~ took [";
		// displayBoard(table);
		int count = 0;
		for (int i = 0; i < 81; i++)
			if (assignment[i] > 0)
				count++;

        auto start = high_resolution_clock::now();
		vector<int> result = backtrackCSP_MRV(assignment, count, domain, C);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start); 
		BT_MRV.push_back(duration.count());
        cout << duration.count() << " ms] to solve" << endl;
		fillDisplayBoard(table, result);
		// displayBoard(table);
		// system("pause");
	}

	cout << "Backtrack_MRV average time: ";
	for (long ms: BT_MRV) sum += ms; avg = sum / 20.0;
	cout << avg << endl; sum = 0; avg = 0.0;

    // BackTrack + AC3 computation
    cout << "==========Testing the BT_AC3...\n";
	for (int i = 0; i < 20; i++)
	{
		// system("cls");
		getSudokuCSP(puzzles[i], assignment, domain);
		getSudokuBoard(table);
		fillDisplayBoard(table, assignment);
		cout << "The puzzle#: " << i << "~~ took [";
		// displayBoard(table);
        AC3(domain, C);
		int count = 0;
		for (int i = 0; i < 81; i++)
			if (assignment[i] > 0)
				count++;

        auto start = high_resolution_clock::now();
		vector<int> result = backtrackCSP(assignment, count, domain, C);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start); 
		BT_AC3.push_back(duration.count());
        cout << duration.count() << " ms] to solve" << endl;

		fillDisplayBoard(table, result);
		// displayBoard(table);
		// system("pause");
	}

	cout << "Backtrack_AC3 average time: ";
	for (long ms: BT_AC3) sum += ms; avg = sum / 20.0;
	cout << avg << endl; sum = 0; avg = 0.0;

	// BackTrack_MRV + AC3 computation
    cout << "==========Testing the BT_MRV_AC3...\n";
	for (int i = 0; i < 20; i++)
	{
		// system("cls");
		getSudokuCSP(puzzles[i], assignment, domain);
		getSudokuBoard(table);
		fillDisplayBoard(table, assignment);
		cout << "The puzzle#: " << i << "~~ took [";
		// displayBoard(table);
        AC3(domain, C);
		int count = 0;
		for (int i = 0; i < 81; i++)
			if (assignment[i] > 0)
				count++;

        auto start = high_resolution_clock::now();
		vector<int> result = backtrackCSP_MRV(assignment, count, domain, C);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start); 
		BT_MRV_AC3.push_back(duration.count());
        cout << duration.count() << " ms] to solve" << endl;

		fillDisplayBoard(table, result);
		// displayBoard(table);
		// system("pause");
	}

	cout << "Backtrack_MRV_AC3 average time: ";
	for (long ms: BT_MRV_AC3) sum += ms; avg = sum / 20.0;
	cout << avg << endl; sum = 0; avg = 0.0;

	// Print Result of BT, BT_MRV, BT_AC3, BT_MRV_AC3
	cout << "==============FINAL RESULT==============" << endl;
	cout << "Backtrack average time: ";
	for (long ms: BT) sum += ms; avg = sum / 20.0;
	cout << avg << endl; sum = 0; avg = 0.0;
	cout << "Backtrack_MRV average time: ";
	for (long ms: BT_MRV) sum += ms; avg = sum / 20.0;
	cout << avg << endl; sum = 0; avg = 0.0;
	cout << "Backtrack_AC3 average time: ";
	for (long ms: BT_AC3) sum += ms; avg = sum / 20.0;
	cout << avg << endl; sum = 0; avg = 0.0;
	cout << "Backtrack_MRV_AC3 average time: ";
	for (long ms: BT_MRV_AC3) sum += ms; avg = sum / 20.0;
	cout << avg << endl; sum = 0; avg = 0.0;
	cout << "========================================" << endl;

	system("pause");
	return 0;
}

////////Drawing functions////////////////////////////

void getSudokuBoard(string table[])
{
	string table1[] = {
	"+===========+===========+===========+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"+---*---*---+---*---*---+---*---*---+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"+---*---*---+---*---*---+---*---*---+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"+===========+===========+===========+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"+---*---*---+---*---*---+---*---*---+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"+---*---*---+---*---*---+---*---*---+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"+===========+===========+===========+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"+---*---*---+---*---*---+---*---*---+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"+---*---*---+---*---*---+---*---*---+",
	"] 0 | 0 | 0 ] 0 | 0 | 0 ] 0 | 0 | 0 ]",
	"=====================================", };

	for (int i = 0; i < 19; i++)
	{
		table[i] = table1[i];
		for (int j = 0; j < table[i].length(); j++)
		{
			switch (table[i][j])
			{
			case '+': table[i][j] = char(219); break;
			case ']': table[i][j] = char(219); break;
			case '=': table[i][j] = char(219); break;
			case '-': table[i][j] = char(196); break;
			case '|': table[i][j] = char(179); break;
			case '*': table[i][j] = char(197); break;
			case '0': table[i][j] = ' '; break;
			}

		}
	}
}

void displayBoard(string table[])
{
	for (int i = 0; i < 19; i++)
	{
		cout << table[i] << endl;
	}
}

void fillDisplayBoard(string board[], int sudokuM[][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			if (sudokuM[i][j] > 0)
				board[1 + 2 * i][2 + 4 * j] = char(sudokuM[i][j] + '0');
		}
}

void fillDisplayBoard(string board[], vector<int> assignment)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			if (assignment[i * 9 + j] > 0)
				board[1 + 2 * i][2 + 4 * j] = char(assignment[i * 9 + j] + '0');
		}
}


void displayBoard(string table[], int T[][9])
{
	//https://en.wikipedia.org/wiki/ANSI_escape_code
	char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
	char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < table[i].length(); j++)
		{
			if (i < 18 && T[i / 2][j / 4]>0 && j % 4 == 2 && i % 2 == 1)
				cout << blue << table[i][j] << normal;
			else
				cout << table[i][j];

		}
		cout << endl;
	}
}

void displaySudokuCSP(vector<int> assignment, vector<int> domain[81])
{
	string s1 = " . . .  . . .  . . .    . . .  . . .  . . .    . . .  . . .  . . .";
	string s2 = "                                                                  ";
	string board[] = { s1,s1,s1,s2,s1,s1,s1,s2,s1,s1,s1,s2,s2, s1,s1,s1,s2,s1,s1,s1,s2,s1,s1,s1,s2,s2, s1,s1,s1,s2,s1,s1,s1,s2,s1,s1,s1, };
	for (int a = 0; a < 81; a++)
	{
		int i = a / 9, j = a % 9;
		if (assignment[a] > 0.5)
		{
			int v = assignment[a] - 1;
			int r1 = v / 3, c1 = v % 3;
			int x = i * 4 + r1 + i / 3;
			int y = j * 7 + c1 * 2 + j / 3 * 2 + 1;
			board[x][y] = char(v + '1');

		}
		else
		{
			for (int k = 0; k < domain[a].size(); k++)
			{
				int v = domain[a][k] - 1;
				int r1 = v / 3, c1 = v % 3;
				int x = i * 4 + r1 + i / 3;
				int y = j * 7 + c1 * 2 + j / 3 * 2 + 1;
				board[x][y] = char(v + '1');

			}
		}
	}
	for (int i = 0; i < 37; i++)
		cout << board[i] << endl;
}

void displaySudokuSimple(vector<int> assignment)
{
	string s1 = " . . .  . . .  . . .";
	string s2 = "                    ";
	string board[] = { s1,s1,s1,s2,s1,s1,s1,s2,s1,s1,s1 };
	for (int a = 0; a < 81; a++)
	{
		int i = a / 9, j = a % 9;
		int x = i + i / 3;
		int y = j * 2 + j / 3 + 1;

		if (assignment[a] > 0.5)
		{
			int v = assignment[a];
			board[x][y] = char(v + '0');
		}
	}
	for (int i = 0; i < 11; i++)
		cout << board[i] << endl;
}

//////////////////////////////////////////////////////

/////Helper Functions///////////////////////////////////
void fillConst(bool C[81][81])
{
	for (int i = 0; i < 81; i++)
		for (int j = 0; j < 81; j++)
			C[i][j] = false;

	for (int a = 0; a < 9; a++)
	{
		for (int b = 0; b < 9; b++)
		{
			int z = 9 * a + b;
			for (int i = 0; i < 9; i++)
			{
				int z1 = 9 * i + b;  //same column
				int z2 = 9 * a + i;  //same row
				if (z != z1)
					C[z][z1] = true;
				if (z != z2)
					C[z][z2] = true;
			}
			int r = a / 3, c = b / 3;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					int z3 = 9 * (3 * r + i) + (3 * c + j);
					if (z != z3)
						C[z][z3] = true;  //same cell

				}
		}

	}
}

void getSudokuCSP(string puzzle, vector<int>& assignment, vector<int> domain[81])
{
	vector<int>  d = { 1,2,3,4,5,6,7,8,9 };
	vector<int> assignment2(81, 0);

	for (int a = 0; a < 81; a++)
	{
		int v = int(puzzle[a] - '0');
		assignment2[a] = v;
		domain[a].clear();
		if (v > 0)
			domain[a].push_back(v);
		else
			domain[a] = d;
	}
	assignment = assignment2;
}

////////////////////////////////////////////////////////


//Base bactrack implementation
vector<int> backtrackCSP(vector<int> assignment, int count, vector<int> domain[81], const bool C[81][81])
{
	vector<int> result;
	if (count >= 81) //if assignment complete
		return assignment;
	//pick the next unassigned variable
	int r = 0;
	while (assignment[r] > 0)
		r++;
	int n = domain[r].size();
	for (int i = 0; i < n; i++)
	{
		int value = domain[r][i];  //pick the next value

		//check for if value is consitent with the past
		bool consistent = true;
		for (int j = 0; j < 81; j++)
			if (j != r && C[r][j] && assignment[j] == value)
			{
				consistent = false;
				break;
			}
		if (consistent)
		{
			assignment[r] = value;
			result = backtrackCSP(assignment, count + 1, domain, C);
			if (result.size() > 0)
				return result;
			assignment[r] = 0;
		}
	}
	return result;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//To be implemented by the students

bool AC3(vector<int> domain[81], const bool C[81][81])
{
	queue<arcType> arcs;
	for (int xi = 0; xi < 81; xi++) { // Initialize arcType queue that satisfies C[xi][xj]
		for (int xj = 0; xj < 81; xj++) {
			if (C[xi][xj]) {
				arcType tmpArc = {xi, xj};
				arcs.push(tmpArc);
			}
		}
	}

	// Neighbor index calculation factors
	/*------------------------- general
	(xi-10)[0] | (xi-9) [1] | (xi-8)  [2]
	(xi-1) [3] |     xi     | (xi+1)  [4]
	(xi+8) [5] | (xi+9) [6] | (xi+10) [7]
	---------------------------*/
	int neighbor_idx_calc[] = {-10, -9, -8, -1, 1, 8, 9, 10};

	while (!arcs.empty()) {
		// Remove-first(queue)
		arcType first = arcs.front();
		arcs.pop();

		// Determine if first.source is left-most or right-most index
		char pos = 'G'; // L: leftmost, R: rightmost, G: general
		if (first.source%9) pos='L';
		if ((first.source+1)%9==0) pos='R';

		if (revise(first.source, first.destination, domain, C)) { // if revised
			if (domain[first.source].empty()) return false; // if domain is empty, no solution
			
			// Get neighboring index of source arc (xi)
			for (int i = 0; i < 8; i ++) { // total of 8 neighbors
				if (pos='L') // skip left neighbors
					if (i == 0 || i == 3 || i == 5) continue;
				if (pos='R') // skip right neighbors
					if (i == 2 || i == 4 || i == 7) continue;

				int xk = first.source + neighbor_idx_calc[i];
				if (xk < 0) continue; // skip neighbor less than row 1
				else if (xk > 80) continue; // skip neighbor more than last row
				else if (xk == first.destination) continue; // xk == xj
				else {
					arcType newArc = {xk, first.source}; // {xk, xi}
					arcs.push(newArc); // add (xk, xi) to queue
				}
			}
		}
	}
	return true;
}

bool revise(int xi, int xj, vector<int> domain[81], const bool C[81][81])
{
	bool revised = false;

	if (C[xi][xj]) { // If constraint exists between two cell, go through revision check
		for (int i_idx = 0; i_idx < domain[xi].size(); i_idx++) { // Loop through Domain of (xi)
			bool satisfied = false; // Initially unsatisfied

			for (int j_idx = 0; j_idx < domain[xj].size(); j_idx++) // Loop through Domain of (xj)
				if (domain[xi][i_idx] != domain[xj][j_idx]) satisfied = true; // some value satisfies constraint
			
			if (!satisfied) { // if no value in domain[xj] satisfy constraint with value domain[xi][i_dix]
				domain[xi].erase(domain[xi].begin() + i_idx); // remove unsatisfied value domain[xi][i_dix]
				revised = true;
			}
		}
	}
	return revised;
}


vector<int> backtrackCSP_MRV(vector<int> assignment, int count, vector<int> domain[81], const bool C[81][81])
{
	vector<int> result;
	if (count >= 81) //if assignment complete
		return assignment;
	//pick the next unassigned variable
	int r = 0;
	vector<int> emptyIndex; // vector of empty indexes
	vector<int> domainSize; // vector of domain size
	for (int r = 0; r < 81; r++) { // find all empty index
		if (assignment[r] == 0) {
			emptyIndex.push_back(r);
			domainSize.push_back(domain[r].size());
		}
	}
	r = emptyIndex[distance(domainSize.begin(),min_element(domainSize.begin(), domainSize.end()))]; // pick the most contrained domain
	int n = domain[r].size();
	for (int i = 0; i < n; i++)
	{
		int value = domain[r][i];  //pick the next value

		//check for if value is consitent with the past
		bool consistent = true;
		for (int j = 0; j < 81; j++)
			if (j != r && C[r][j] && assignment[j] == value)
			{
				consistent = false;
				break;
			}
		if (consistent)
		{
			assignment[r] = value;
			result = backtrackCSP(assignment, count + 1, domain, C);
			if (result.size() > 0)
				return result;
			assignment[r] = 0;
		}
	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

