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

#include "menubutton.h"

#include <iostream>

#include "menu/menu.h"
#include "Font.hpp"

MenuButton::MenuButton(Menu *menu, std::string name, std::string identifier) :
				MenuItem(menu, name, identifier)
{
	m_name = name;
	m_identifier = identifier;
}

MenuButton::~MenuButton()
{
}

MenuButton::MenuButton(const MenuButton &item) :
			MenuItem(item)
{
	m_name = item.name();
	m_identifier = item.identifier();
}

const MenuButton &MenuButton::operator=(const MenuButton &item)
{
	m_name = item.name();
}

std::string MenuButton::name() const
{
	return m_name;
}

std::string MenuButton::currentOptionText() const
{
	return "";
}

int MenuButton::currentOptionValue() const
{
	return -1;
}

int MenuButton::width(SFont* font)
{
	return font->getTextWidth(text().c_str());
}

int MenuButton::maximumWidth(SFont* font)
{
	return width(font);
}

std::string MenuButton::text() const
{
	return m_name;
}

std::string MenuButton::calculateTextString(std::string option) const
{
	return m_name + " " + option;
}

std::string MenuButton::identifier() const
{
	return m_identifier;
}

void MenuButton::leftPressed()
{
}

void MenuButton::rightPressed()
{
}

void MenuButton::selectPressed()
{
	m_menu->setFinished();
}

void MenuButton::update(Uint8 *keys)
{
	// Does not react to keys
	(void) keys;
}
