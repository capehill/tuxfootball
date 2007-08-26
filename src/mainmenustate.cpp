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
	
#include "mainmenustate.h"
#include "gameengine.h"
#include "mainmenu.h"

MainMenuState::MainMenuState(GameEngine &engine) :
			m_engine(engine)
{
}

MainMenuState::~MainMenuState()
{
}
	
void MainMenuState::enterState()
{
	m_engine.setCameraFollows(GameEngine::CameraPattern);

	initialiseMainMenu();

	m_engine.setupHalfTime();

	m_engine.setMusic("sound/titlemusic.ogg");
}

void MainMenuState::leaveState()
{
}

void MainMenuState::updateLoop()
{
	Menu *menu = m_engine.menu();
	
	if(menu) {
		if(menu->selectionMade()) {
			if(menu->cancelled()) {
				std::cout << "menu cancelled" << std::endl;
				m_engine.setFinished(true);
			} else if(menu->selected()->text() == "Play Game!") {
				m_engine.setState(GameEngine::MatchStart);
			} else if(menu->selected()->text() == "Redefine Keys") {
				m_engine.setState(GameEngine::RedefineKeysScreen);
			} else if(menu->selected()->text() == "Video Settings") {
				m_engine.setState(GameEngine::VideoSettingsMenu);
			} else {
				std::cout << "unknown menu selection" << std::endl;
				m_engine.setFinished(true);
			}
		}
	} else {
		std::cout << "menu non-existant" << std::endl;
		m_engine.setFinished(true);
	}
	if((menu) && (menu->finished())) {
		m_engine.clearLogo();
	}
}

void MainMenuState::initialiseMainMenu()
{
	Menu *menu = new MainMenu(&m_engine, m_engine.controller(GameEngine::HomeController),
					m_engine.controller(GameEngine::AwayController),
				       	m_engine.screen(), "TitleScreen");
	menu->show();
	m_engine.setMenu(menu);
	m_engine.setLogo("graphics/tuxfootball.png");
}
