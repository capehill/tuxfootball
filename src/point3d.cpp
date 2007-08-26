/***************************************************************************
                          point3d.cpp  - A 3d point.
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

#include "point3d.h"
#include "matrix.h"
#include <cmath>

Point3D::Point3D()	
{
	m_x = m_y = m_z = 0.0;
}
	
Point3D::Point3D(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

Point3D::Point3D(const Point3D &copy) :
	m_x(copy.m_x),
	m_y(copy.m_y),
	m_z(copy.m_z)

{
}

Point3D &Point3D::operator=(const Point3D &rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	m_z = rhs.m_z;
	return *this;
}

Point3D::~Point3D()
{
}

Point3D Point3D::operator*(double k) const
{
	return Point3D(m_x*k, m_y*k, m_z*k);
}

Point3D & Point3D::operator*=(double k)
{
	m_x*=k;
	m_y*=k;
	m_z*=k;

	return *this;
}

Point3D Point3D::operator+(Point3D vec) const
{
	return Point3D(	m_x + vec.x(),
			m_y + vec.y(),
			m_z + vec.z());
}

Point3D Point3D::operator-(Point3D vec) const
{
	return Point3D(	m_x - vec.x(),
			m_y - vec.y(),
			m_z - vec.z());
}

Point3D & Point3D::operator+=(Point3D vec)
{
	m_x += vec.x();
	m_y += vec.y();
	m_z += vec.z();
	
	return *this;
}

Point3D & Point3D::operator-=(Point3D vec)
{
	m_x -= vec.x();
	m_y -= vec.y();
	m_z -= vec.z();
	
	return *this;
}

double Point3D::x() const
{
	return m_x;
}

double Point3D::y() const
{
	return m_y;
}

double Point3D::z() const
{
	return m_z;
}

double Point3D::length() const
{
	return m_x*m_x + m_y*m_y + m_z*m_z;
}


Point3D &Point3D::setZ(double z)
{
	m_z = z;
	return *this;
}

double Point3D::dotProduct(Point3D point) const
{
	return m_x * point.x() + m_y*point.y() + m_z*point.z();	
}

void Point3D::applyArbitraryRotation(Point3D &axis, double theta)
{

}

Point3D Point3D::normalise() const
{
	double k;

	k = sqrt(length());

	if(k!=0) {
		k = 1/k;
		return *this * k;
	} else {
		return Point3D(1, 0, 0);
	}
}

bool Point3D::liesWithinArc(Point3D left, Point3D right)
{
	Point3D vec = normalise();

	left = (Matrix::rollTransform(+1.570796327) * left).normalise();
	right = (Matrix::rollTransform(-1.570796327) * right).normalise();
		
	if(left.dotProduct(vec) < 0) return false;
	if(right.dotProduct(vec) < 0) return false;

	return true;
}
