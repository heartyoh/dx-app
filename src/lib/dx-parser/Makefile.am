if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib/dx-core -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib/dx-core -Wall
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SQLITE3_CFLAGS)

# The libraries to build
noinst_LIBRARIES = libdx-parser.a
noinst_HEADERS = dx-parser.h \
                 dx_file_avi.h \
                 dx_file_movie.h 

# The files to add to the library and to the source distribution
libdx_parser_a_SOURCES = $(libdx_parser_a_HEADERS) \
                  dx_file_avi.c \
                  dx_file_avi_parser.c \
                  dx_file_movie.c
