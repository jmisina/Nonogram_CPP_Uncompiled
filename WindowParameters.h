#pragma once
#include "Level.h"
#include "SideMenu.h"

class WindowParameters
{
private:
	unsigned int windowXSize;
	unsigned int windowYSize;
public:
	bool menuBiggerThanLevel;

	WindowParameters(Level loadedLevel, SideMenu menu);
	unsigned int getXSize() const;
	unsigned int getYSize() const;
};

