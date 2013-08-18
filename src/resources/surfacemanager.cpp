/***************************************************************************
 *   Copyright (C) 2003-2011 by Tux Football development team              *
 *   Authors: Jason Wood <jasonwood@blueyonder.co.uk>                      *
 *            Christoph Brill <egore911@egore911.de>                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "surfacemanager.h"
#include "const.h"
#include "logger/logger.h"

#include <iostream>
#include <SDL_image.h>

std::map<std::string, ManagedSurface> SurfaceManager::m_surfaces;

SurfaceManager::SurfaceManager(SDL_Renderer* renderer) : ResourceManager(renderer) {
}

SDL_Texture *SurfaceManager::load(std::string filename) {
	if (m_surfaces[filename].refCount == 0) {
		return add(filename);
	} else {
		m_surfaces[filename].refCount++;
		return m_surfaces[filename].surface;
	}
}

SDL_Texture *SurfaceManager::load(std::string filename, bool colorKey, bool alpha)
{
	if (m_surfaces[filename].refCount == 0) {
		return add(filename, colorKey, alpha);
	} else {
		m_surfaces[filename].refCount++;
		return m_surfaces[filename].surface;
	}
}

void SurfaceManager::release(SDL_Texture *surface)
{
	std::map<std::string, ManagedSurface>::iterator itt;

	itt = m_surfaces.begin();

	while(itt!= m_surfaces.end()) {
		if( (*itt).second.surface == surface) {
			--((*itt).second.refCount);
			if(! (*itt).second.refCount) {
				SDL_DestroyTexture((*itt).second.surface);
				m_surfaces.erase(itt);
			}
			return;
			
		}
		++itt;
	}

	ERROR("Tried to free a surface, could not be found.");
}

SDL_Texture *SurfaceManager::add(std::string filename) {
	// Try and load any image format. If that fails, Crash 'n burn :-)

	SDL_Texture *surf = 0;
	int data_dirs = sizeof(data_dir)/sizeof(std::string);
	for (int i = 0; i < data_dirs; i++) {
		std::string imgfile = std::string(data_dir[i]);
		imgfile.append("/");
		imgfile.append(filename.c_str());
		surf = IMG_LoadTexture(m_renderer, imgfile.c_str());
		if (surf) break;
	}

	if (!surf) {	
		ERROR("could not load image : " << SDL_GetError());
		return 0;
	}

	m_surfaces[filename].surface = surf;
	if(!m_surfaces[filename].surface) {
		ERROR("could not convert surface to Display Format : " << SDL_GetError());
	}
	
	m_surfaces[filename].refCount = 1;
	
	return m_surfaces[filename].surface;
}

SDL_Texture *SurfaceManager::add(std::string filename, bool colorKey, bool alpha)
{
	// Try and load any image format. If that fails, Crash 'n burn :-)

	SDL_Texture *surf = 0;
	int data_dirs = sizeof(data_dir)/sizeof(std::string);
	for (int i = 0; i < data_dirs; i++) {
		std::string imgfile = std::string(data_dir[i]);
		imgfile.append("/");
		imgfile.append(filename.c_str());
		surf = IMG_LoadTexture(m_renderer, imgfile.c_str());
		if (surf) break;
	}

	if (!surf) {	
		ERROR("could not load image : " << SDL_GetError());
		return 0;
	}

	if(colorKey) {
		// FIXME disabled for now
		//Uint32 key = getPixel(surf, 0, 0);
		//if(SDL_SetColorKey(surf, SDL_TRUE | SDL_RLEACCEL, key) < 0) {
		//	ERROR("could not apply color key to surface : " << SDL_GetError());
		//}
	}
	if(alpha) {
		// FIXME disabled for now
		//if(SDL_SetAlpha(surf, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE) < 0) {
		//	ERROR("could not set Alpha to surface : " << SDL_GetError());
		//}
	}

	// FIXME disabled for now
	//if(colorKey || alpha) {
	//	m_surfaces[filename].surface = SDL_DisplayFormatAlpha(surf);
	//} else {
	//	m_surfaces[filename].surface = SDL_DisplayFormat(surf);
	//}
	m_surfaces[filename].surface = surf;
	if(!m_surfaces[filename].surface) {
		ERROR("could not convert surface to Display Format : " << SDL_GetError());
	}
	//SDL_FreeSurface(surf);
	
	m_surfaces[filename].refCount = 1;
	
	return m_surfaces[filename].surface;
}

Uint32 SurfaceManager::getPixel(SDL_Texture *surface, int x, int y)
{
	// FIXME disabled for now
	//if( SDL_LockSurface(surface) < 0) {
	//	ERROR("Cannot lock surface : " << SDL_GetError());
		return 0;
	//}

	//int bpp = surface->format->BytesPerPixel;
	//Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	//Uint32 val;
	
	//switch(bpp) {
	//	case 1:
	//		val = *p;
	//		break;
	//	case 2:
	//		val = *(Uint16 *)p;
	//		break;
	//	case 3:
	//		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	//			val = p[0] << 16 | p[1] << 8 | p[2];
	//		else
	//			val = p[0] | p[1] << 8 | p[2] << 16;
	//		break;
	//	case 4:
	//		val = *(Uint32 *)p;
	//		break;
	//	default:
	//		/* never happens, but avoids warnings */
	//		val = 0;
	//		break;
	//}

	//SDL_UnlockSurface(surface);

	//return val;
}
