Heesang Mark Whang

CSCI 440: Artificial Intelligence

Assignment #4

10/23/2019

1. **(5 points)** You get full points if either
   * all the rest of the assignment elements work or ...
   * you spend a considerable amount of time working on trying to get the assignment working
     * Record the approximate amount of time working on the assignment
     * Detail the parts you struggled with and your attempts to get them working

2. Implement the minmax and alpha beta algorithms to play TicTacToe. Consider the TicTacToe board. We can label each position 0 to 8 as shown below.

   |   0   |   1   |   2   |
   | :---: | :---: | :---: |
   | **3** | **4** | **5** |
   | **6** | **7** | **8** |

   Then the state of the board is given by a string S, where S[i]='x' or 'X' if the first player has made that move and, S[i] = 'o' or 'O' if the second player has made that move, and S[i] = ' ' or '.' otherwise. Player 1(x) is the maximizing player and Player 2(o) is the minimizing one.

   * a) **(1 point)** Implement a function that given a state of the board will return

     * 1 if it is a wining position for player 1(x)
     * -1 if it is a winning position for player 2(o)
     * 0 if the position is not a winning position for either side yet

     ```C++
     int getAttackScore(int Q[]);
     ```

     

   * b) **(2 points)** The minmax function has already implemented, but in order for it to work, you need to implement the minvalue and maxvalue functions (pseudocode in the textbook page 166).

     ```C++
     double minvalue(string state);
     double maxvalue(string state);
     ```

     

   * c) **(2 points)** Implement the alpha-beta algorithm (pseudocode in the textbook page 170). 

     ```C++
     int minmaxAB(string state, bool xturn);
     ```

     