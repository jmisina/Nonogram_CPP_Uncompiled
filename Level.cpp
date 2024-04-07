#include "level.h"
#include <iostream>
#include <fstream>

short int initialTileStatus = 0;

Level::Level(std::string levelNewName, Board boardToLoad)
{
	levelName = levelNewName;
	levelBoard = boardToLoad;
	
	xAxisClues = Clues(boardToLoad);
	yAxisClues = Clues(boardToLoad.transpose());

	int biggerAxis = (levelBoard.getGridSizeX() + yAxisClues.getCluesWidth() > levelBoard.getGridSizeY() + xAxisClues.getCluesWidth()) ? levelBoard.getGridSizeX() + yAxisClues.getCluesWidth() : levelBoard.getGridSizeY() + xAxisClues.getCluesWidth();
	if ((levelBoard.getGridSizeX()+yAxisClues.getCluesWidth()) >= 24 || (levelBoard.getGridSizeY() + xAxisClues.getCluesWidth()) >= 24)
		cellSize = sf::Vector2f(625 / biggerAxis, 625 / biggerAxis);
	else
		cellSize = sf::Vector2f(25, 25);

	sf::Vector2f temp(yAxisClues.getCluesWidth() * cellSize.x, xAxisClues.getCluesWidth() * cellSize.y);
	renderStartingPoint = temp;
}


Level::Level(std::string lvName)
{
	std::ifstream loadedLevel("levels/" + lvName + ".nlv");
	std::string line;
	std::string lineElement;

	std::getline(loadedLevel, line);
	int levelXSize = std::stoi(line);
	std::getline(loadedLevel, line);
	int levelYSize = std::stoi(line);


	std::vector<std::vector<short int>> tempBoard(levelXSize, std::vector<short int>(levelYSize, 0));


	for (int i = 0; i < levelYSize; i++) {
		std::getline(loadedLevel, line);
		for (int j = 0; j < levelXSize; j++) {
			lineElement = line[j];
			tempBoard[j][i] = std::stoi(lineElement);
		}
		line = "";
	}

	Board loadedBoard(levelXSize, levelYSize, tempBoard);

	levelName = lvName;
	levelBoard = loadedBoard;
	int biggerAxis = (levelBoard.getGridSizeX() > levelBoard.getGridSizeY()) ? levelBoard.getGridSizeX() : levelBoard.getGridSizeY();
	if ((levelBoard.getGridSizeX() + yAxisClues.getCluesWidth()) >= 24 || (levelBoard.getGridSizeY() + xAxisClues.getCluesWidth()) >= 24)
		cellSize = sf::Vector2f(625 / biggerAxis, 625 / biggerAxis);
	else
		cellSize = sf::Vector2f(25, 25);
	xAxisClues = Clues(levelBoard);
	yAxisClues = Clues(levelBoard.transpose());

	sf::Vector2f temp(yAxisClues.getCluesWidth() * cellSize.x, xAxisClues.getCluesWidth() * cellSize.y);
	renderStartingPoint = temp;
}


Level::~Level() {
	levelBoard.~Board();
	xAxisClues.~Clues();
	yAxisClues.~Clues();
}

std::string Level::getLevelName() {
	return levelName;
}

Board Level::getLevelBoard() {
	return levelBoard;
}

Clues Level::getXAxisClues() {
	return xAxisClues;
}

Clues Level::getYAxisClues() {
	return yAxisClues;
}

sf::Vector2f Level::getCellSize() {
	return cellSize;
}

sf::Vector2f Level::getRenderStartingPoint() {
	return renderStartingPoint;
}

void Level::setRenderStartingPointX(float x) {
	renderStartingPoint.x = x;
	return;
}

void Level::setRenderStartingPointY(float y) {
	renderStartingPoint, y = y;
	return;
}


void Level::drawLevel(sf::RenderWindow& window) {


	sf::Font font;
	if (!font.loadFromFile("fonts/Montserrat.otf"))
	{
		return;
	}
	sf::Text Text;
	Text.setFont(font);
	Text.setFillColor(sf::Color::Black);
	Text.setCharacterSize(this->cellSize.x - 4);

	sf::Vector2f fillerSize(window.getSize().x, window.getSize().y);
	sf::RectangleShape filler(fillerSize);
	filler.setFillColor(sf::Color::Color(240, 240, 240));
	window.draw(filler);


	for (int i = 0; i < xAxisClues.getClues().size(); i++) {
		for (int j = 0; j < xAxisClues.getClues()[i].size(); j++) {
			if (xAxisClues.getClue(i,j)> 0 ) {
				short int offset = xAxisClues.getCluesWidth() - xAxisClues.getClues()[i].size();
				Text.setString(std::to_string(xAxisClues.getClue(i,j)));
				Text.setPosition(this->renderStartingPoint.x + 5 + ((1+i) * this->cellSize.x),offset*cellSize.y + (this->renderStartingPoint.y - (this->xAxisClues.getCluesWidth()*this->cellSize.y)) + ((1+j) * cellSize.y) + 2);
				window.draw(Text);
			}
		}
	}

	for (int i = 0; i < yAxisClues.getClues().size(); i ++) {
		for (int j = 0; j < yAxisClues.getClues()[i].size(); j ++) {
			if (this->yAxisClues.getClue(i,j) > 0 ) {
				short int offset = yAxisClues.getCluesWidth() - yAxisClues.getClues()[i].size();
				Text.setString(std::to_string(yAxisClues.getClue(i,j)));
				Text.setPosition((offset * cellSize.x)+((1+j) * this->cellSize.x + 5 ), this->renderStartingPoint.y + ((1+i) * cellSize.y));
				window.draw(Text);
			}
		}
	}

	this->levelBoard.drawPlayingBoard(window, this->cellSize, this->renderStartingPoint);

}


