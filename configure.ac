AC_INIT([ur], [1.0], [andrew@orospakr.ca])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
])
dnl Check for SDL 1.2
PKG_CHECK_MODULES([SDL], [sdl >= 1.2.0])

dnl After PKG_CHECK_MODULES we now need to set the include path and library path from it.

AM_CXXFLAGS="$AM_CXXFLAGS $SDL_CFLAGS"
AM_LDFLAGS="$AM_LDFLAGS $SDL_LIBS"

AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])
    
AC_OUTPUT
