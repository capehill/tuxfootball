/***************************************************************************
                          team.cpp  - Handles team-based logic.
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

#ifndef TUXFOOTBALL_TEAM
#define TUXFOOTBALL_TEAM

#include <list>
#include <string>

#include "SDL.h"
#include "player.h"
#include "pitch.h"
#include "ball.h"
#include "graphics.h"
#include "gameengine.h"

using std::list;

class Team {
public:	
	Team(GameEngine *gameEngine, std::string name, std::string skin, std::string playerMarker, Pitch *pitch, Ball *ball, bool topHalf);
	~Team();

	void setFormation(int defense, int midfield, int attack);	
	void setupCorner(bool left, bool attack);
	void setupPenalty(bool attack);
	void setupKickoff(bool attack);	
	void setupGoalKick(bool attack, bool left, bool onFloor);
	void setupThrowIn(const Point3D &pos, bool attack);
	void setupHalfTime();
	void setupExtraTime();
	void setupNationalAnthem();
	bool ready();
	void changeSides();
	void setPitch(Pitch *pitch);
	void setControlState(Player::ControlState state);
	Player::ControlState controlState();
	
	void update();
	void setActivePlayer(list<PlayerContainer>::iterator player);
	Player *activePlayer();
	void calculateDesirablePositions();
	std::string name();
	bool topHalf();
	Player *findPlayerFromPosition(Point3D position, int direction);
	Player *calculateClosestPlayers(Point3D point);
private:
	list<PlayerContainer> m_players;
	bool m_topHalf;
	Player::ControlState m_controlState;	
	Pitch *m_pitch;
	int m_defenders;
	int m_midfielders;
	int m_attackers;
	Ball *m_ball;
	Player *m_activePlayer;	
	Player *m_firstPlayer;
	Player *m_secondPlayer;
	std::string m_name;
};

#endif /* TUXFOOTBALL_TEAM */