unsigned int Level::analyzeLevel() {
	std::vector<std::vector<int>> tempBoard(this->levelBoard.getGridSizeX(), std::vector<int>(this->levelBoard.getGridSizeY(), 0));
	int mistakeCounter = 0;

	for (int i = 0; i < this->levelBoard.getGridSizeX(); i++) {
		for (int j = 0; j < this->levelBoard.getGridSizeY(); j++) {
			if (this->levelBoard.getPlayingBoard()[i][j] == 2)
			{
				tempBoard[i][j] = 0;
			}
			else if (this->levelBoard.getPlayingBoard()[i][j] == 1)
			{
				tempBoard[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < this->levelBoard.getGridSizeX(); i++) {
		for (int j = 0; j < this->levelBoard.getGridSizeY(); j++) {
			if (tempBoard[i][j] != this->levelBoard.getLevelBoard()[i][j]) {
				mistakeCounter += 1;

			}
		}
	}
	return mistakeCounter;
}

void Level::boardEvents(sf::RenderWindow& window, sf::Event event) {
	sf::Vector2i mousePositionWindow = sf::Mouse::getPosition(window);
	sf::Vector2f mousePositionGrid = window.mapPixelToCoords(mousePositionWindow);
	sf::Vector2f lastMousePos(0, 0);

	
	if (event.type == sf::Event::MouseButtonPressed) {
		if (mousePositionGrid.x >= this->renderStartingPoint.x + (cellSize.x) && mousePositionGrid.y >= this->renderStartingPoint.y + cellSize.y &&
			mousePositionGrid.x < this->renderStartingPoint.x + ((1 + this->levelBoard.getGridSizeX()) * this->cellSize.x) &&
			mousePositionGrid.y < this->renderStartingPoint.y + ((1 + this->levelBoard.getGridSizeY()) * this->cellSize.y)) {
				int columnIndex = ((mousePositionGrid.x - this->renderStartingPoint.x) / this->cellSize.x) - 1;
				int rowIndex = ((mousePositionGrid.y - this->renderStartingPoint.y) / this->cellSize.y) - 1;
				initialTileStatus = levelBoard.getPlayingBoard()[columnIndex][rowIndex];
		}
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (mousePositionGrid.x >= this->renderStartingPoint.x + (cellSize.x) && mousePositionGrid.y >= this->renderStartingPoint.y + cellSize.y &&
			mousePositionGrid.x < this->renderStartingPoint.x + ((1+this->levelBoard.getGridSizeX()) * this->cellSize.x) &&
			mousePositionGrid.y < this->renderStartingPoint.y + ((1+this->levelBoard.getGridSizeY()) * this->cellSize.y)) {

				mousePositionWindow = sf::Mouse::getPosition(window);
				mousePositionGrid = window.mapPixelToCoords(mousePositionWindow);
				int columnIndex = ((mousePositionGrid.x - this->renderStartingPoint.x) / this->cellSize.x) - 1;
				int rowIndex = ((mousePositionGrid.y - this->renderStartingPoint.y) / this->cellSize.y) - 1;							
				if(initialTileStatus == 1 )
					levelBoard.setPlayingBoardCell(columnIndex, rowIndex, 0);
				else
					levelBoard.setPlayingBoardCell(columnIndex, rowIndex, 1);
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (mousePositionGrid.x >= this->renderStartingPoint.x + (cellSize.x) && mousePositionGrid.y >= this->renderStartingPoint.y + cellSize.y &&
			mousePositionGrid.x < this->renderStartingPoint.x + ((1 + this->levelBoard.getGridSizeX()) * this->cellSize.x) &&
			mousePositionGrid.y < this->renderStartingPoint.y + ((1 + this->levelBoard.getGridSizeY()) * this->cellSize.y)) {

			mousePositionWindow = sf::Mouse::getPosition(window);
			mousePositionGrid = window.mapPixelToCoords(mousePositionWindow);
			int columnIndex = ((mousePositionGrid.x - this->renderStartingPoint.x) / this->cellSize.x) - 1;
			int rowIndex = ((mousePositionGrid.y - this->renderStartingPoint.y) / this->cellSize.y) - 1;

			if (initialTileStatus == 2)
				levelBoard.setPlayingBoardCell(columnIndex, rowIndex, 0);
			else
				levelBoard.setPlayingBoardCell(columnIndex, rowIndex, 2);
		}
	}
}


void Level::saveLevel() {
	std::ofstream savedLevel("levels/" + this->levelName + ".nlv");
	std::string boardLine = "";

	savedLevel << std::to_string(this->levelBoard.getGridSizeX()) + "\n" + std::to_string(this->levelBoard.getGridSizeY()) + "\n";
	for (int i = 0; i < this->levelBoard.getGridSizeY(); i++) {
		for (int j = 0; j < this->levelBoard.getGridSizeX(); j++) {
			boardLine += std::to_string((levelBoard.getPlayingBoard()[j][i] == 1)?1:0);
		}
		savedLevel << boardLine + "\n";
		boardLine = "";
	}
	savedLevel.close();
}

