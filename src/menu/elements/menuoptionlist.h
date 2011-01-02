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

#ifndef TUXFOOTBALL_MENUOPTIONLIST
#define TUXFOOTBALL_MENUOPTIONLIST

#include <string>
#include <list>

#include "menuitem.h"

class Menu;

struct MenuOption {
	std::string text;
	int value;
};

class MenuOptionList : public MenuItem {
public:
	MenuOptionList(Menu *menu, std::string name, std::string identifier);
	~MenuOptionList();
	MenuOptionList(const MenuOptionList &item);
	const MenuOptionList &operator=(const MenuOptionList &item);
	std::string name() const;
	void addOption(std::string option, int value);
	std::string currentOptionText() const;
	int currentOptionValue() const;
	int width(SFont* font);
	int maximumWidth(SFont* font);
	std::string text() const;
	void selectOption(std::string option);
	void selectOption(int value);	
	void incrementOption();
	void decrementOption();
	bool isOption() const;
	const std::list<MenuOption> &optionList() const;
	std::string identifier() const;
	void leftPressed();
	void rightPressed();
	void selectPressed();
	void update(Uint8 *keys);
private:
	std::list<MenuOption> m_optionList;
	std::list<MenuOption>::iterator m_curOption;
	std::string m_name;
	std::string m_identifier;

	std::string calculateTextString(std::string option) const;
};

#endif // TUXFOOTBALL_MENUOPTIONLIST
