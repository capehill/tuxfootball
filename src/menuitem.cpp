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

#include "menuitem.h"
#include "SFont.h"
#include <iostream>

MenuItem::MenuItem(Menu *menu, std::string name, std::string identifier)
{
	m_menu = menu;
	m_name = name;
	m_identifier = identifier;
	m_refCount = 0;
}

MenuItem::~MenuItem()
{
}

MenuItem::MenuItem(const MenuItem &item)
{
	m_name = item.name();
	m_identifier = item.identifier();	
}

const MenuItem &MenuItem::operator=(const MenuItem &item)
{
	m_name = item.name();
}

std::string MenuItem::name() const
{
	return m_name;
}

std::string MenuItem::calculateTextString(std::string option) const
{
	return m_name + " " + option;
}

std::string MenuItem::identifier() const
{
	return m_identifier;
}

void MenuItem::incrementReference()
{
	m_refCount++;
}

void MenuItem::decrementReference()
{
	m_refCount--;
	if(!m_refCount) delete this;
}

int MenuItem::height() 
{
	return 30;
}

void MenuItem::draw(int x, int y, int wid, SDL_Surface *screen) 
{
	int midX = x + (wid/2);
	
	PutString(screen, midX - (width()/2), y, text().c_str());
}
