/***************************************************************************
 *   Copyright (C) 2003-2010 by Tux Football development team              *
 *   Authors: Jason Wood <jasonwood@blueyonder.co.uk>                      *
 *            Christoph Brill <egore911@egore911.de>                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#ifdef HAVE_GETTEXT
#include <libintl.h>
#define _(String) gettext (String)
#else
#define _(String) (String)
#endif

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
			} else if(menu->selected()->text() == _("Play Game!")) {
				m_engine.setState(GameEngine::MatchStart);
			} else if(menu->selected()->text() == _("Redefine Keys")) {
				m_engine.setState(GameEngine::RedefineKeysScreen);
			} else if(menu->selected()->text() == _("Video Settings")) {
				m_engine.setState(GameEngine::VideoSettingsMenu);
			} else {
				std::cout << "unknown menu selection " << menu->selected()->text() << std::endl;
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

bool MainMenuState::isGameInProgress()
{
	return false;
}
