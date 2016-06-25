if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -O3
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SQLITE3_CFLAGS)

bin_PROGRAMS = dx-app
dx_app_SOURCES = main.c

dx_app_LDADD = $(top_builddir)/src/lib/libdx.a $(AM_LDFLAGS)
dx_app_LDADD += $(GLIB_LIBS)
dx_app_LDADD += $(SQLITE3_LIBS)
