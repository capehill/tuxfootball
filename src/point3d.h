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

#ifndef TUXFOOTBALL_VECTOR
#define TUXFOOTBALL_VECTOR

class Point3D {
public:
	Point3D();
	Point3D(double x, double y, double z=0.0);
	Point3D(const Point3D &copy);
	Point3D &operator=(const Point3D &rhs);
	~Point3D();
	Point3D operator*(double k) const;
	Point3D &operator*=(double k);
	Point3D operator+(Point3D vec) const;
	Point3D &operator+=(Point3D vec);	
	Point3D operator-(Point3D vec) const;
	Point3D &operator-=(Point3D vec);	
	Point3D &setZ(double z);
	void applyArbitraryRotation(Point3D &axis, double theta);
	double x() const;
	double y() const;
	double z() const;
	double length() const;
	double dotProduct(Point3D point) const;
	Point3D normalise() const;
	bool liesWithinArc(Point3D left, Point3D right);
private:
	double m_x, m_y, m_z;
};

#endif /* TUXFOOTBALL_VECTOR */
