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
	
#include "videomenustate.h"
#include "videosettingsmenu.h"
#include "gameengine.h"
#include "mainmenu.h"

VideoMenuState::VideoMenuState(GameEngine &engine) :
			m_engine(engine)
{
}

VideoMenuState::~VideoMenuState()
{
}
	
void VideoMenuState::enterState()
{
	initialiseVideoMenu();
}

void VideoMenuState::leaveState()
{
}

void VideoMenuState::updateLoop()
{
	Menu *menu = m_engine.menu();
	
	if(menu) {
		if(menu->selectionMade()) {
			m_engine.setFullScreen((dynamic_cast<VideoSettingsMenu*>(menu))->currentMode());
			m_engine.setState(GameEngine::TitleScreen);
		}
	} else {
		m_engine.setState(GameEngine::TitleScreen);
	}
}

void VideoMenuState::initialiseVideoMenu()
{
	Menu *menu = new VideoSettingsMenu(m_engine.fullScreen(), m_engine.screen(), "Video Settings");
	
	menu->show();
	m_engine.setMenu(menu);
	m_engine.setLogo("graphics/tuxfootball.png");
}

