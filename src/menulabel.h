/***************************************************************************
                          menulabel.cpp  - An un-clickable menu item that displays
						  					a text label.
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

#ifndef TUXFOOTBALL_MENULABEL
#define TUXFOOTBALL_MENULABEL

#include <string>
#include <list>

#include "menuitem.h"

class Menu;

class MenuLabel : public MenuItem {
public:
	MenuLabel(Menu *menu, std::string name, std::string identifier);
	~MenuLabel();
	MenuLabel(const MenuLabel &item);
	const MenuLabel &operator=(const MenuLabel &item);
	std::string name() const;
	int currentOptionValue() const;
	std::string currentOptionText() const;
	int width();
	int height();
	int maximumWidth();
	std::string text() const;
	bool isOption() const;
	std::string identifier() const;
	void leftPressed();
	void rightPressed();
	void selectPressed();
	void update(Uint8 *keys);
	void draw(int x, int y, int wid, SDL_Surface *screen);
private:
	std::string m_name;
	std::string m_identifier;

	std::string calculateTextString(std::string option) const;
};

#endif // TUXFOOTBALL_MENULABEL
