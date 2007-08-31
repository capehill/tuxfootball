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
	if(m_sounds[filename].refCount == 0) {
		return addSound(filename);
	} else {
		m_sounds[filename].refCount++;
		return m_sounds[filename].sound;
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
	Mix_Chunk *sound = 0;
	int data_dirs = sizeof(data_dir)/sizeof(std::string);
	for (int i = 0; i < data_dirs; i++) {
		std::string soundfile = std::string(data_dir[i]);
		soundfile.append("/");
		soundfile.append(filename.c_str());
		std::cout << soundfile.c_str() << std::endl;
		sound = Mix_LoadWAV(soundfile.c_str());
		if (sound) break;
	}

	if(!sound) {
		std::cerr << "Tried to add sound \"" << filename.c_str() << "\" but failed : " << Mix_GetError() << std::endl;
		return 0;
	}

	m_sounds[filename].sound = sound;
	m_sounds[filename].refCount = 1;

	return m_sounds[filename].sound;
}

