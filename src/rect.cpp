/***************************************************************************
                          rect.cpp  - A rectangle
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

#include "rect.h"

Rect::Rect() : 
	SDL_Rect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(int x, int y, int width, int height) :
	SDL_Rect()
{
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
}

Rect::~Rect() 
{
}
