#include "clues.h"


std::vector<short int> Clues::analyzeVector(std::vector<short int> analyzedVector)
{
	int counter = 0;

	std::vector<short int> rowClues;
	int i = 0;

	for (i; i < analyzedVector.size(); i++)
	{
		switch (analyzedVector[i])
		{
		case 1:
			counter++;
			break;
		case 0:
			if (counter > 0) {
				rowClues.push_back(counter);
				counter = 0;
			}
			break;
		default:
			break;
		}
	}
	if (counter > 0 && counter <= analyzedVector.size()) {
		rowClues.push_back(counter);
		counter = 0;
	}

	return rowClues;
}

Clues::Clues(Board analyzedBoard)
{	
	int sizeMeasure = 0;
	std::vector<std::vector<short int>> temp;

	for (int i = 0; i < analyzedBoard.getGridSizeX(); i++) {
			temp.push_back(analyzeVector(analyzedBoard.getLevelBoard()[i]));
	}
	horizontalClues = temp;
	
	for (int i = 0; i < horizontalClues.size(); i++) {
		if (horizontalClues[i].size() > sizeMeasure)
			sizeMeasure = horizontalClues[i].size();
	}
	cluesWidth = sizeMeasure;
}


Clues::~Clues() {}


std::vector<std::vector<short int>> Clues::getClues() const {
	return horizontalClues;
}

int Clues::getCluesWidth() const{
	return cluesWidth;
}

int Clues::getClue(int x, int y) const{
	return horizontalClues[x][y];
}

