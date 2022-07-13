John Hessefort
UIN: 01046558

Compilation
-----------
Compile the code for this program from one of the ODU Linux servers by giving the following commands after entering the directory which contains the assignment source code files.

g++ -std=c++11 -g -c crossword.cpp
g++ -g -o crosspuzzle crossword.o

Execution
---------
From the same Linux terminal and within the same directory as where compilation and linking occurred type the following command:
./crosspuzzle
For the system to print out the amount of time the program took to run at the end, you can run the following command: 
time ./crosspuzzle