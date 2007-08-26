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
	
#include "extratimesecondhalfstate.h"

#include "gameengine.h"

ExtraTimeSecondHalfState::ExtraTimeSecondHalfState(GameEngine &engine) :
				m_engine(engine)
{
}

ExtraTimeSecondHalfState::~ExtraTimeSecondHalfState()
{
}
	
void ExtraTimeSecondHalfState::enterState()
{
	m_engine.team(GameEngine::HomeTeam)->changeSides();
	m_engine.team(GameEngine::AwayTeam)->changeSides();
	m_engine.setSubMode(GameEngine::KickOff, false);
	m_engine.setTimer(GameEngine::Restart);
	m_engine.setTimer(GameEngine::Stop);
}

void ExtraTimeSecondHalfState::leaveState()
{
}

void ExtraTimeSecondHalfState::updateLoop()
{
	if(m_engine.timer() > m_engine.halfLength()/3) {
		if(m_engine.score(GameEngine::HomeTeam) == m_engine.score(GameEngine::AwayTeam)) {
			m_engine.setState(GameEngine::PenaltyShootout);
		} else {
			m_engine.setState(GameEngine::Finished);
		}
		m_engine.setTimer(GameEngine::Stop);
		m_engine.playSound(GameEngine::RefWhistleEnd);
	}							
}
