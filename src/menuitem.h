/***************************************************************************
                          menuitem.cpp  - A menu item, a base class for any
						  					widget that exists in a menu.
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

#ifndef TUXFOOTBALL_MENUITEM
#define TUXFOOTBALL_MENUITEM

#include <string>
#include <list>

#include "SDL.h"

class Menu;

class MenuItem {
public:
	MenuItem(Menu *menu, std::string name, std::string identifier);
	virtual ~MenuItem();
	MenuItem(const MenuItem &item);
	const MenuItem &operator=(const MenuItem &item);
	std::string name() const;
	std::string identifier() const;
	void incrementReference();
	void decrementReference();

	virtual std::string text() const = 0;	
	virtual std::string currentOptionText() const = 0;
	virtual int currentOptionValue() const = 0;
	virtual int width() = 0;
	virtual int height();
	virtual int maximumWidth() = 0;
	virtual void leftPressed() = 0;
	virtual void rightPressed() = 0;
	virtual void selectPressed() = 0;
	virtual void update(Uint8 *keys) = 0;
	virtual void draw(int x, int y, int wid, SDL_Surface *screen);
private:	// private methods
	std::string calculateTextString(std::string option) const;
private:	// private attributes
	std::string m_name;
	std::string m_identifier;
	int m_refCount;
protected:
	Menu *m_menu;
};

#endif // TUXFOOTBALL_MENUITEM
