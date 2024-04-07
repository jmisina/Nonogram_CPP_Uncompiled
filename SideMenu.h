#pragma once
#include "SFML/Graphics.hpp"
#include <filesystem>
#include <string>
#include "level.h"
#include <vector>
#include "MenuStatus.h"


class SideMenu
{
private:
	float menuOffset;
	float menuWidth;
	float menuHeight;
	int mistakeCounter;
	int levelListSize;
	int levelSelection[2];
	std::string selectedNewLevel;
	std::string loadedLevelName;
	std::string lvCreateXSize;
	std::string lvCreateYSize;
	std::string lvCreateName;
public:
	struct MenuStatus currentStatus;

	float getMenuWidth() const;
	std::string getSelectedNewLevel() const;
	std::string getLoadedLevelName() const;
	std::string getNewLevelXSize() const;
	std::string getNewLevelYSize() const;
	std::string getNewLevelName() const;

	void setMistakeCounter(unsigned int mistakes);

	SideMenu(Level loadedLevel);
	SideMenu();
	void renderMenu(sf::RenderWindow& window);
	void menuEvents(sf::RenderWindow& window, sf::Event event);
	void renderLevelSelection(sf::RenderWindow& window, bool loadLevelClicked);
	std::vector<std::string> loadLevelList();


};



