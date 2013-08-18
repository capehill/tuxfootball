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

#ifndef TUXFOOTBALL_CONTROLLER
#define TUXFOOTBALL_CONTROLLER

#include <SDL.h>

class Ball;
class Pitch;
class Player;
class Team;

/** Player and CPU control. */
class Controller {
public:
	Controller(Team *team, Team *opp, SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right, SDL_Keycode shoot, SDL_Keycode pass, bool isCPU, Ball *ball, Pitch *pitch);
	~Controller();
	void updateController(const Uint8 *keys);
	void updateComputer();
	SDL_Keycode keyUp();
	SDL_Keycode keyDown();
	SDL_Keycode keyLeft();
	SDL_Keycode keyRight();
	SDL_Keycode keyPass();
	SDL_Keycode keyShoot();
	void setKeyUp(SDL_Keycode key);
	void setKeyDown(SDL_Keycode key);
	void setKeyLeft(SDL_Keycode key);
	void setKeyRight(SDL_Keycode key);
	void setKeyPass(SDL_Keycode key);
	void setKeyShoot(SDL_Keycode key);
	void setCPU(bool cpu);
private:
	int m_shootCount;
	bool m_canKick;
	Player *m_lastPlayer;
	Team *m_team;
	Team *m_oppTeam;
	SDL_Keycode m_up;
	SDL_Keycode m_down;
	SDL_Keycode m_left;
	SDL_Keycode m_right;
	SDL_Keycode m_shoot;
	SDL_Keycode m_pass;
	bool m_isCPU;
	Ball *m_ball;
	Pitch *m_pitch;
	/** a counter saying how long ago we last passed the ball. used by the computer controller */
	int m_lastPass;

	int calculateBestPass(Player *player);
	double calculateClosestOpponent(Player *player);
};

#endif /* TUXFOOTBALL_CONTROLLER */
