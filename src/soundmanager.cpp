/***************************************************************************
                          soundmanager.cpp  - Keeps track of sounds, loading
						  						on demand and making sure they
												are deleted as needed.
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

#include "soundmanager.h"
#include "const.h"
#include <iostream>

std::map<std::string, ManagedSound> SoundManager::m_sounds;
	
Mix_Chunk *SoundManager::loadSound(std::string filename)
{
        std::string soundfile(DATA_DIR);
	soundfile.append("/");
	soundfile.append(filename);
	
	if(m_sounds[soundfile].refCount == 0) {
		return addSound(soundfile);
	} else {
		m_sounds[soundfile].refCount++;
		return m_sounds[soundfile].sound;
	}
}

void SoundManager::releaseSound(Mix_Chunk *sound)
{
	std::map<std::string, ManagedSound>::iterator itt;

	itt = m_sounds.begin();

	while(itt!= m_sounds.end()) {
		if( (*itt).second.sound == sound) {
			--((*itt).second.refCount);
			if(! (*itt).second.refCount) {
				Mix_FreeChunk((*itt).second.sound);
				m_sounds.erase(itt);
			}
			return;
			
		}
		++itt;
	}
	
	std::cerr << "Tried to free a sound, could not be found." << std::endl;
}

Mix_Chunk *SoundManager::addSound(std::string filename)
{
	Mix_Chunk *sound = Mix_LoadWAV(filename.c_str());

	if(!sound) {
		std::cerr << "Tried to add sound \"" << filename.c_str() << "\" but failed : " << Mix_GetError() << std::endl;
		return 0;
	}

	m_sounds[filename].sound = sound;
	m_sounds[filename].refCount = 1;

	return m_sounds[filename].sound;
}

