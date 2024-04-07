#pragma once
#include <vector>
#include <string>
#include "board.h"
#include "clues.h"
#include <SFML/Graphics.hpp>


class Level
{
private:
	std::string levelName;
	Board levelBoard;
	Clues xAxisClues;
	Clues yAxisClues;
	sf::Vector2f cellSize;
	sf::Vector2f renderStartingPoint;

public:
	Level(std::string levelNewName, Board boardToLoad);
	Level(std::string lvName = "Powitanie");
	~Level();
	std::string getLevelName();
	Board getLevelBoard();
	Clues getXAxisClues();
	Clues getYAxisClues();
	sf::Vector2f getCellSize();
	sf::Vector2f getRenderStartingPoint();
	void setRenderStartingPointX(float x);
	void setRenderStartingPointY(float y);
	void saveLevel();
	void drawLevel(sf::RenderWindow& window);
	unsigned int analyzeLevel();
	void boardEvents(sf::RenderWindow& window, sf::Event event);
};

