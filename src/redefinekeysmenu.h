/***************************************************************************
                          redefinekeysmenu.cpp  - A menu to allow keys to
						  							be redefined.
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

#ifndef REDEFINEKEYSMENU
#define REDEFINEKEYSMENU

#include <string>

#include "menu.h"

#include "SDL.h"

class Controller;
class MenuKeySelect;

class RedefineKeysMenu : public Menu
{
public:	
	RedefineKeysMenu(Controller *home, Controller *away, SDL_Surface *screen, std::string name);
	~RedefineKeysMenu();
private:
	Controller *m_home;
	Controller *m_away;
	MenuKeySelect *m_keyHomeUp;
	MenuKeySelect *m_keyHomeDown;
	MenuKeySelect *m_keyHomeLeft;
	MenuKeySelect *m_keyHomeRight;
	MenuKeySelect *m_keyHomePass;
	MenuKeySelect *m_keyHomeShoot;
	MenuKeySelect *m_keyAwayUp;
	MenuKeySelect *m_keyAwayDown;
	MenuKeySelect *m_keyAwayLeft;
	MenuKeySelect *m_keyAwayRight;
	MenuKeySelect *m_keyAwayPass;
	MenuKeySelect *m_keyAwayShoot;
};

#endif //REDEFINEKEYSMENU
