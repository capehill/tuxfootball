/***************************************************************************
                          mainmenu.cpp  - Defines the main menu
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

#include "mainmenu.h"
#include "menulabel.h"
#include "menubutton.h"
#include "menuoptionlist.h"
#include "controller.h"
#include "gameengine.h"

#include <iostream>
#include <libintl.h>

MainMenu::MainMenu(GameEngine *gameEngine, Controller *home, Controller *away, SDL_Surface *screen, std::string name) :
				Menu(screen, name),
				m_gameEngine(gameEngine),
				m_home(home),
				m_away(away)
{
	addItem(new MenuButton(this, "Play Game!", "start"));
	MenuOptionList *length = new MenuOptionList(this, gettext("Half Length :"), "halflength");
	length->addOption(gettext("1 minute"), 6000);
	length->addOption(gettext("2 minutes"), 12000);
	length->addOption(gettext("5 minutes"), 30000);
	length->addOption(gettext("10 minutes"), 60000);
	length->addOption(gettext("20 minutes"), 120000);
	length->addOption(gettext("45 minutes"), 270000);
	addItem(length);
	MenuOptionList *who = new MenuOptionList(this, gettext("Players :"), "players");
	who->addOption(gettext("Player V Computer"), 1);
	who->addOption(gettext("Player V Player"), 3);
	who->addOption(gettext("Computer V Computer"), 0);	
	addItem(who);
	addItem(new MenuButton(this, gettext("Video Settings"), "video"));
	addItem(new MenuButton(this, gettext("Redefine Keys"), "redefine"));
	addItem(new MenuButton(this, gettext("Exit"), "exit"));
}

MainMenu::~MainMenu()
{
	int halfLength;
	const MenuItem *item = menuItem("halflength");
	if(item) {
		halfLength = item->currentOptionValue();
	} else {
		halfLength = 100;
	}
	m_gameEngine->setHalfLength(halfLength);

	item = menuItem("players");
	if(item) {
		int value = item->currentOptionValue();		
		m_home->setCPU( (value & 1) == 0);
		m_away->setCPU( (value & 2) == 0);
	} else {
		std::cerr << "Error - number of players not defined" << std::endl;
		m_home->setCPU(true);
		m_away->setCPU(false);
	}
}
