AC_INIT([rhasher], [1.0], [egor.mikheev32@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_PROG_CC
AC_PROG_INSTALL

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([RHASH], [librhash])

AC_ARG_WITH([readline],
    [AS_HELP_STRING([--without-readline], [Build without readline support])],
    [with_readline=$withval],
    [with_readline=yes])

have_readline=no
if test "x$with_readline" != xno; then
    PKG_CHECK_MODULES([READLINE], [readline], [
        AC_DEFINE([USE_READLINE], [1], [Use readline])
        have_readline=yes
    ], [
        if test "x$with_readline" = xyes; then
            AC_MSG_ERROR([readline requested but not found])
        fi
    ])
fi

AM_CONDITIONAL([USE_READLINE], [test "x$have_readline" = xyes])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
