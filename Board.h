#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Board
{
private:
	int gridSizeX;
	int gridSizeY;
	std::vector<std::vector<short int>> levelBoard;
	std::vector<std::vector<short int>> playingBoard;

public:
	Board(int X = 1, int Y = 1, std::vector<std::vector<short int>> board = std::vector(1, std::vector<short int>(1, 0)));
	~Board();
	int getGridSizeX() const;
	int getGridSizeY() const;
	std::vector<std::vector<short int>> getPlayingBoard() const;
	void setPlayingBoardCell(int x, int y, int val);
	std::vector<std::vector<short int>> getLevelBoard() const;
	
	void drawPlayingBoard(sf::RenderWindow& window,  const sf::Vector2f& cellSize, sf::Vector2f& renderPosition);
	Board transpose();


};

