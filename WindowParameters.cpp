#include "windowParameters.h"


WindowParameters::WindowParameters(Level loadedLevel, SideMenu menu) {
    windowXSize = ((2 + loadedLevel.getLevelBoard().getGridSizeX()) * loadedLevel.getCellSize().x + loadedLevel.getRenderStartingPoint().x + menu.getMenuWidth());
    windowYSize = ((2 + loadedLevel.getLevelBoard().getGridSizeY()) * loadedLevel.getCellSize().y + loadedLevel.getRenderStartingPoint().y > 500) ? ((1 + loadedLevel.getLevelBoard().getGridSizeY()) * loadedLevel.getCellSize().y + loadedLevel.getRenderStartingPoint().y) : 500;
    menuBiggerThanLevel = (windowYSize < 500) ? true : false;
    if (menuBiggerThanLevel) 
        loadedLevel.setRenderStartingPointY((500 + (2 + loadedLevel.getLevelBoard().getGridSizeY() * loadedLevel.getCellSize().y) + (loadedLevel.getXAxisClues().getCluesWidth() * loadedLevel.getCellSize().y)) / 6);
}

unsigned int WindowParameters::getXSize() const{
    return windowXSize;
}

unsigned int WindowParameters::getYSize() const{
    return windowYSize;
}



