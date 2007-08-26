dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(tuxfootball, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC
AM_PROG_CC_C_O



dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
GETTEXT_PACKAGE=tuxfootball
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])



AM_PROG_LIBTOOL






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

AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
