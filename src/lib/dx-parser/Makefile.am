AM_CFLAGS = -I$(top_srcdir)/src/lib/dx-core
AM_CFLAGS += -I$(top_srcdir)/src/lib/dx-net

if DEBUG
  AM_CFLAGS += -Wall -g -O3
else
  AM_CFLAGS += -Wall -O3
endif

# The libraries to build
noinst_LIBRARIES = libdx-parser.a
noinst_HEADERS = dx-parser.h

# The files to add to the library and to the source distribution
libdx_parser_a_SOURCES = $(libdx_parser_a_HEADERS) \
                  dx_net_packet_movie_playback.c \
                  dx_file_avi.c \
                  dx_file_avi_parser.c \
                  dx_file_movie.c

libdx_net_a_LIBADD = $(top_builddir)/src/lib/dx-core/libdx-core.a
libdx_net_a_LIBADD += $(top_builddir)/src/lib/dx-core/libdx-net.a
libdx_net_a_LIBADD += $(AM_LDFLAGS)
