/***************************************************************************
                          resourcemanager.cpp - Keeps track of files, loading
						  						on demand and making sure they
												are deleted as needed.
                             -------------------
    begin                : 01.09.2007
    copyright            : (C) 2007 by Jason Wood
    email                : egore@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TUXFOOTBALL_RESOURCEMANAGER
#define TUXFOOTBALL_RESOURCEMANAGER

#include <string>
#include <map>

template<class T, typename C> class ResourceManager {
public:
	virtual T *load(std::string filename) = 0;
	virtual void release(T *file) = 0;
	static C* instance () {
		if (!_instance)
			_instance = new C ();
		return _instance;
	}
protected:
	virtual T *add(std::string filename) = 0;

	static C *_instance;
	ResourceManager() {};
	ResourceManager(const ResourceManager&);
	virtual ~ResourceManager() {
		_instance = 0;
	}
private:
	ResourceManager& operator = (const ResourceManager&);
};

template <class T, typename C> C* ResourceManager <T,C>::_instance = 0;


#endif // TUXFOOTBALL_RESOURCEMANAGER
