/***************************************************************************
 *   Copyright (C) 2003-2011 by Tux Football development team              *
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

bool HalfTimeState::isGameInProgress() const
{
	return false;
}

void HalfTimeState::renderFrame()
{
}
