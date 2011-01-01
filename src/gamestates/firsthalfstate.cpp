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
	
#include "firsthalfstate.h"

#include "gameengine.h"

FirstHalfState::FirstHalfState(GameEngine &engine) :
		m_engine(engine)
{
}

FirstHalfState::~FirstHalfState()
{
}
	
void FirstHalfState::enterState()
{
	m_engine.setTimer(GameEngine::Restart);
	m_engine.setSubMode(GameEngine::KickOff, true);
}

void FirstHalfState::leaveState()
{
}

void FirstHalfState::updateLoop()
{
	if(m_engine.timer() > m_engine.halfLength()) {
		m_engine.setState(GameEngine::HalfTime);
		m_engine.playSound(GameEngine::RefWhistleTwice);
		m_engine.setTimer(GameEngine::Stop);
	}
}
