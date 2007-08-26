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

#ifndef TUXFOOTBALL_RECT
#define TUXFOOTBALL_RECT

#include "SDL.h"

class Rect : public SDL_Rect {
public:
	Rect();
	Rect(int x, int y, int width, int height);
	~Rect();
};

#endif // TUXFOOTBALL_RECT
