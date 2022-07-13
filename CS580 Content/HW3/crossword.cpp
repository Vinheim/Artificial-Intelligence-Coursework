#include <iostream>
#include <list>
#include <stack>
#include <fstream>

#include "board.h"

using namespace std;

bool backtrackingSearch(board &seed, list<string> &dictionary);
bool recursiveBacktracking(board &cword, list<string> &dictionary);
bool notTried(string word, list<string> &tried);
void fillDict(list<string> &dictionary);

int main() {

	list<string> dictionary;

	fillDict(dictionary);

	cout << "Original Board!\n";
	cout << "+---+---+---+---+---+\n";
	cout << "| 1 |   | 2 |   | 3 |\n";
	cout << "+---+---+---+---+---+\n";
	cout << "| # | # |   | # |   |\n";
	cout << "+---+---+---+---+---+\n";
	cout << "| # | 4 |   | 5 |   |\n";
	cout << "+---+---+---+---+---+\n";
	cout << "| 6 | # | 7 |   |   |\n";
	cout << "+---+---+---+---+---+\n";
	cout << "| 8 |   |   |   |   |\n";
	cout << "+---+---+---+---+---+\n";
	cout << "|   | # | # |   | # |\n";
	cout << "+---+---+---+---+---+\n\n\n";

	board seed;
	bool check = true;
	
	check = recursiveBacktracking(seed, dictionary);
	
	cout << "Solution!\n";
	seed.display();

	return 0;
}

bool backtrackingSearch(board &seed, list<string> &dictionary) {
	return recursiveBacktracking(seed, dictionary);
}

bool recursiveBacktracking(board &cword, list<string> &dictionary) {
	list<string>::iterator ditr;
	//cword.display();
	if(cword.isComplete()){
		return true;
	}
	ditr = dictionary.begin();
	while(ditr != dictionary.end()){
		list<string> tried;
		if(cword.consistent(*ditr) && notTried((*ditr), tried)){
			cword.addWord(*ditr);
			bool result = recursiveBacktracking(cword, dictionary);
			if(result != false){
				cout << "Match Found!\n";
				return result;
			}
			cword.deleteWord();
			tried.push_back(*ditr);
		}
		ditr++;
	}
	return false;
}

bool notTried(string word, list<string> &tried) {
	list<string>::iterator titr;
	titr = tried.begin();
	while(titr != tried.end()){
		if((*titr) == word){
			return false;
		}
	}
	return true;
}

void fillDict(list<string> &dictionary) {
	ifstream inFile;
	
	inFile.open("words.txt");

	while(inFile){
        string tempString;
        inFile >> tempString;
		dictionary.push_back(tempString);
	}
	
	inFile.close();
	
	dictionary.unique();
}