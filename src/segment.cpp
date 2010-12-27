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

#include "segment.h"

Segment::Segment(Point3D start, Point3D end)
{
	m_start = start;
	m_end = end;
}

Segment::~Segment()
{
}

const Point3D Segment::start()
{
	return m_start;
}

const Point3D Segment::end()
{
	return m_end;
}

Point3D Segment::vector()
{
	return m_end - m_start;
}
