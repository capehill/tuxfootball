/***************************************************************************
                          ball.cpp  - Contains all functioanlity related
									  to the football.
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

#ifndef TUXFOOTBALL_BALL
#define TUXFOOTBALL_BALL

#include "body.h"

class Graphics;
class Pitch;
class Player;
class SpriteObject;
struct Mix_Chunk;

/** Contains all functioanlity related to the football. */
class Ball : public Body {
public:
	Ball(Graphics *renderer, Pitch *pitch);
	~Ball();
	Point3D lastPosition();
	void move();
	void kickBall(const Point3D &vel, int priority, Player *kickBy);
	void applyKick();

	/**Calculate the velocity required for the ball to reach and stop at end */
	Point3D calculateReqVelocity(double z, Point3D end);
private:
	Pitch *m_pitch;
	Graphics *m_renderer;
	Point3D m_lastPosition;
	SDL_Surface *m_football;
	SDL_Surface *m_shadow;
	SpriteObject *m_object;
	static double bounceFactor;
	
	Point3D m_kickVel;
	Player *m_kickBy;
	int m_kickPriority;

	// sound fx
	Mix_Chunk *m_bounce;
	Mix_Chunk *m_kick;
	Mix_Chunk *m_rebound;
};

#endif  /* TUXFOOTBALL_BALL */
