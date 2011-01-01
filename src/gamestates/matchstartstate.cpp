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
	
#include "matchstartstate.h"

#include "gameengine.h"

MatchStartState::MatchStartState(GameEngine &engine) :
			m_engine(engine)
{
}

MatchStartState::~MatchStartState()
{
}
	
void MatchStartState::enterState()
{
	m_engine.initialiseMatch();
	m_engine.setMusic("sound/ingame.ogg");
	m_engine.setState(GameEngine::NationalAnthem);
	m_engine.setTimer(GameEngine::Stop);
	m_engine.setCameraFollows(GameEngine::CameraBall);
}

void MatchStartState::leaveState()
{
}

void MatchStartState::updateLoop()
{
}
