/***************************************************************************
                          menuoptionlist.cpp  - Specifies a menu item with multiple
						  						selectable choices.
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

#include "menuoptionlist.h"
#include "SFont.h"
#include <iostream>

MenuOptionList::MenuOptionList(Menu *menu, std::string name, std::string identifier) :
				MenuItem(menu, name, identifier)
{
	m_name = name;
	m_identifier = identifier;
	m_curOption = m_optionList.begin();
}

MenuOptionList::~MenuOptionList()
{
}

MenuOptionList::MenuOptionList(const MenuOptionList &item) :
				MenuItem(item)
{
	m_name = item.name();
	m_identifier = item.identifier();
	m_optionList = item.optionList();
	m_curOption = m_optionList.begin();
}

const MenuOptionList &MenuOptionList::operator=(const MenuOptionList &item)
{
	m_name = item.name();
	m_optionList = item.optionList();
	m_curOption = m_optionList.begin();
}

void MenuOptionList::addOption(std::string option, int value)
{
	MenuOption opt;
	opt.text = option;
	opt.value = value;
	m_optionList.push_back(opt);
	m_curOption = m_optionList.begin();
}

std::string MenuOptionList::name() const
{
	return m_name;
}

std::string MenuOptionList::currentOptionText() const
{
	if(isOption()) {
		return (*m_curOption).text;
	} else {
		return "";
	}
}

int MenuOptionList::currentOptionValue() const
{
	if(isOption()) {
		return (*m_curOption).value;
	} else {
		return -1;
	}
}

int MenuOptionList::width(SFont* font)
{
	return font->getTextWidth(text().c_str());
}

int MenuOptionList::maximumWidth(SFont* font)
{
	if(!isOption()) return width(font);
	
	int maxWidth = 0;

	std::list<MenuOption>::iterator itt;

	for(itt=m_optionList.begin(); itt!=m_optionList.end(); ++itt) {
		int testWidth = font->getTextWidth(calculateTextString((*itt).text).c_str());

		if(testWidth > maxWidth) {
			maxWidth = testWidth;
		}
	}

	return maxWidth;
}

std::string MenuOptionList::text() const
{
	if(isOption()) {
		return calculateTextString((*m_curOption).text);
	}
	
	return m_name;
}

void MenuOptionList::selectOption(std::string option)
{
	if(!isOption()) return;
	
	std::list<MenuOption>::iterator itt;
	
	for(itt=m_optionList.begin(); itt!=m_optionList.end(); ++itt) {
		if((*itt).text == option) {
			m_curOption = itt;
			return;
		}
	}
}

void MenuOptionList::selectOption(int value)
{
	if(!isOption()) return;
	
	std::list<MenuOption>::iterator itt;
	
	for(itt=m_optionList.begin(); itt!=m_optionList.end(); ++itt) {
		if((*itt).value == value) {
			m_curOption = itt;
			return;
		}
	}
}

void MenuOptionList::incrementOption()
{
	++m_curOption;

	if(m_curOption == m_optionList.end()) {
		m_curOption = m_optionList.begin();
	}
}

void MenuOptionList::decrementOption()
{
	if(m_curOption == m_optionList.begin()) {
		m_curOption = m_optionList.end();
	}
	--m_curOption;
}

std::string MenuOptionList::calculateTextString(std::string option) const
{
	return m_name + " " + option;
}

const std::list<MenuOption> &MenuOptionList::optionList() const
{
	return m_optionList;
}

bool MenuOptionList::isOption() const
{
	return (!m_optionList.empty());
}

std::string MenuOptionList::identifier() const
{
	return m_identifier;
}

void MenuOptionList::leftPressed() 
{
	decrementOption();
}

void MenuOptionList::rightPressed()
{
	incrementOption();
}

void MenuOptionList::selectPressed()
{
}

void MenuOptionList::update(Uint8 *keys)
{
}

