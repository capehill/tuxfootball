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
	
#include "matchfinishedstate.h"

#include "gameengine.h"

MatchFinishedState::MatchFinishedState(GameEngine &engine) :
				m_engine(engine)
{
}

MatchFinishedState::~MatchFinishedState()
{
}
	
void MatchFinishedState::enterState()
{
	m_engine.setState(GameEngine::TitleScreen);
}

void MatchFinishedState::leaveState()
{
}

void MatchFinishedState::updateLoop()
{
}
