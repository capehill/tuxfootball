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

#include "tilemap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <surfacemanager.h>
#include "const.h"

TileMap::TileMap(SDL_Surface *screen, std::string path)
{
	m_screen = screen;

	std::ifstream *pTilemap = 0;
	SDL_Surface *surf = 0;
	int data_dirs = sizeof(data_dir)/sizeof(std::string);
	for (int i = 0; i < data_dirs; i++) {
		std::string datadir = std::string(data_dir[i]);
		datadir.append("/");
		std::ifstream tilemap((datadir+path+"/tile.map").c_str());
		if (tilemap) {
			pTilemap = &tilemap;
			break;
		}
	}

	

	if(!pTilemap) {
		std::cout << "Error - tile.map not found in " << path << std::endl;
		return;
	}

	std::cout << "FIXME - tilesize fixed at 16X16" << std::endl;
	m_tileWidth = 16;
	m_tileHeight = 16;

	std::cout << "FIXME - tilemap size fixed at 2560 * 4096 for the moment" << std::endl;
	m_tileMapWidth = 2560;
	m_tileMapHeight = 4096;

	m_numTilesWidth = m_tileMapWidth / m_tileWidth;
	m_numTilesHeight = m_tileMapHeight / m_tileHeight;

	m_tileSurfaces.resize(m_numTilesWidth * m_numTilesHeight);

	for(int y = 0; y<m_numTilesHeight; y++) {
		for(int x = 0; x<m_numTilesWidth; x++) {
			char next;
			std::ostringstream word;

			next = pTilemap->get();
			while(!isWhiteSpace(next)) {
				word << next;
				next = pTilemap->get();
			}

			next = pTilemap->peek();
			while(isWhiteSpace(next)) {
				pTilemap->ignore();
				next = pTilemap->peek();
			}
			
			if(word.str().compare(".") == 0) {
				setTileSurface(x, y, 0);
			} else {
				std::ostringstream file;
				file << path << "/tile" << word.str() << ".png";
				setTileSurface(x, y,  SurfaceManager::loadImage(screen->format, file.str(), false, true));
			}
		}
	}

	pTilemap->close();
}

TileMap::~TileMap()
{
	std::vector<SDL_Surface *>::iterator itt = m_tileSurfaces.begin();

	while(itt != m_tileSurfaces.end()) {
		if(*itt) SurfaceManager::releaseImage(*itt);
		
		++itt;
	}
}

void TileMap::draw(int left, int top)
{
	SDL_Rect tr;
	SDL_Rect sr;

	tr.x = 0;
	tr.y = 0;
	sr.w = tr.w = m_tileWidth;
	sr.w = tr.h = m_tileHeight;

	int tx, ty; 
	
	int ex = ((left+m_screen->w) / m_tileWidth) + 1;
	int ey = ((top+m_screen->h) / m_tileHeight) + 1;
	SDL_Surface *surf;

	ty = top / m_tileHeight;
	
	for(;ty < ey; ty++) {
		tx = left / m_tileWidth;
		
		for(; tx < ex; tx++) {
			surf = tileSurface(tx, ty);

			sr.x = (tx*m_tileWidth) - left;
			sr.y = (ty*m_tileHeight) - top; 

			if(surf) {
				if(SDL_BlitSurface(surf, &tr, m_screen, &sr) < 0) {
					std::cerr << "Error - could not pitch tile : " << SDL_GetError() << std::endl;
				}
			}
		}
	}	
}

SDL_Surface *TileMap::tileSurface(int x, int y)
{
	if(x<0) return 0;
	if(y<0) return 0;
	if(x>=m_numTilesWidth) return 0;
	if(y>=m_numTilesHeight) return 0;

	return m_tileSurfaces[x + y*m_numTilesWidth];
}

void TileMap::setTileSurface(int x, int y, SDL_Surface *surface)
{
	if(x<0) return;
	if(x>=m_numTilesWidth) return;
	if(y<0) return;
	if(y>=m_numTilesHeight) return;
	
	m_tileSurfaces[x + y*m_numTilesWidth] = surface;
}

bool TileMap::isWhiteSpace(char val)
{
	switch(val) {
		case ',' :
		case ' ' :
		case '\n' : return true;
	}
	return false;
}
