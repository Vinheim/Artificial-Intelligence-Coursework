#include "WordNode.h"

WordNode::WordNode()
	:word(""), heuristic(0) { }

WordNode::WordNode(std::string w)
	:word(w) { }

WordNode::WordNode(std::string w, int h)
	:word(w), heuristic(h) { }

void WordNode::calculateHeuristic(const std::string& targetWord)
{
	int h = 0;
	for(int i = 0; i < targetWord.length(); i++)
	{
		if(word[i] == targetWord[i])
		{
			h++;
		}
	}
	heuristic = h;
}

void WordNode::calculateHeuristic(const WordNode& targetWord)
{
	std::string goalWord = targetWord.getWord();

	int h = 0;
	for(int i = 0; i < goalWord.length(); i++)
	{
		if(word[i] == goalWord[i])
		{
			h++;
		}
	}
	heuristic = h;
}

std::ostream& WordNode::display(std::ostream& outs) const
{
	outs << "Word Transformation: " << word << std::endl;
	return outs;
}