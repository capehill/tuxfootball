/***************************************************************************
                          menukeyselect.cpp  - A menu item that remembers a key
						  						press and allows it to be redefined.
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

#ifndef TUXFOOTBALL_MENUKEYSELECT
#define TUXFOOTBALL_MENUKEYSELECT

#include <string>
#include <list>

#include "menuitem.h"

#include "SDL.h"

class Menu;

class MenuKeySelect : public MenuItem {
public:
	MenuKeySelect(Menu *menu, SDLKey key, std::string name, std::string identifier);
	~MenuKeySelect();
	MenuKeySelect(const MenuKeySelect &item);
	const MenuKeySelect &operator=(const MenuKeySelect &item);
	std::string name() const;
	std::string currentOptionText() const;
	int currentOptionValue() const;
	int width(SFont* font);
	int maximumWidth(SFont* font);
	std::string text() const;
	void incrementOption();
	void decrementOption();
	std::string identifier() const;
	void leftPressed();
	void rightPressed();
	void selectPressed();
	void update(Uint8 *keys);
	SDLKey currentKey();
private:
	Uint8 m_keystate[SDLK_LAST];
	std::string m_name;
	std::string m_identifier;
	SDLKey m_key;
};

#endif // TUXFOOTBALL_MENUKEYSELECT
