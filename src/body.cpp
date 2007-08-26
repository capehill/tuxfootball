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

#include "body.h"

Body::Body()
{
}

Body::Body(const Point3D position, const Point3D velocity, const SDL_Rect boundingBox) :
		m_position(position),
		m_velocity(velocity),
		m_boundingBox(boundingBox)
{
}

Body::~Body()
{
}

Point3D Body::position()
{
	return m_position;
}

Point3D Body::velocity()
{
	return m_velocity;
}

void Body::move()
{
	m_position += m_velocity;
}
void Body::setPosition(const Point3D &pos)
{
	m_position = pos;
}

void Body::setVelocity(const Point3D &vel)
{
	m_velocity = vel;
}

void Body::accelerate(const Point3D &acc)
{
	m_velocity += acc;
}

void Body::applyFriction(double friction)
{
	m_velocity = Point3D(	m_velocity.x()*friction,
				m_velocity.y()*friction,
				m_velocity.z());
}
