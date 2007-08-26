/***************************************************************************
                          body.cpp  - Represents a physical body in the
						  			world.
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

#ifndef TUXFOOTBALL_BODY
#define TUXFOOTBALL_BODY

#include "point3d.h"
#include "SDL.h"

class Body {
public:
	Body();
	Body(const Point3D position, const Point3D velocity, const SDL_Rect boundingBox);
	virtual ~Body();
	virtual Point3D position();
	virtual Point3D velocity();
	virtual void setPosition(const Point3D &pos);
	virtual void setVelocity(const Point3D &vel);
	virtual void accelerate(const Point3D &acc);
	virtual void applyFriction(double friction);
	virtual void move();
private:
	Point3D m_position;
	Point3D m_velocity;
	SDL_Rect m_boundingBox;
};

#endif /* TUXFOOTBALL_BODY */
