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

#ifndef TUXFOOTBALL_SOUNDMANAGER
#define TUXFOOTBALL_SOUNDMANAGER

#include "resourcemanager.h"

#include <SDL_mixer.h>
#include <string>
#include <map>

struct ManagedSound {
	Mix_Chunk *sound;
	int refCount;
};

class SoundManager : public ResourceManager<Mix_Chunk, SoundManager> {
public:
	virtual Mix_Chunk *load(std::string filename);
	virtual void release(Mix_Chunk *file);
protected:
	virtual Mix_Chunk *add(std::string filename);
private:
	static std::map<std::string, ManagedSound> m_sounds;
};

#endif // TUXFOOTBALL_SOUNDMANAGER
