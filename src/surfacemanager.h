/***************************************************************************
                          surfacemanager.cpp  - Manages surfaces, makes sure
						  						that they are only loaded once
												and are deleted when no longer
												needed.
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

#ifndef TUXFOOTBALL_SURFACEMANAGER
#define TUXFOOTBALL_SURFACEMANAGER

#include <string>
#include <map>

#include "SDL.h"

struct ManagedSurface {
	SDL_Surface *surface;
	int refCount;
};

class SurfaceManager {
public:
	/** If colorKey is true, then the image will use the top-leftmost pixel as the color key. */
	static SDL_Surface *loadImage(SDL_PixelFormat *format, std::string filename, bool colorKey, bool alpha);
	static void releaseImage(SDL_Surface *surface);
private:
	static SDL_Surface *addImage(SDL_PixelFormat *format, std::string filename, bool colorKey, bool alpha);
	
	static std::map<std::string, ManagedSurface> m_surfaces;
	static Uint32 getPixel(SDL_Surface *surface, int x, int y);	
};

#endif /* TUXFOOTBALL_SURFACEMANAGER */
