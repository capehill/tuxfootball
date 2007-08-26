/***************************************************************************
                          camera.cpp  - Defines a camera, including routines
						  				to smoothly move it around the pitch.
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

#ifndef TUXFOOTBALL_CAMERA
#define TUXFOOTBALL_CAMERA

#include "body.h"
#include "point3d.h"
#include "SDL.h"

class Camera {
public:
	Camera();
	~Camera();

	void setPosition(const Point3D &pos);
	void setDestination(const Point3D &pos);
	void update();
	Point3D position();
	double keepInRange(double val, double range);
	void setBoundingRect(const SDL_Rect &rect);
	void setScreenRect(const SDL_Rect &rect);
	void setTarget(Body *target);
private: // private attributes
	double m_accel;
	
	Body m_body;

	/** If set, the camera will follow this target. */
	Body *m_target;
	
	Point3D m_dest;
	SDL_Rect m_boundRect;
	SDL_Rect m_screenRect;

private: // private methods
	void updateDestination();
	void updatePosition();
};


#endif // TUXFOOTBALL_CAMERA
