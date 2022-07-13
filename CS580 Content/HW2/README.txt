Compilation and Executable Creation
-----------------------------------
From the ODU Linux servers, run the following commands.
g++ -g -c HillClimbingSearch.cpp nQueens_GeneticAlgorithm.cpp nQueens_HillClimbing.cpp
g++ -g -o HillClimbingSearch HillClimbingSearch.o
g++ -g -o NQUEENS_GENALG nQueens_GeneticAlgorithm.o
g++ -g -o NQUEENS_HILLCLIMB nQueens_HillClimbing.o

And from here you will have produced three executable files: HillClimbingSearch, NQUEENS_GENALG, NQUEENS_HILLCLIMB

Execution
---------
./HillClimbingSearch
./NQUEENS_GENALG
./NQUEENS_HILLCLIMB

Any information that must be provided by the programmer will be done during program execution.