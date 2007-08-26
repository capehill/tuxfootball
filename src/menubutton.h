/***************************************************************************
                          menubutton.cpp  - A menu button.
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

#ifndef TUXFOOTBALL_MENUBUTTON
#define TUXFOOTBALL_MENUBUTTON

#include <string>
#include <list>

#include "menuitem.h"

class Menu;

class MenuButton : public MenuItem {
public:
	MenuButton(Menu *menu, std::string name, std::string identifier);
	~MenuButton();
	MenuButton(const MenuButton &item);
	const MenuButton &operator=(const MenuButton &item);
	std::string name() const;
	int currentOptionValue() const;
	std::string currentOptionText() const;
	int width();
	int maximumWidth();
	std::string text() const;
	bool isOption() const;
	std::string identifier() const;
	void leftPressed();
	void rightPressed();
	void selectPressed();
	void update(Uint8 *keys);
private:
	std::string m_name;
	std::string m_identifier;

	std::string calculateTextString(std::string option) const;
};

#endif // TUXFOOTBALL_MENUBUTTON
