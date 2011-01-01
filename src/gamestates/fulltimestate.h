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

#ifndef TUXFOOTBALL_FULLTIMESTATE
#define TUXFOOTBALL_FULLTIMESTATE

#include "statebase.h"

class GameEngine;

/** State that controls full time, deciding whether to go into extra time or
 * end the match. */
class FullTimeState : public StateBase {
public:
	FullTimeState(GameEngine &engine);
	~FullTimeState();

	/** Called when the state is entered. Occurs before the update loop method is called. */
	virtual	void enterState();

	/** Called when leaving the state, after the last updateLoop has finished. */
	virtual void leaveState();

	/** The main logic for the state should be in updateLoop. */
	virtual void updateLoop();

	/** Returns true, if the gamestate is a 'in game' gamestate */
	virtual bool isGameInProgress();
private:
	GameEngine &m_engine;
};
#endif /* TUXFOOTBALL_FULLTIMESTATE */
