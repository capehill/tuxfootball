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

#ifndef DATA_DIR
# if defined( WIN32 )
#  define DATA_DIR "./data"
# else
#  define DATA_DIR "/usr/local/share/tuxfootball"
# endif /* defined( WIN32 ) */
#endif
