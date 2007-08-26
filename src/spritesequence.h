/***************************************************************************
                          spritesequence.cpp  - A sequence of sprite objects
						  						which can be played one after
												another to form an animation.
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

#ifndef TUXFOOTBALL_SPRITESEQUENCE
#define TUXFOOTBALL_SPRITESEQUENCE

#include <list>
#include <string>

#include "SDL.h"

struct Sprite {
	SDL_Surface *surface[8];
	int duration;
};

class SpriteSequence {
public:
	SpriteSequence(SDL_PixelFormat *format, std::string basename, int animationFrames, bool repeats);
	~SpriteSequence();
	SDL_Surface *surface(int direction);
	void updateSequence();
	void restartSequence();
private:
	SDL_PixelFormat *m_format;
	std::list<Sprite> m_seq;
	std::list<Sprite>::iterator m_current;
	int m_spriteTime;
	bool m_repeats;
};

#endif /* TUXFOOTBALL_SPRITESEQUENECE */
