if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib/dx-core -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib/dx-core -Wall
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SQLITE3_CFLAGS)

# The libraries to build
noinst_LIBRARIES = libdx-net.a
noinst_HEADERS = dx-net.h \
                 dx_net_discovery.h \
                 dx_net_packet_movie_playback.h \
                 dx_net.h \
                 dx_net_server.h \
                 dx_net_packet_camera_preview.h \
                 dx_net_packet_file.h \
                 dx_net_client.h \
                 dx_net_packet.h \
                 dx_net_dgram.h \
                 dx_net_packet_io.h

# The files to add to the library and to the source distribution
libdx_net_a_SOURCES = $(libdx_net_a_HEADERS) \
                  dx_net_packet.c \
                  dx_net_packet_camera_preview.c \
                  dx_net_packet_file.c \
                  dx_net_client.c \
                  dx_net_packet_io.c \
                  dx_net_dgram.c \
                  dx_net_packet_movie_playback.c \
                  dx_net_discovery.c \
                  dx_net_server.c
