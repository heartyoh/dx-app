if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib/dx-core -I$(top_srcdir)/src/lib/dx-video -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib/dx-core -I$(top_srcdir)/src/lib/dx-video -Wall -O3
endif

THREAD_CFLAGS = -pthread
THREAD_LIBS = -lpthread

AM_CFLAGS += $(THREAD_CFLAG)
AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SQLITE3_CFLAGS)

bin_PROGRAMS = dx-app
dx_app_SOURCES = main.c

dx_app_LDADD = $(top_builddir)/src/lib/dx-core/libdx-core.a $(AM_LDFLAGS)
dx_app_LDADD += $(top_builddir)/src/lib/dx-video/libdx-video.a $(AM_LDFLAGS)
dx_app_LDADD += $(THREAD_LIBS)
dx_app_LDADD += $(GLIB_LIBS)
dx_app_LDADD += $(SQLITE3_LIBS)
