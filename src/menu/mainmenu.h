/***************************************************************************
                          mainmenu.cpp  - Defines the main menu
                             -------------------
    begin                : 18.04.2003
    copyright            : (C) 2003 by Jason Wood
    email                : jasonwood@blueyonder.co.uk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MAINMENU
#define MAINMENU

#include <string>

#include "menu.h"

#include "SDL.h"

class Controller;
class MenuKeySelect;
class GameEngine;

class MainMenu : public Menu
{
public:	
	MainMenu(GameEngine *gameEngine, Controller *home, Controller *away,  SDL_Surface *screen, std::string name);
	~MainMenu();
private:
	GameEngine *m_gameEngine;
	Controller *m_home;
	Controller *m_away;
};

#endif //MAINMENU
