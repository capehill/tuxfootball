dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_PREREQ([2.67])
AC_INIT([tuxfootball], [0.1.1], http://tuxfootball.sourceforge.net/)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION, [dist-bzip2])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
IT_PROG_INTLTOOL([0.35.0])

# Checks for libraries.
PKG_CHECK_MODULES(SDL, [sdl >= 1.2.0])
AC_SUBST(SDL_CFLAGS)
AC_SUBST(SDL_LIBS)

AC_CHECK_LIB([SDL_image],
	[IMG_Load],
	LIBS="$LIBS -lSDL_image",
	[AC_MSG_ERROR([*** SDL_image library not found!])]
)

AC_CHECK_LIB([SDL_mixer], 
	[Mix_OpenAudio], 
	LIBS="$LIBS -lSDL_mixer", 
	[AC_MSG_ERROR([*** SDL_mixer library not found!])] 
)

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([atexit pow sqrt])


dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
AC_CHECK_HEADERS([libintl.h])
GETTEXT_PACKAGE=AC_PACKAGE_NAME
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE(GETTEXT_PACKAGE, "AC_PACKAGE_NAME", [foo])

AM_GLIB_GNU_GETTEXT

AM_PROG_LIBTOOL

AC_CONFIG_FILES([Makefile
                 data/Makefile
                 data/graphics/Makefile
                 po/Makefile.in
                 src/Makefile])
AC_OUTPUT

AC_MSG_RESULT([Configuration successful! Now type 'make'.])
