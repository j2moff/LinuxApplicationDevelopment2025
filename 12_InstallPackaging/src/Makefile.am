bin_PROGRAMS=romanizer

romanizer_SOURCES=romanizer.c
romanizer_LDADD = libromanizer.la

lib_LTLIBRARIES = libromanizer.la

libromanizer_la_SOURCES = dict.c dict.h

AM_CFLAGS=-D'LOCALE_PATH="$(localedir)"'
