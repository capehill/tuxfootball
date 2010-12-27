/***************************************************************************
                          matrix.cpp  - Matrix math operations.
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

#ifndef TUXFOOTBALL_MATRIX
#define TUXFOOTBALL_MATRIX

#include "point3d.h"

class Matrix {
public:
	Matrix();
	~Matrix();

	Matrix operator*(const Matrix &mat);
	Matrix& operator*=(const Matrix &mat);
	Point3D operator*(const Point3D &vec);

	static Matrix identity();
	static Matrix arbitraryTransform(const Point3D &dir, double angle);
	static Matrix pitchTransform(double pitch);
	static Matrix rollTransform(double roll);
	static Matrix yawTransform(double yaw);

	Matrix inverse();

	double val(int x, int y) const;
	void setVal(int x, int y, double val);
#if 0
private:
	void correct();
#endif
private:
	double m_array[16];
};

#endif // TUXFOOTBALL_MATRIX
