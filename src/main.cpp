/***************************************************************************
                          main.cpp  - Execution starts here.
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
/*
  $Id: main.cpp,v 1.3 2005/10/26 19:00:54 egore Exp $
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_GETTEXT
#include <libintl.h>
#include <locale.h>
#endif

#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#ifdef _WIN32
#include "windows.h"
#endif

#include "gameengine.h"

void die(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  exit(1);
}

int main(int argc, char *argv[])
{
#ifdef HAVE_GETTEXT
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#else
	std::cout << "Gettext support not available due to missing config.h support" << std::endl;
#endif

	bool fullscreen = false;
	if(argc > 1) // first arg is path - we don't need it for now
	for(int i = argc-1; i > 0; i--) {
		if(argv[i][0] == '-') {
			switch(argv[i][1]) {
				default:
				case 'h':
					printf("\nTux Football [-switch]\n\nswitch can be:\n\n-h\tprint this help\n-w\trun Tux Football in windowed mode\n\n");
					return 0;
				break;
				case 'w':
					fullscreen = false;
				break;
			}
		}
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
		die("Couldn't initialize SDL: %s\n", SDL_GetError());
	atexit(SDL_Quit);

	GameEngine engine(fullscreen);

	engine.gameLoop();

	return 0;
}

#ifdef _WIN32
/* Taken from http://www.flipcode.com/archives/WinMain_Command_Line_Parser.shtml */
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, char* command_line, int show_command)
{

    int    argc;
    char** argv;

    char*  arg;
    int    index;
    int    result;

    // count the arguments

    argc = 1;
    arg  = command_line;

    while (arg[0] != 0) {

        while (arg[0] != 0 && arg[0] == ' ') {
            arg++;
        }

        if (arg[0] != 0) {

            argc++;

            while (arg[0] != 0 && arg[0] != ' ') {
                arg++;
            }

        }

    }

    // tokenize the arguments

    argv = (char**)malloc(argc * sizeof(char*));

    arg = command_line;
    index = 1;

    while (arg[0] != 0) {

        while (arg[0] != 0 && arg[0] == ' ') {
            arg++;
        }

        if (arg[0] != 0) {

            argv[index] = arg;
            index++;

            while (arg[0] != 0 && arg[0] != ' ') {
                arg++;
            }

            if (arg[0] != 0) {
                arg[0] = 0;
                arg++;
            }

        }

    }

    // put the program name into argv[0]

    char filename[_MAX_PATH];

    GetModuleFileName(NULL, filename, _MAX_PATH);
    argv[0] = filename;

    // call the user specified main function

    result = main(argc, argv);

    free(argv);
    return result;

}
#endif
