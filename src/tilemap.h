/***************************************************************************
                          tilemap.cpp  - Draws "tiles". A tile map specifies
						  				a number of bitmap images, and then
										a grid specifying where each of those
										images should be placed. This allows
										for efficient management of large images
										with small amounts of unique detail - for
										instance, with pitch lines.
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

#ifndef TUXFOOTBALL_TILEMAP
#define TUXFOOTBALL_TILEMAP

#include <string>
#include <vector>
#include "SDL.h"

class TileMap {
public:
	TileMap(SDL_Surface *screen, std::string path);
	~TileMap();

	void draw(int left, int top);	
private:
	int m_tileWidth;
	int m_tileHeight;
	int m_tileMapWidth;
	int m_tileMapHeight;
	int m_numTilesWidth;
	int m_numTilesHeight;	
	std::vector<SDL_Surface *> m_tileSurfaces;
	SDL_Surface *m_screen;
	
	SDL_Surface *tileSurface(int x, int y);	
	void setTileSurface(int x, int y, SDL_Surface *surface);
	bool isWhiteSpace(char val);
};

#endif // TUXFOOTBALL_TILEMAP
