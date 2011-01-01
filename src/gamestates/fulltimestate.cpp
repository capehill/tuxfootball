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
	
#include "fulltimestate.h"

#include "gameengine.h"

FullTimeState::FullTimeState(GameEngine &engine) :
			m_engine(engine)
{
}

FullTimeState::~FullTimeState()
{
}
	
void FullTimeState::enterState()
{
	if(m_engine.score(GameEngine::HomeTeam) == m_engine.score(GameEngine::AwayTeam)) {
		m_engine.setState(GameEngine::ExtraTimeStart);
		m_engine.setTimer(GameEngine::Stop);
	} else {
		m_engine.team(GameEngine::HomeTeam)->setupHalfTime();
		m_engine.team(GameEngine::AwayTeam)->setupHalfTime();
		m_engine.setLogo("graphics/fulltime.png");
	}
}

void FullTimeState::leaveState()
{
}

void FullTimeState::updateLoop()
{
	if(m_engine.timerState() == GameEngine::Stop) {
		if(m_engine.team(GameEngine::HomeTeam)->ready() && m_engine.team(GameEngine::AwayTeam)->ready()) {
			m_engine.setTimer(GameEngine::Restart);
		}
	} else if(m_engine.timer() > 300) {
		m_engine.clearLogo();
		m_engine.setState(GameEngine::Finished);
		m_engine.setTimer(GameEngine::Stop);
	}
}
