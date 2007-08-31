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

#include "surfacemanager.h"
#include "SDL_image.h"
#include "const.h"

#include <iostream>

std::map<std::string, ManagedSurface> SurfaceManager::m_surfaces;

SDL_Surface *SurfaceManager::loadImage(SDL_PixelFormat *format, std::string filename, bool colorKey, bool alpha)
{
	if(m_surfaces[filename].refCount == 0) {
		return addImage(format, filename, colorKey, alpha);
	} else {
		m_surfaces[filename].refCount++;
		return m_surfaces[filename].surface;
	}
}

void SurfaceManager::releaseImage(SDL_Surface *surface)
{
	std::map<std::string, ManagedSurface>::iterator itt;

	itt = m_surfaces.begin();

	while(itt!= m_surfaces.end()) {
		if( (*itt).second.surface == surface) {
			--((*itt).second.refCount);
			if(! (*itt).second.refCount) {
				SDL_FreeSurface((*itt).second.surface);
				m_surfaces.erase(itt);
			}
			return;
			
		}
		++itt;
	}

	std::cerr << "Tried to free a surface, could not be found." << std::endl;
}

SDL_Surface *SurfaceManager::addImage(SDL_PixelFormat *format, std::string filename, bool colorKey, bool alpha)
{
	// Try and load any image format first. If that fails, try and force loading as TGA. If that fails,
	// Crash 'n burn :-)

	SDL_Surface *surf = 0;
	int data_dirs = sizeof(data_dir)/sizeof(std::string);
	for (int i = 0; i < data_dirs; i++) {
		std::string imgfile = std::string(data_dir[i]);
		imgfile.append("/");
		imgfile.append(filename.c_str());
		surf = IMG_Load(imgfile.c_str());
		if (surf) break;
	}

	if (!surf) {	
		SDL_RWops *rw = SDL_RWFromFile(filename.c_str(), "r");	
		
		if(rw==NULL) {
			std::cerr << "Error - could not open image \"" << filename.c_str() << "\": " << SDL_GetError() << std::endl;
			return NULL;
		}

		surf = IMG_LoadTGA_RW(rw);	
		if(surf == NULL) {
			std::cerr << "Error - could not load image : " << SDL_GetError() << std::endl;		
			SDL_RWclose(rw);
			return NULL;
		}
		SDL_RWclose(rw);
	}

	if(colorKey) {
		Uint32 key = getPixel(surf, 0, 0);
		if(SDL_SetColorKey(surf, SDL_SRCCOLORKEY | SDL_RLEACCEL, key) < 0) {
			std::cout << "Error - could not apply color key to surface : " << SDL_GetError() << std::endl;
		}
	}
	if(alpha) {
		if(SDL_SetAlpha(surf, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE) < 0) {
			std::cout << "Error - could not set Alpha to surface : " << SDL_GetError() << std::endl;
		}
	}

	if(colorKey || alpha) {
		m_surfaces[filename].surface = SDL_DisplayFormatAlpha(surf);
	} else {
		m_surfaces[filename].surface = SDL_DisplayFormat(surf);
	}
	if(!m_surfaces[filename].surface) {
		std::cout << "Error - could not convert surface to Display Format : " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surf);
	
	m_surfaces[filename].refCount = 1;
	
	return m_surfaces[filename].surface;
}

Uint32 SurfaceManager::getPixel(SDL_Surface *surface, int x, int y)
{
	if( SDL_LockSurface(surface) < 0) {
		std::cerr << "Cannot lock surface : " << SDL_GetError() << std::endl;
		return 0;
	}
	
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	Uint32 val;
	
	switch(bpp) {
		case 1	: 	val = *p;
				break;
				
		case 2	: 	val = *(Uint16 *)p;
				break;
				
		case 3	: 	if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
					val = p[0] << 16 | p[1] << 8 | p[2];
				else
					val = p[0] | p[1] << 8 | p[2] << 16;
				break;
				
		case 4	: 	val = *(Uint32 *)p;
				break;
				
		default	:	val = 0;       /* shouldn't happen, but avoids warnings */
	}

	SDL_UnlockSurface(surface);

	return val;
}
