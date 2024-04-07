#include <filesystem>
#include <iostream>
#include "sideMenu.h"

sf::Vector2f buttonSize(150, 50);
std::vector<std::string> levelList;

std::string saveLevelText = "  Zapisz Poziom";
bool lvCreateXSelected = false;
bool lvCreateYSelected = false;
bool lvCreateNameSelected = false;


SideMenu::SideMenu(Level loadedLevel) {

	menuOffset = (loadedLevel.getYAxisClues().getCluesWidth() + loadedLevel.getLevelBoard().getGridSizeX() + 2) * loadedLevel.getCellSize().x;
	loadedLevelName = loadedLevel.getLevelName();
	menuWidth = 200;
	menuHeight = (((2+loadedLevel.getXAxisClues().getClues().size() + loadedLevel.getRenderStartingPoint().y) * loadedLevel.getCellSize().y)>500) ? ((2 + loadedLevel.getXAxisClues().getClues().size() + loadedLevel.getRenderStartingPoint().y) * loadedLevel.getCellSize().y) : 500;
	currentStatus.loadLevelClicked = false;
	currentStatus.finishLevelClicked = false;
	currentStatus.lvCreateClicked = false;
	currentStatus.lvCreateConfirmed = false;
	currentStatus.levelCreatorOpened = false;
	currentStatus.saveLevelClicked = false;
	levelListSize = loadLevelList().size();
	levelSelection[0] = -1;
	levelSelection[1] = 2;
	mistakeCounter = -1;
	selectedNewLevel = loadedLevelName;
	lvCreateXSize = "";
	lvCreateYSize = "";
	lvCreateName = "";
}

std::vector<std::string> SideMenu::loadLevelList() {
	std::vector<std::string> levelList;
	const std::filesystem::path path{ "levels" };
	for (const auto& entry : std::filesystem::directory_iterator(path)){
		levelList.push_back(entry.path().stem().string());
	}
	return levelList;
}

float SideMenu::getMenuWidth() const {
	return menuWidth;
}

std::string SideMenu::getSelectedNewLevel() const {
	return selectedNewLevel;
}
std::string SideMenu::getLoadedLevelName() const {
	return loadedLevelName;
}
std::string SideMenu::getNewLevelXSize() const {
	return lvCreateXSize;
}
std::string SideMenu::getNewLevelYSize() const {
	return lvCreateYSize;
}
std::string SideMenu::getNewLevelName() const {
	return lvCreateName;
}

void SideMenu::setMistakeCounter(unsigned int mistakes) {
	mistakeCounter = mistakes;
	return;
}


