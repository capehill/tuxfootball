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

#ifndef TUXFOOTBALL_FONTMANAGER
#define TUXFOOTBALL_FONTMANAGER

#include "resourcemanager.h"

#include "Font.hpp"
#include <string>
#include <map>


struct ManagedFont {
	SFont *font;
	int refCount;
	SDL_Surface *surface;
};

class FontManager : public ResourceManager<SFont, FontManager> {
public:
	virtual SFont *load(std::string filename);
	virtual SFont *load(SDL_PixelFormat *format, std::string filename, bool colorKey, bool alpha);
	virtual void release(SFont *font);
protected:
	virtual SFont *add(SDL_PixelFormat *format, std::string filename, bool colorKey, bool alpha);
	virtual SFont *add(std::string filename);
private:
	static std::map<std::string, ManagedFont> m_fonts;
};

#endif /* TUXFOOTBALL_FONTMANAGER */
