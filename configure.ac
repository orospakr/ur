#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([ur], [0.1.0], [andrew@orospakr.ca])
AC_CONFIG_SRCDIR([src/ur.h])
AC_CONFIG_HEADERS([config.h])

# initialize automake
AM_INIT_AUTOMAKE([-Wall -Werr foreign subdir-objects])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP

# Check for dependencies.
# Check for SDL 2.x, sdlimage 2.x, and openmpt using pkg-config
PKG_CHECK_MODULES([SDL2], [sdl2 >= 2.0.0], [AC_DEFINE([HAVE_SDL], [1], [Define to 1 if you have the SDL 2.9 library])], [AC_MSG_ERROR([SDL 2.x not found])])
PKG_CHECK_MODULES([SDL2_IMAGE], [sdl2_image >= 2.0.0], [AC_DEFINE([HAVE_SDL_IMAGE], [1], [Define to 1 if you have the sdl-image image library])], [AC_MSG_ERROR([SDL image not found])])
PKG_CHECK_MODULES([openmpt], [libopenmpt], [AC_DEFINE([HAVE_OPENMPT], [1], [Define to 1 if you have the libopenmpt library])], [AC_MSG_ERROR([libopenmpt not found])])

# putting --std++=c++17 here manually is a hack, with no autoconf checks for it. Too gross to do it properly,
# you have to add Autoconf Archive contrib macros.
AM_CXXFLAGS="-std=c++17 $AM_CXXFLAGS $SDL2_CFLAGS $SDL2_IMAGE_CFLAGS $openmpt_CFLAGS"
AM_LDFLAGS="$AM_LDFLAGS $SDL2_LIBS $SDL2_IMAGE_LIBS $openmpt_LIBS"

AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T

# Checks for library functions.
AC_CHECK_FUNCS([atexit])

AC_OUTPUT
