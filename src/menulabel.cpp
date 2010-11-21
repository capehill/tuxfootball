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

#include <iostream>

#include "menu.h"
#include "menulabel.h"

MenuLabel::MenuLabel(Menu *menu, std::string name, std::string identifier) :
				MenuItem(menu, name, identifier)
{
	m_name = name;
	m_identifier = identifier;
}

MenuLabel::~MenuLabel()
{
}

MenuLabel::MenuLabel(const MenuLabel &item) :
			MenuItem(item)
{
	m_name = item.name();
	m_identifier = item.identifier();
}

const MenuLabel &MenuLabel::operator=(const MenuLabel &item)
{
	m_name = item.name();
}

std::string MenuLabel::name() const
{
	return m_name;
}

std::string MenuLabel::currentOptionText() const
{
	return "";
}

int MenuLabel::currentOptionValue() const
{
	return -1;
}

int MenuLabel::width(SFont* font)
{
	return font->getTextWidth(text().c_str());
}

int MenuLabel::maximumWidth(SFont* font)
{
	return width(font);
}

std::string MenuLabel::text() const
{
	return m_name;
}

std::string MenuLabel::calculateTextString(std::string option) const
{
	return m_name + " " + option;
}

std::string MenuLabel::identifier() const
{
	return m_identifier;
}

void MenuLabel::leftPressed()
{
}

void MenuLabel::rightPressed()
{
}

void MenuLabel::selectPressed()
{
}

void MenuLabel::update(Uint8 *keys)
{
}

int MenuLabel::height() 
{
	return 40;
}

void MenuLabel::draw(SFont* font, int x, int y, int wid, SDL_Surface *screen) 
{
	int midX = x + (wid/2);
	
	font->write(screen, text().c_str(), midX - (width(font)/2), y+10);	
}
