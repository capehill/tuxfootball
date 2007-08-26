/***************************************************************************
                          controller.cpp  - Player and CPU control.
                             -------------------
    begin                : 18.04.2003
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

#ifndef TUXFOOTBALL_CONTROLLER
#define TUXFOOTBALL_CONTROLLER

#include "SDL.h"
#include "team.h"
#include "player.h"
#include "ball.h"
#include "pitch.h"

class Controller {
public:
	Controller(Team *team, Team *opp, SDLKey up, SDLKey down, SDLKey left, SDLKey right, SDLKey shoot, SDLKey pass, bool isCPU, Ball *ball, Pitch *pitch);
	~Controller();
	void updateController(Uint8 *keys);
	void updateComputer();
	SDLKey keyUp();
	SDLKey keyDown();
	SDLKey keyLeft();
	SDLKey keyRight();
	SDLKey keyPass();
	SDLKey keyShoot();
	void setKeyUp(SDLKey key);
	void setKeyDown(SDLKey key);
	void setKeyLeft(SDLKey key);
	void setKeyRight(SDLKey key);
	void setKeyPass(SDLKey key);
	void setKeyShoot(SDLKey key);
	void setCPU(bool cpu);
private:
	int m_shootCount;
	bool m_canKick;
	Player *m_lastPlayer;
	Team *m_team;
	Team *m_oppTeam;
	SDLKey m_up;
	SDLKey m_down;
	SDLKey m_left;
	SDLKey m_right;
	SDLKey m_shoot;
	SDLKey m_pass;
	bool m_isCPU;
	Ball *m_ball;
	Pitch *m_pitch;
	/** a counter saying how long ago we last passed the ball. used by the computer controller */
	int m_lastPass;

	int calculateBestPass(Player *player);
	double calculateClosestOpponent(Player *player);
};

#endif
