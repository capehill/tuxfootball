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

#include "videosettingsmenu.h"

#include "elements/menubutton.h"
#include "elements/menuoptionlist.h"

VideoSettingsMenu::VideoSettingsMenu(bool currentMode, SDL_Surface *screen, std::string name) :
							Menu(screen, name),
							m_fullscreen(currentMode)
{
	addItem(m_modes = new MenuOptionList(this, "Video mode", "videomode"));
	m_modes->addOption("Fullscreen", true);
	m_modes->addOption("Windowed", false);
	m_modes->selectOption(currentMode);
	addItem(new MenuButton(this, "Exit", "exit"));
}

VideoSettingsMenu::~VideoSettingsMenu()
{
}

bool
VideoSettingsMenu::currentMode() const
{
	return m_modes->currentOptionValue() == 1;
}
