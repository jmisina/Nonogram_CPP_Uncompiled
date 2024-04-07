#include "board.h"
#include <SFML/Graphics.hpp>

Board::Board(int X, int Y, std::vector<std::vector<short int>> board)
{
    gridSizeX = X;
    gridSizeY = Y;

    levelBoard = board;

    playingBoard = std::vector<std::vector<short int>>(X, std::vector<short int>(Y, 0));
}

Board::~Board(){}

int Board::getGridSizeX() const {
    return gridSizeX;
}
int Board::getGridSizeY() const {
    return gridSizeY;
}

std::vector<std::vector<short int>> Board::getPlayingBoard() const {
    return playingBoard;
}

std::vector<std::vector<short int>> Board::getLevelBoard() const {
    return levelBoard;
}

void Board::setPlayingBoardCell(int x, int y, int val) {
    playingBoard[x][y] = val;
}


void Board::drawPlayingBoard(sf::RenderWindow& window, const sf::Vector2f& cellSize, sf::Vector2f& renderPosition) {

    sf::Texture texture;
    if (!texture.loadFromFile("textures/negative-cell.png")) {
        return;
    }

    for (int i = 0; i < gridSizeX; ++i) {
        for (int j = 0; j < gridSizeY; ++j) {
            sf::RectangleShape cell(cellSize);
            cell.setPosition(renderPosition.x +((1+i) * cellSize.x), renderPosition.y + ((1+j) * cellSize.y));
            if (playingBoard[i][j] == 1) {
                cell.setFillColor(sf::Color::Color(48,48,48));
            }
            else if (playingBoard[i][j] == 2) {
                cell.setTexture(&texture);

            }
            else {
                cell.setFillColor(sf::Color::White);
            }
            cell.setOutlineColor(sf::Color::Black); 
            cell.setOutlineThickness(1.0f); 
            window.draw(cell);
        }
    }
}

Board Board::transpose()
{
    std::vector<std::vector<short int>> transposedBoard(gridSizeY, std::vector<short int>(this->gridSizeX, 0));

    for (int i = 0; i < this->gridSizeX; ++i) {
        for (int j = 0; j < this->gridSizeY; ++j) {
            transposedBoard[j][i] = this->levelBoard[i][j];
        }
    }
    Board transposed(gridSizeY, gridSizeX, transposedBoard);
    return transposed;
}


