/***************************************************************************
   			   fulltimestate.cpp  - State that controls full time,
			   deciding whether to go into extra time or end the
			   match.
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
	
#include "penaltyshootoutstate.h"

#include "gameengine.h"

PenaltyShootoutState::PenaltyShootoutState(GameEngine &engine) :
				m_engine(engine)
{
}

PenaltyShootoutState::~PenaltyShootoutState()
{
}
	
void PenaltyShootoutState::enterState()
{
	m_engine.setState(GameEngine::Finished);
}

void PenaltyShootoutState::leaveState()
{
}

void PenaltyShootoutState::updateLoop()
{
}
