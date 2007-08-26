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

#include "redefinekeysmenu.h"
#include "menulabel.h"
#include "menubutton.h"
#include "menukeyselect.h"
#include "controller.h"

RedefineKeysMenu::RedefineKeysMenu(Controller *home, Controller *away, SDL_Surface *screen, std::string name) :
							Menu(screen, name),
							m_home(home),
							m_away(away)
{
	addItem(new MenuLabel(this, "Player 1", "player1label"));
	addItem(m_keyHomeUp = new MenuKeySelect(this, home->keyUp(), "Up", "p1_up"));
	addItem(m_keyHomeDown = new MenuKeySelect(this, home->keyDown(), "Down", "p1_down"));
	addItem(m_keyHomeLeft = new MenuKeySelect(this, home->keyLeft(), "Left", "p1_left"));
	addItem(m_keyHomeRight = new MenuKeySelect(this, home->keyRight(), "Right", "p1_right"));
	addItem(m_keyHomePass = new MenuKeySelect(this, home->keyPass(), "Pass", "p1_pass"));
	addItem(m_keyHomeShoot = new MenuKeySelect(this, home->keyShoot(), "Shoot", "p1_shoot"));
	addItem(new MenuLabel(this, "Player 2", "player2label"));
	addItem(m_keyAwayUp = new MenuKeySelect(this, away->keyUp(), "Up", "p2_up"));
	addItem(m_keyAwayDown = new MenuKeySelect(this, away->keyDown(), "Down", "p2_down"));
	addItem(m_keyAwayLeft = new MenuKeySelect(this, away->keyLeft(), "Left", "p2_left"));
	addItem(m_keyAwayRight = new MenuKeySelect(this, away->keyRight(), "Right", "p2_right"));
	addItem(m_keyAwayPass = new MenuKeySelect(this, away->keyPass(), "Pass", "p2_pass"));
	addItem(m_keyAwayShoot = new MenuKeySelect(this, away->keyShoot(), "Shoot", "p2_shoot"));
	addItem(new MenuButton(this, "Exit", "exit"));
}

RedefineKeysMenu::~RedefineKeysMenu()
{
	m_home->setKeyUp(m_keyHomeUp->currentKey());
	m_home->setKeyDown(m_keyHomeDown->currentKey());
	m_home->setKeyLeft(m_keyHomeLeft->currentKey());
	m_home->setKeyRight(m_keyHomeRight->currentKey());
	m_home->setKeyPass(m_keyHomePass->currentKey());
	m_home->setKeyShoot(m_keyHomeShoot->currentKey());
	m_away->setKeyUp(m_keyAwayUp->currentKey());
	m_away->setKeyDown(m_keyAwayDown->currentKey());
	m_away->setKeyLeft(m_keyAwayLeft->currentKey());
	m_away->setKeyRight(m_keyAwayRight->currentKey());
	m_away->setKeyPass(m_keyAwayPass->currentKey());
	m_away->setKeyShoot(m_keyAwayShoot->currentKey());
}
