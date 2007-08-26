/***************************************************************************
                          graphics.cpp  - Handles the correct drawing of sprites
						  					on screen.
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

#ifndef TUXFOOTBALL_GRAPHICS
#define TUXFOOTBALL_GRAPHICS

#include "SDL.h"
#include "spriteobject.h"
#include <list>


class SpriteContainer {
public:
	SpriteContainer(SpriteObject *obj) {
		m_so = obj;
	}
	
	~SpriteContainer() {
	}
	
	SpriteObject *operator*() {
		return m_so;
	}

	bool operator<(SpriteContainer &cont) {
		return (m_so->position().y() < (*cont)->position().y());
	}
private:
	SpriteObject *m_so;
};

class Graphics {
public:
	Graphics(SDL_Surface *screen);
	~Graphics();
	void addSprite(SpriteObject *obj);
	void removeSprite(SpriteObject *obj);
	void draw(int left, int top);
	void update();
	SDL_Surface *screen();
private:
	std::list<SpriteContainer> m_sprites;
	SDL_Surface *m_screenSurface;
};

#endif
