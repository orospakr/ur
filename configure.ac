#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([ur], [0.1.0], [andrew@orospakr.ca])
AC_CONFIG_SRCDIR([src/ur.h])
AC_CONFIG_HEADERS([config.h])

# initialize automake
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP

# Checks for libraries.

# Checks for header files.


# Check for SDL 1.2 and openmpt using pkg-config
PKG_CHECK_MODULES([SDL], [sdl >= 1.2.0], [AC_DEFINE([HAVE_SDL], [1], [Define to 1 if you have the SDL library])], [AC_MSG_ERROR([SDL 1.2 not found])])
PKG_CHECK_MODULES([openmpt], [libopenmpt], [AC_DEFINE([HAVE_OPENMPT], [1], [Define to 1 if you have the libopenmpt library])], [AC_MSG_ERROR([libopenmpt not found])])

# putting --std++=c++17 here manually is a hack, with no autoconf checks for it. Too gross to do it properly,
# you have to add Autoconf Archive contrib macros.
AM_CXXFLAGS="-std=c++17 $AM_CXXFLAGS $SDL_CFLAGS $openmpt_CFLAGS"
AM_LDFLAGS="$AM_LDFLAGS $SDL_LIBS $openmpt_LIBS"

AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T



# Checks for library functions.
AC_CHECK_FUNCS([atexit])

AC_OUTPUT
