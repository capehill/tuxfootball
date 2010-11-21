/***************************************************************************
                          fontmanager.cpp  - Manages fonts, makes sure
						  						that they are only loaded once
												and are deleted when no longer
												needed.
                             -------------------
    begin                : 21.11.2010
    copyright            : (C) 2010 by Christoph Brill
    email                : egore@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "fontmanager.h"
#include "surfacemanager.h"
#include "const.h"
#include <iostream>

std::map<std::string, ManagedFont> FontManager::m_fonts;

SFont *FontManager::load(std::string filename)
{
	// FIXME: Dummy
}

SFont *FontManager::load(SDL_PixelFormat *format, std::string filename, bool colorKey, bool alpha)
{
	if(m_fonts[filename].refCount == 0) {
		return add(format, filename, colorKey, alpha);
	} else {
		m_fonts[filename].refCount++;
		return m_fonts[filename].font;
	}
}

void FontManager::release(SFont *font)
{
	std::map<std::string, ManagedFont>::iterator itt;

	itt = m_fonts.begin();

	while(itt!= m_fonts.end()) {
		if( (*itt).second.font == font) {
			--((*itt).second.refCount);
			if(! (*itt).second.refCount) {
				// NOTE: This only works because we changed SFont_FreeFont NOT
				// to release the surface
				delete ((*itt).second.font);
				SurfaceManager::instance()->release((*itt).second.surface);
				m_fonts.erase(itt);
			}
			return;
			
		}
		++itt;
	}

	std::cerr << "Tried to free a font, could not be found." << std::endl;
}

SFont *FontManager::add(std::string filename)
{
	// FIXME: Dummy
}

SFont *FontManager::add(SDL_PixelFormat *format, std::string filename, bool colorKey, bool alpha)
{
	SDL_Surface* fontSurface = SurfaceManager::instance()->load(format, filename, colorKey, alpha);
	SFont* font = new SFont(fontSurface);
	
	if(!font) {
		std::cerr << "Tried to add font \"" << filename.c_str() << "\" but failed " << std::endl;
		return 0;
	}

	m_fonts[filename].font = font;
	m_fonts[filename].refCount = 1;
	m_fonts[filename].surface = fontSurface;

	return m_fonts[filename].font;
}

