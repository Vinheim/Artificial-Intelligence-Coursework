#ifndef WORD_NODE_H
#define WORD_NODE_H

#include <iostream>

/**
 * This class contains as member data the word to be analyzed as well as its heuristic score value.
 * This value determines where it falls into the priority queue fringe.
 * If a WordNode matches more letters in the target node than a different WordNode, then the first has a higher heuristic value and will be explored first in the fringe.
 */
class WordNode
{
private:
	std::string word;
	int heuristic;
public:
	/**
	 * Default Constructor
	 */
	WordNode();
	
	WordNode(std::string w);

	/**
	 * Multi-Argument Constructor
	 */
	WordNode(std::string w, int h);

	std::string getWord() const;
	int getHeuristic() const;
	void setWord(std::string w);
	void setHeuristic(int h);

	/**
	 * Calculate the heuristic value for a WordNode transformation for determination of placement location in a priority queue fringe.
	 * @param targetWord : The word which we are looking for and the word which we are comparing against to calculate the heuristic value.
	 * Set heuristic equal to a value representative of how close this WordNode matches up to the targetWord.
	 */
	void calculateHeuristic(const std::string& targetWord);
	void calculateHeuristic(const WordNode& targetWord);

	bool operator<(const WordNode& rhs) const;
	std::ostream& display(std::ostream& outs) const;
};

inline
std::string WordNode::getWord() const 
{
	return word;
}

inline
int WordNode::getHeuristic() const
{
	return heuristic;
}

inline
void WordNode::setWord(std::string w)
{
	word = w;
}

inline
void WordNode::setHeuristic(int h)
{
	heuristic = h;
}

inline
bool WordNode::operator<(const WordNode& rhs) const
{
	return (this->heuristic < rhs.heuristic);
}

inline
std::ostream& operator<<(std::ostream& outs, const WordNode& print)
{
	print.display(outs);
	return outs;
}

#endif