void SideMenu::renderMenu(sf::RenderWindow& window) {
	sf::Vector2f menuRenderStart(menuOffset, 0);
	sf::Vector2f size(menuWidth, window.getSize().y);
	


	sf::RectangleShape background(size);
	background.setPosition(menuRenderStart);
	background.setFillColor(sf::Color::Color(180, 180, 180));
	background.setOutlineColor(sf::Color::Black); 
	background.setOutlineThickness(1.0f); 

	
	window.draw(background);

	if (currentStatus.loadLevelClicked || currentStatus.lvCreateClicked) {
		saveLevelText = "  Zapisz poziom";

		sf::RectangleShape auxMenuBg(size);
		auxMenuBg.setPosition(menuRenderStart.x+menuWidth, menuRenderStart.y);
		auxMenuBg.setFillColor(sf::Color::Color(180, 180, 180));
		auxMenuBg.setOutlineColor(sf::Color::Black);
		auxMenuBg.setOutlineThickness(1.0f);
		window.draw(auxMenuBg);
	}

	sf::Font font;
	if (!font.loadFromFile("fonts/Montserrat-Medium.otf"))
	{
		return;
	}
	sf::Text Text;
	Text.setFont(font);
	Text.setFillColor(sf::Color::Black);
	Text.setCharacterSize(16);
	Text.setPosition(5 + menuOffset, 2);
	Text.setString("Wczytany poziom: \n" + loadedLevelName);

	sf::RectangleShape levelCell(sf::Vector2f(200, 30));
	levelCell.setOutlineColor(sf::Color::Black);
	levelCell.setOutlineThickness(1.0f);

	window.draw(Text);
	
	sf::RectangleShape loadLevelButton(buttonSize);
	loadLevelButton.setPosition(menuOffset + (menuWidth - buttonSize.x)/2, 50);
	if (currentStatus.loadLevelClicked)
	{	
		loadLevelButton.setFillColor(sf::Color::Color(153, 253, 255));
		levelList = loadLevelList();
		for (int i = 0; i < levelList.size(); i++) {
			levelCell.setPosition(menuOffset + menuWidth, i*30);
			if (i == levelSelection[0]) {
				levelCell.setFillColor(sf::Color::Color(161, 161, 161));
				if (levelSelection[1] > 2){
					levelCell.setFillColor(sf::Color::Red);
					selectedNewLevel = levelList[i];
				}
			}
			else
				levelCell.setFillColor(sf::Color::White);
			Text.setCharacterSize(12);
			Text.setPosition(menuOffset + menuWidth + 5, (i * 30)+ 6);
			Text.setString(levelList[i]);
			window.draw(levelCell);
			window.draw(Text);
		}

	}
	else{ 
		Text.setCharacterSize(16);
		loadLevelButton.setFillColor(sf::Color::White); 
		levelList.clear();

	}
	loadLevelButton.setOutlineThickness(-1.0f);
	loadLevelButton.setOutlineColor(sf::Color::Black);

	sf::RectangleShape finishLevelButton(buttonSize);
	finishLevelButton.setPosition(menuOffset + (menuWidth - buttonSize.x) / 2, 105); 
	finishLevelButton.setOutlineThickness(-1.0f);
	finishLevelButton.setOutlineColor(sf::Color::Black);


	sf::RectangleShape levelCreatorButton(buttonSize);
	levelCreatorButton.setPosition(menuOffset + (menuWidth - buttonSize.x) / 2, window.getSize().y - 100);
	levelCreatorButton.setOutlineThickness(-1.0f);
	levelCreatorButton.setOutlineColor(sf::Color::Black);
	if (currentStatus.lvCreateClicked) {

		sf::RectangleShape levelCreatorXParam(sf::Vector2f(buttonSize.x/2, buttonSize.y));
		sf::RectangleShape levelCreatorYParam(sf::Vector2f(buttonSize.x / 2, buttonSize.y));
		sf::RectangleShape levelCreatorNameParam(sf::Vector2f(buttonSize.x, buttonSize.y/2));	

		sf::RectangleShape levelCreatorConfirmButton(buttonSize);
		Text.setPosition(30 + menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2, window.getSize().y - 85);
		Text.setString("Potwierdz");

		levelCreatorConfirmButton.setPosition(menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2, window.getSize().y - 100);
		levelCreatorConfirmButton.setFillColor(sf::Color::White);
		levelCreatorConfirmButton.setOutlineThickness(-1.0f);
		levelCreatorConfirmButton.setOutlineColor(sf::Color::Black);

		window.draw(levelCreatorConfirmButton);
		window.draw(Text);

		levelCreatorXParam.setPosition(menuOffset + menuWidth + (menuWidth - (buttonSize.x/2)) / 2,  50);
		levelCreatorYParam.setPosition(menuOffset + menuWidth + (menuWidth - (buttonSize.x / 2)) / 2,  150);
		levelCreatorNameParam.setPosition(menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2,  250);

		if (lvCreateXSelected) {
			levelCreatorXParam.setFillColor(sf::Color::Color(153, 253, 255));
		}
		else 
			levelCreatorXParam.setFillColor(sf::Color::White);

		if (lvCreateYSelected) {
			levelCreatorYParam.setFillColor(sf::Color::Color(153, 253, 255));
		}
		else
			levelCreatorYParam.setFillColor(sf::Color::White);
		if (lvCreateNameSelected)
		{
			levelCreatorNameParam.setFillColor(sf::Color::Color(153, 253, 255));
		}
		else
			levelCreatorNameParam.setFillColor(sf::Color::White);

		levelCreatorXParam.setOutlineThickness(-1.0f);
		levelCreatorXParam.setOutlineColor(sf::Color::Black);
		levelCreatorYParam.setOutlineThickness(-1.0f);
		levelCreatorYParam.setOutlineColor(sf::Color::Black);
		levelCreatorNameParam.setOutlineThickness(-1.0f);
		levelCreatorNameParam.setOutlineColor(sf::Color::Black);


		Text.setPosition(menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2, 30);
		Text.setCharacterSize(16);
		Text.setString("Rozmiar X");
		window.draw(Text);
		window.draw(levelCreatorXParam);
		Text.setPosition(10 + menuOffset + menuWidth + (menuWidth - (buttonSize.x / 2)) / 2, 30 + (buttonSize.y / 1.5));
		Text.setCharacterSize(20);
		Text.setString(lvCreateXSize);
		window.draw(Text);
		

		Text.setPosition(menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2, 130);
		Text.setCharacterSize(16);
		Text.setString("Rozmiar Y");
		window.draw(Text);
		window.draw(levelCreatorYParam);
		Text.setPosition(10 + menuOffset + menuWidth + (menuWidth - (buttonSize.x / 2)) / 2, 130 + (buttonSize.y / 1.5));
		Text.setCharacterSize(20);
		Text.setString(lvCreateYSize);
		window.draw(Text);

		Text.setPosition(menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2, 230);
		Text.setCharacterSize(16);
		Text.setString("Nazwa (max 15)");
		window.draw(Text);
		window.draw(levelCreatorNameParam);
		Text.setPosition(5 + menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2, 230 + (buttonSize.y / 2));
		Text.setCharacterSize(12);
		Text.setString(lvCreateName);
		window.draw(Text);



		levelCreatorButton.setFillColor(sf::Color::Color(153, 253, 255));
	}
	else {
		levelCreatorButton.setFillColor(sf::Color::White);
		lvCreateXSize = "";
		lvCreateYSize = "";
		lvCreateName = "";

	}

	Text.setFillColor(sf::Color::Black);
	Text.setCharacterSize(16);
	Text.setPosition(10 + menuOffset + (menuWidth - buttonSize.x) / 2, 65);
	Text.setString("Wczytaj poziom");
	

	window.draw(loadLevelButton);
	window.draw(Text);
	if (!currentStatus.levelCreatorOpened) {
		Text.setString("Sprawdz poziom");	
	}
	else {
		Text.setString(saveLevelText);
	}
	Text.setPosition(6 + menuOffset + (menuWidth - buttonSize.x) / 2, 120);
	window.draw(finishLevelButton);
	window.draw(Text);
	Text.setPosition(10 + menuOffset + (menuWidth - buttonSize.x) / 2, window.getSize().y - 85);
	Text.setString("Utworz poziom");

	window.draw(levelCreatorButton);
	window.draw(Text);

	if (mistakeCounter > -1) {
		Text.setPosition(5 +menuOffset, 180);
		Text.setString("Wciaz zostalo ci: \n" + std::to_string(mistakeCounter) + " bledow");
		if (mistakeCounter == 0){
			Text.setString("Poziom ukonczony!");
		}
		window.draw(Text);
	}
	if (currentStatus.saveLevelClicked) {
		saveLevelText = "Poziom zapisany";

	}


}

