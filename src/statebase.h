/***************************************************************************
   			   statebase.cpp  - ABC for game states.
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

#ifndef TUXFOOTBALL_STATEBASE
#define TUXFOOTBALL_STATEBASE

class StateBase {
public:
	StateBase();
	virtual ~StateBase();

	/** Called when the state is entered. Occurs before the update loop method is called. */
	virtual	void enterState() = 0;

	/** Called when leaving the state, after the last updateLoop has finished. */
	virtual void leaveState() = 0;

	/** The main logic for the state should be in updateLoop. */
	virtual void updateLoop() = 0;
};
#endif /* TUXFOOTBALL_GAMEENGINE */
