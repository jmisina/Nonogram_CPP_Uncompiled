#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "level.h"
#include "board.h"
#include "sideMenu.h"
#include "windowParameters.h"
#include <string>

Game::Game() {
    Level loadedLevel;
    SideMenu menu(loadedLevel);
    WindowParameters windowParams(loadedLevel, menu);

    sf::RenderWindow window(sf::VideoMode(windowParams.getXSize(), windowParams.getYSize()), "Nonogram: " + loadedLevel.getLevelName());
    sf::View view(sf::FloatRect(0, 0, windowParams.getXSize(), windowParams.getYSize()));

    window.setView(view);


    while (window.isOpen()) {
        sf::Event event;
        if (loadedLevel.getLevelName() != menu.getSelectedNewLevel()) {
            menu.currentStatus.loadLevelClicked = false;
            loadedLevel.~Level();
            loadedLevel = Level(menu.getSelectedNewLevel());
            menu = SideMenu(loadedLevel);
            windowParams = WindowParameters(loadedLevel, menu);
            window.setSize(sf::Vector2u(windowParams.getXSize(), windowParams.getYSize()));
            window.setTitle("Nonogram: " + loadedLevel.getLevelName());
            view.setSize(windowParams.getXSize(), windowParams.getYSize());
            view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
            window.setView(view);

        }
        if (menu.currentStatus.lvCreateConfirmed) {
            unsigned int newXSize = stoi("0" + menu.getNewLevelXSize());
            unsigned int newYSize = stoi("0" + menu.getNewLevelYSize());
            if (newXSize > 0 && newXSize <=50 && newYSize > 0 && newYSize <=50 && menu.getNewLevelName().length() > 0) {
                loadedLevel = Level(menu.getNewLevelName(), Board(newXSize, newYSize, std::vector<std::vector<short int>>(newXSize, std::vector<short int>(newYSize, 0))));
                menu = SideMenu(loadedLevel);
                menu.currentStatus.levelCreatorOpened = true;
                windowParams = WindowParameters(loadedLevel, menu);
                window.setSize(sf::Vector2u(windowParams.getXSize(), windowParams.getYSize()));
                window.setTitle("Nonogram: " + loadedLevel.getLevelName());
                view.setSize(windowParams.getXSize(), windowParams.getYSize());
                view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
                window.setView(view);
            }
            menu.currentStatus.lvCreateConfirmed = false;

        }
        if (menu.currentStatus.levelCreatorOpened) {
            if (menu.currentStatus.saveLevelClicked) {
                loadedLevel.saveLevel();
                menu.currentStatus.saveLevelClicked = false;
            }

        }
        window.clear();
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (menu.currentStatus.finishLevelClicked) {
                menu.setMistakeCounter(loadedLevel.analyzeLevel());
                menu.currentStatus.finishLevelClicked = false;
            }
            if (menu.currentStatus.loadLevelClicked || menu.currentStatus.lvCreateClicked) {

                window.setSize(sf::Vector2u(windowParams.getXSize() + 200, windowParams.getYSize()));
                view.setSize(windowParams.getXSize() + 200, windowParams.getYSize());
                view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
                window.setView(view);

            }
            else {
                window.setSize(sf::Vector2u(windowParams.getXSize(), windowParams.getYSize()));
                view.setSize(windowParams.getXSize(), windowParams.getYSize());
                view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
                window.setView(view);
            }
            loadedLevel.boardEvents(window, event);
            menu.menuEvents(window, event);
        }
        loadedLevel.drawLevel(window);
        menu.renderMenu(window);

        window.display();
    }


}