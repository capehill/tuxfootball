/***************************************************************************
                          redefinekeysmenu.cpp  - A menu to allow keys to
						  							be redefined.
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

#ifndef VIDEOSETTINGSMENU
#define VIDEOSETTINGSMENU

#include <string>

#include "menu.h"

#include "SDL.h"

class MenuOptionList;

class VideoSettingsMenu : public Menu
{
public:	
	VideoSettingsMenu(bool currentMode, SDL_Surface *screen, std::string name);
	~VideoSettingsMenu();

	bool	currentMode() const;
private:
	bool m_fullscreen;

	MenuOptionList *m_modes;
};

#endif //VIDEOSETTINGSMENU
