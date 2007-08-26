/***************************************************************************
   			   mainmenustate.cpp  - State that controls the main menu.
                             -------------------
    begin                : 31.05.2003
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
	
#include "redefinekeysstate.h"
#include "gameengine.h"
#include "redefinekeysmenu.h"

RedefineKeysState::RedefineKeysState(GameEngine &engine) :
			m_engine(engine)
{
}

RedefineKeysState::~RedefineKeysState()
{
}
	
void RedefineKeysState::enterState()
{
	initialiseRedefineMenu();
	m_engine.setupHalfTime();
}

void RedefineKeysState::leaveState()
{
}

void RedefineKeysState::updateLoop()
{
	Menu *menu = m_engine.menu();
	
	if(menu) {
		if(menu->selectionMade()) {
			m_engine.setState(GameEngine::TitleScreen);
		}
	} else {
		m_engine.setState(GameEngine::TitleScreen);
	}
}

void RedefineKeysState::initialiseRedefineMenu()
{
	
	Menu *menu = new RedefineKeysMenu(m_engine.controller(GameEngine::HomeController),
					 m_engine.controller(GameEngine::AwayController),
					 m_engine.screen(), "Redefine Keys");
	menu->show();
	m_engine.setMenu(menu);
	m_engine.setLogo("graphics/tuxfootball.png");
}

