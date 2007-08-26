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

#include "menu.h"
#include "menukeyselect.h"
#include "SFont.h"
#include <iostream>

MenuKeySelect::MenuKeySelect(Menu *menu, SDLKey key, std::string name, std::string identifier) :
				MenuItem(menu, name, identifier)
{
	m_key = key;
	m_name = name;
	m_identifier = identifier;
}

MenuKeySelect::~MenuKeySelect()
{
}

MenuKeySelect::MenuKeySelect(const MenuKeySelect &item) :
				MenuItem(item)
{
	m_name = item.name();
	m_identifier = item.identifier();
}

const MenuKeySelect &MenuKeySelect::operator=(const MenuKeySelect &item)
{
	m_name = item.name();
}

std::string MenuKeySelect::name() const
{
	return m_name;
}

std::string MenuKeySelect::currentOptionText() const
{
	return "";
}

int MenuKeySelect::currentOptionValue() const
{
	return -1;
}

int MenuKeySelect::width()
{
	return TextWidth(text().c_str());
}

int MenuKeySelect::maximumWidth()
{
	return width();
}

std::string MenuKeySelect::text() const
{
	return m_name + " " + SDL_GetKeyName(m_key);
}

std::string MenuKeySelect::identifier() const
{
	return m_identifier;
}

void MenuKeySelect::leftPressed() 
{
}

void MenuKeySelect::rightPressed()
{
}

void MenuKeySelect::selectPressed()
{
	for(int count=0; count<SDLK_LAST; count++) m_keystate[count] = 0;
	
	m_menu->grabFocus(this);
}

void MenuKeySelect::update(Uint8 *keys)
{
	for(int count=0; count<SDLK_LAST; count++) {
		if((m_keystate[count]) && (!keys[count])) {
			m_menu->grabFocus(0);
			m_key = (SDLKey)count;
		}
		m_keystate[count] = keys[count];
	}
}

SDLKey MenuKeySelect::currentKey()	
{
	return m_key;
}
