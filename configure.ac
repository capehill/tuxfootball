AC_PREREQ([2.67])
AC_INIT([tuxfootball], [0.3.1], http://tuxfootball.sourceforge.net/)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION, [dist-bzip2])
AM_MAINTAINER_MODE
AM_GNU_GETTEXT([external])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES(SDL2, [sdl2 >= 2.0.0])
AC_SUBST(SDL2_CFLAGS)
AC_SUBST(SDL2_LIBS)

PKG_CHECK_MODULES(SDL2_IMAGE, [SDL2_image >= 2.0.0])
AC_SUBST(SDL2_IMAGE_CFLAGS)
AC_SUBST(SDL2_IMAGE_LIBS)

PKG_CHECK_MODULES(SDL2_MIXER, [SDL2_mixer >= 2.0.0])
AC_SUBST(SDL2_MIXER_CFLAGS)
AC_SUBST(SDL2_MIXER_LIBS)

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([atexit pow sqrt])


AC_CONFIG_FILES([Makefile
                 tuxfootball.desktop
                 data/Makefile
                 data/graphics/Makefile
                 data/graphics/team1/Makefile
                 data/graphics/team1_goalie/Makefile
                 data/graphics/team2/Makefile
                 data/graphics/team2_goalie/Makefile
                 po/Makefile.in
                 src/Makefile])
AC_OUTPUT

AC_MSG_RESULT([Configuration successful! Now type 'make'.])
