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
	
#include "halftimestate.h"

#include "gameengine.h"

HalfTimeState::HalfTimeState(GameEngine &engine) :
			m_engine(engine)
{
}

HalfTimeState::~HalfTimeState()
{
}
	
void HalfTimeState::enterState()
{
	m_engine.team(GameEngine::HomeTeam)->setupHalfTime();
	m_engine.team(GameEngine::AwayTeam)->setupHalfTime();
	m_engine.setLogo("graphics/halftime.png");
}

void HalfTimeState::leaveState()
{
}

void HalfTimeState::updateLoop()
{
	if(m_engine.timerState() == GameEngine::Stop) {
		if(m_engine.team(GameEngine::HomeTeam)->ready() && m_engine.team(GameEngine::AwayTeam)->ready()) {
			m_engine.setTimer(GameEngine::Restart);
		}
	} else if(m_engine.timer() > 300) {
		m_engine.setState(GameEngine::SecondHalf);
		m_engine.clearLogo();
		m_engine.setTimer(GameEngine::Stop);
	}								
}
