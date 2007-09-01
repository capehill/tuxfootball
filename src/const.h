/***************************************************************************
                          const.h - Few defaults can be found here
                             -------------------
    begin                : 03.11.2005
    copyright            : (C) 2005 by Christoph Brill
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
/*
  $Id: const.h,v 1.1 2005/11/03 12:21:56 egore Exp $
*/

#include <vector>
#include <string>

#ifdef PACKAGE_DATA_DIR
const std::string data_dir[] = { (std::string(PACKAGE_DATA_DIR)+"/tuxfootball").c_str(), "./data", "/usr/local/share/tuxfootball" };
#else
const std::string data_dir[] = { "./data", "/usr/local/share/tuxfootball" };
#endif
