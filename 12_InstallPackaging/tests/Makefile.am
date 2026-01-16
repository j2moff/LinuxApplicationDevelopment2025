TESTS = dict
check_PROGRAMS = dict

.ts.c:
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libromanizer.la @CHECK_LIBS@
