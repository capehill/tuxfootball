/***************************************************************************
                          segment.cpp  - A line segment, from a start point
						  				to an end point.
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

#ifndef TUXFOOTBALL_SEGMENT
#define TUXFOOTBALL_SEGMENT

#include "point3d.h"

class Segment {
public:
	Segment(Point3D start, Point3D end);		
	~Segment();
	Point3D start();
	Point3D end();
	Point3D vector();
private:
	Point3D m_start;
	Point3D m_end;
};

#endif
