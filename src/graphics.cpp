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

#include "graphics.h"

#include "logger/logger.h"

#include <iostream>

Graphics::Graphics(SDL_Surface *screen)
{
	m_screenSurface = screen;
}

Graphics::~Graphics()
{
}

void Graphics::addSprite(SpriteObject *obj)
{
	m_sprites.push_back(SpriteContainer(obj));
}

void Graphics::removeSprite(SpriteObject *obj)
{
	std::list<SpriteContainer>::iterator itt;

	for(itt = m_sprites.begin(); itt!=m_sprites.end(); ++itt) {
		if((*(*itt))==obj) {
			m_sprites.erase(itt);
			return;
		}
	}
	WARN("Graphics::removeSprite() : sprite does not exist");
}

void Graphics::draw(int left, int top)
{
	std::list<SpriteContainer>::iterator itt;

	for(itt=m_sprites.begin(); itt!=m_sprites.end(); ++itt) {
		(*(*itt))->drawShadow(left, top, m_screenSurface);
	}
	for(itt=m_sprites.begin(); itt!=m_sprites.end(); ++itt) {
		(*(*itt))->draw(left, top, m_screenSurface);
	}
	for(itt=m_sprites.begin(); itt!=m_sprites.end(); ++itt) {
		(*(*itt))->drawOverlay(left, top, m_screenSurface);
	}
}

void Graphics::update()
{
	m_sprites.sort();
}


SDL_Surface *Graphics::screen() {
	return m_screenSurface;
}
