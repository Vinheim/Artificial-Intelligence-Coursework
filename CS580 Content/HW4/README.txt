Compilation
-----------
To compile this program's code from the ODU Linux terminals, give the following command.
g++ -g -c PerfectSolver.cpp
g++ -g -o Connect4 PerfectSolver.o

From here you can execute the program and test your skills against the MiniMax-powered AI by giving the following command.
./Connect4 on Linux
Connect4.exe on Windows

Analysis
--------
Because Connect 4 is a perfect knowledge game and the AI. named MAX, is allowed to go first, the player is guaranteed to lose. All possible positions will be evaluated by the MiniMax variation function Negamax and the best position at any time and on any turn will always be chosen by MAX. It is not possible for the player to win given that they are starting as the second player to take a turn.

Initial Board State
-------------------

	1       2       3       4       5       6       7
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |   O   |       |       |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
Where would you like to play? (Enter Column Number)

Example Terminal Board State
----------------------------

    1       2       3       4       5       6       7
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |   O   |   X   |       |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |   X   |   O   |   X   |       |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |   O   |   O   |   O   |   O   |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|       |       |       |   O   |   X   |   O   |   X   |
|       |       |       |       |       |       |       |
---------------------------------------------------------
|       |       |       |       |       |       |       |
|   X   |   X   |       |   O   |   X   |   O   |   X   |
|       |       |       |       |       |       |       |
---------------------------------------------------------
Player 1 WON !
