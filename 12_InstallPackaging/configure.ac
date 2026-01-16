#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Romanizer], [1.0], [j2m@off.com], [romanizer])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/romanizer.c])
AC_CONFIG_HEADERS([config.h])
DX_INIT_DOXYGEN(romanizer)

# Check for gettext
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)

# Checks for programs.
AC_PROG_CC
LT_INIT

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([locale.h wchar.h libintl.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_TYPES([wint_t])

# Checks for library functions.
AC_CHECK_FUNCS([setlocale fputwc fgetwc fputws])

PKG_CHECK_MODULES([CHECK], [check])

AC_CONFIG_FILES([
    Makefile
    Doxyfile
    src/Makefile
    po/Makefile.in
    tests/Makefile
])

AC_OUTPUT
