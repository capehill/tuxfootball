/***************************************************************************
   			   extratimestate.cpp - State that handles the break
			   before extra time starts. Once finished, it goes
			   into extratimefirsthalf.
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
	
#include "extratimestate.h"

#include "gameengine.h"

ExtraTimeState::ExtraTimeState(GameEngine &engine) :
			m_engine(engine)
{
}

ExtraTimeState::~ExtraTimeState()
{
}
	
void ExtraTimeState::enterState()
{
	m_engine.setState(GameEngine::ExtraTimeFirstHalf);
}

void ExtraTimeState::leaveState()
{
}

void ExtraTimeState::updateLoop()
{
}
