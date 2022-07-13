#include <fstream>   // Used to read words from Dictionary and store those relevant in Words text file.
#include <iostream>  // Used to print messages to console window.
#include <queue> 	 // FIFO data structure utilized in Breadth-First Search Algorithm.
#include <stack>	 // FILO data structure utilized in Depth-First Search Algorithm.
#include <list>		 // Used to store words read from Dictionary.txt.
#include <algorithm> // Contains find function to be used when identifying new paths.
using namespace std;

const char alphabet[26] = {
							'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
			    		  	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
			    		  };

/**
 * Prints information regarding the program and what search algorithm is employed in implementation of the Word Ladder.
 */
void programmerInfo();

/**
 * Upon determining the length of the initial and target words, n, prune the dictionary such that a new version of it is created, containing only words of n length.
 * This will help to speed up any searches through the dictionary.
 */
void pruneDictionary(ifstream& inFile, list<string> * dictionary, int * wordLength);

/**
 * Store into an output file the words located in the pruned dictionary.
 */
void storeWords(ofstream& outFile, list<string> * dictionary);

/**
 * Play the word game.
 * @return : A list of all word transformations explored whilst playing the game.
 */
list<string>* playWordGame(list<string> * dictionary, string& initialWord, string& targetWord);

/**
 * Main Function
 * Precondition: argc == 3
 * Precondition: argv contains the program invocation followed by the initial word and target word, in the listed order.
 * Precondition: Both the initial state word and the goal state word must be unique words of the same length, n.
 */
int main(int argc, char* argv[])
{
	/// Print to the console window information regarding the student programmer and the intentions of this program. 
	programmerInfo();

	string initialWord = argv[1];
	string targetWord  = argv[2];

	if(initialWord.size() != targetWord.size())
	{
		cerr << "The words which you entered are of different lengths, and this cannot be so if the Word Ladder game is to function properly. Please try again." << endl;
		return 0;
	}

	int * wordLength = new int(initialWord.size());
	
	/**
	 * cerr << "Initial Word: " << initialWord << endl
	 *	    << "Target Word: "  << targetWord  << endl;
	 */

	/// Store every word of length wordLength from Dictionary.txt into a data collection list dictionary.
	ifstream inFile;
	list<string> * dictionary = new list<string>();
	pruneDictionary(inFile, dictionary, wordLength);

	if(find(dictionary->begin(), dictionary->end(), initialWord) == dictionary->end())
	{
		cerr << "Your choice for the initial word does not exist within the dictionary. Please enter a new word and try again." << endl;
		return 0;
	}

	if(find(dictionary->begin(), dictionary->end(), targetWord) == dictionary->end())
	{
		cerr << "Your choice for the goal word does not exist within the dictionary. Please enter a new word and try again." << endl;
		return 0;
	}

	/// Store the words from the data collection list dictionary into an output file.
	ofstream outFile;
	storeWords(outFile, dictionary);

	list<string> * exploredWords = playWordGame(dictionary, initialWord, targetWord);
	cout << "Explored Words: " << endl;
	list<string>::iterator itr =  exploredWords->begin();
	while(itr != exploredWords->end())
	{
		cout << *(itr) << " ---> ";
		itr++;
	}
	cout << targetWord;

	delete exploredWords;
	delete wordLength;
	return 0;
}

void programmerInfo()
{
	cout << "******************************************" << '\n'
		 << "* Student Name: John Hessefort           *" << '\n'
		 << "* University ID Number: 01046558         *" << '\n'
		 << "* Due Date: 10/11/2018                   *" << '\n'
		 << "* Program Name: breadthFirstSearch       *" << '\n'
		 << "******************************************" << '\n'
		 << "* Program Description: Allow the user    *" << '\n'
		 << "* to play some kind of word ladder game  *" << '\n'
		 << "* wherein they select two words of the   *" << '\n'
		 << "* same length, n, to serve as the start  *" << '\n'
		 << "* and goal words, respectively. Through  *" << '\n'
		 << "* a series of transformations that       *" << '\n'
		 << "* change one letter per iteration, reach *" << '\n'
		 << "* the goal word from the initial word    *" << '\n'
		 << "* and record the first successful path.  *" << '\n'
		 << "* This version utilizes a breadth-first  *" << '\n'
		 << "* search algorithm to identify possible  *" << '\n'
		 << "* paths.                                 *" << '\n'
		 << "******************************************" << endl;
}

void pruneDictionary(ifstream& inFile, list<string> * dictionary, int * wordLength)
{
	string word;
	inFile.open("Dictionary.txt");
	while(!inFile.eof())
	{
		// Store only words which are of the same length as the initial and goal words.
		inFile >> word;
		int readWordLength = word.size();
		if(readWordLength == *(wordLength))
			dictionary->push_back(word);
	}
	inFile.close();
}

void storeWords(ofstream& outFile, list<string> * dictionary)
{
	outFile.open("PrunedDictionary.txt");
	for(string word : (*dictionary))
	{
		outFile << word << endl;
	}

	outFile.close();
}

list<string>* playWordGame(list<string> * dictionary, string& initialWord, string& targetWord)
{
	// As the Breadth-First Search Algorithm utilizes a FIFO structure, define an empty queue variable to represent the fringe.
	// Maintain a list of explored words so as to prevent infinite recursion. (I.E. - Goal -> Foal -> Goal, where Goal is the initial word.)
	list<string>  * exploredWords = new list<string>();
	queue<string> * fringe 		  = new queue<string>();
	fringe->push(initialWord);
	exploredWords->push_back(initialWord);

	// Create a local string variable to maintain the most current version of the initial word transformation.
	string currentWord = initialWord;
	int wordLength = currentWord.size();
	
	// While we have yet to discover a way to transform the initial word into the target word, continue to perform single-character transformations on the word.
	// exploredWords->push_back(currentWord);
	while(currentWord != targetWord)
	{
		// For each letter in the word, test to see if by changing the letter to one of the other 25 yields a valid word. If so, add it to the fringe.
		for(int i = 0; i < wordLength; i++)
		{
			char currentChar = currentWord[i];
			for(int j = 0; j < 26; j++)
			{
				// Change the ith letter of the current word transformation to be the jth letter of the alphabet if and only if the letters are not the same.
				// We do not want the new transformation to be the same word we began with.
				if(currentWord[i] != alphabet[j])
					currentWord[i] = alphabet[j];

				// If the word transformation can be found in the dictionary and is not already in the list of explored words, add it to the fringe of paths to be explored.
				auto foundInDictionary = find(dictionary->begin(), dictionary->end(), currentWord);
				if(foundInDictionary != dictionary->end())
				{
					auto foundInExplored = find(exploredWords->begin(), exploredWords->end(), currentWord);
					if(foundInExplored == exploredWords->end())
					{
						if(currentWord == targetWord)
						{
							exploredWords->push_back(currentWord);
							return exploredWords;
						}

						// The word exists in the dictionary and should be added to the fringe.
						fringe->push(*(foundInDictionary));
					}
				}
			}
			currentWord[i] = currentChar;
		}
		// If after each letter has been tested for this index we are left with a unique word, then add it to the list of explored words and remove it from the fringe.
		if(currentWord != initialWord)
			exploredWords->push_back(currentWord);

		fringe->pop();
		// Set the new current word to the next one in the fringe.
		currentWord = fringe->front();
	}
	if(currentWord == targetWord)
		cout << "GOAL ACHIEVED! YOU DEFEATED. Target Word transformation path found!" << endl;
	return exploredWords;                                                                                          
}