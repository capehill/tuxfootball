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
	
#include "secondhalfstate.h"

#include "gameengine.h"

SecondHalfState::SecondHalfState(GameEngine &engine) :
			m_engine(engine)
{
}

SecondHalfState::~SecondHalfState()
{
}
	
void SecondHalfState::enterState()
{
	m_engine.team(GameEngine::HomeTeam)->changeSides();
	m_engine.team(GameEngine::AwayTeam)->changeSides();
	m_engine.setSubMode(GameEngine::KickOff, false);
	m_engine.setTimer(GameEngine::Restart);
	m_engine.setTimer(GameEngine::Stop);
}

void SecondHalfState::leaveState()
{
}

void SecondHalfState::updateLoop()
{
	if(m_engine.timer() > m_engine.halfLength()) {
		m_engine.setState(GameEngine::FullTime);
		m_engine.playSound(GameEngine::RefWhistleEnd);
		m_engine.setTimer(GameEngine::Stop);
	}								
}
