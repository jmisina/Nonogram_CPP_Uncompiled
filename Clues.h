#pragma once
#include <vector>
#include "board.h"

class Clues
{
private:
	std::vector<std::vector<short int>> horizontalClues;
	int cluesWidth;
public:
	Clues(Board analyzedBoard = Board());
	~Clues();
	std::vector<std::vector<short int>> getClues() const;
	int getClue(int x, int y) const;
	int getCluesWidth() const;
	std::vector<short int> analyzeVector(std::vector<short int> analyzed);

};