void SideMenu::menuEvents(sf::RenderWindow& window, sf::Event event) {

	sf::Vector2i mousePositionWindow = sf::Mouse::getPosition(window);
	sf::Vector2f mousePositionGrid = window.mapPixelToCoords(mousePositionWindow);

	if (event.type == sf::Event::MouseButtonPressed) {
		if (mousePositionGrid.x >= (menuOffset + (menuWidth - buttonSize.x) / 2) && mousePositionGrid.y >= 50 &&
			mousePositionGrid.x < (menuOffset + (menuWidth - buttonSize.x) / 2) + buttonSize.x &&
			mousePositionGrid.y < 50 + buttonSize.y)
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				currentStatus.loadLevelClicked = (currentStatus.loadLevelClicked) ? false : true;
				currentStatus.lvCreateClicked = false;
			}
		}
		if (mousePositionGrid.x >= (menuOffset + menuWidth) && mousePositionGrid.y >= 0 &&
			mousePositionGrid.x < (menuOffset + (menuWidth * 2)) &&
			mousePositionGrid.y < levelListSize * 30)
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePositionWindow = sf::Mouse::getPosition(window);
				sf::Vector2f mousePositionGrid = window.mapPixelToCoords(mousePositionWindow);

				int previousChoice = levelSelection[0];
				levelSelection[0] = mousePositionGrid.y / 30;
				if (previousChoice == levelSelection[0])
					levelSelection[1] += 1;
				else
					levelSelection[1] = 2;

			}
		}
		if (mousePositionGrid.x >= (menuOffset + (menuWidth - buttonSize.x) / 2) && mousePositionGrid.y >= 105 &&
			mousePositionGrid.x < (menuOffset + (menuWidth - buttonSize.x) / 2) + buttonSize.x &&
			mousePositionGrid.y < 105 + buttonSize.y)
		{
			if (event.mouseButton.button == sf::Mouse::Left && !currentStatus.levelCreatorOpened) {
				currentStatus.finishLevelClicked = true;
			}
			if (event.mouseButton.button == sf::Mouse::Left && currentStatus.levelCreatorOpened) {
				currentStatus.saveLevelClicked = true;
			}
		}
		if (mousePositionGrid.x >= (menuOffset + (menuWidth - buttonSize.x) / 2) && mousePositionGrid.y >= window.getSize().y - 100 &&
			mousePositionGrid.x < (menuOffset + (menuWidth - buttonSize.x) / 2) + buttonSize.x &&
			mousePositionGrid.y < window.getSize().y - 100 + buttonSize.y)
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				currentStatus.lvCreateClicked = (currentStatus.lvCreateClicked == false) ? true : false;
				currentStatus.loadLevelClicked = false;
			}
		}
		
		if (mousePositionGrid.x >= menuOffset + menuWidth + (menuWidth - (buttonSize.x / 2)) / 2 && mousePositionGrid.y >= 50 &&
			mousePositionGrid.x < menuOffset + menuWidth + (menuWidth - (buttonSize.x / 2)) + (buttonSize.x/2) &&
			mousePositionGrid.y < 50 + buttonSize.y)
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				lvCreateXSelected = (lvCreateXSelected == false) ? true : false;
				lvCreateYSelected = false;
				lvCreateNameSelected = false;
			}
		}
		if (mousePositionGrid.x >= menuOffset + menuWidth + (menuWidth - (buttonSize.x / 2)) / 2 && mousePositionGrid.y >= 150 &&
			mousePositionGrid.x < menuOffset + menuWidth + (menuWidth - (buttonSize.x / 2)) / 2 + (buttonSize.x/2) &&
			mousePositionGrid.y < 150 + buttonSize.y)
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				lvCreateYSelected = (lvCreateYSelected == false) ? true : false;
				lvCreateXSelected = false;
				lvCreateNameSelected = false;
			}
		}
		if (mousePositionGrid.x >= (menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2) && mousePositionGrid.y >= 250 &&
			mousePositionGrid.x < (menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2) + buttonSize.x &&
			mousePositionGrid.y < 250 + (buttonSize.y/2))
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				lvCreateNameSelected = (lvCreateNameSelected == false) ? true : false;
				lvCreateXSelected = false;
				lvCreateYSelected = false;
			}
		}
		if (mousePositionGrid.x >= (menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2) && mousePositionGrid.y >= window.getSize().y - 100 &&
			mousePositionGrid.x < (menuOffset + menuWidth + (menuWidth - buttonSize.x) / 2) + buttonSize.x &&
			mousePositionGrid.y < window.getSize().y - 100 + buttonSize.y)
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				
				currentStatus.lvCreateConfirmed = true;
			}
		}


	}
	if (event.type == sf::Event::TextEntered && currentStatus.lvCreateClicked) {
		if (event.text.unicode < 128 )
		{
			if (lvCreateXSelected) {
				if (event.text.unicode == '\b' && lvCreateXSize.size() > 0) {
					lvCreateXSize.erase(lvCreateXSize.size() - 1, 1);
				}
				else if (event.text.unicode < 58 && event.text.unicode > 47 && lvCreateXSize.size() < 2)
					lvCreateXSize += event.text.unicode;
			}
			if (lvCreateYSelected) {
				if (event.text.unicode == '\b' && lvCreateYSize.size() > 0) {
					lvCreateYSize.erase(lvCreateYSize.size() - 1, 1);
				}
				else if (event.text.unicode < 58 && event.text.unicode > 47 && lvCreateYSize.size() < 2)
					lvCreateYSize += event.text.unicode;

			}
			if (lvCreateNameSelected) {
				if (event.text.unicode == '\b' && lvCreateName.size() > 0) {
					lvCreateName.erase(lvCreateName.size() - 1, 1);
				}
				else if (event.text.unicode > 48 && lvCreateName.size() < 10)
					lvCreateName += event.text.unicode;
			}
		}	
	}
}

