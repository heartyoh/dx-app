if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SQLITE3_CFLAGS)

# The libraries to build
noinst_LIBRARIES = libdx.a
noinst_HEADERS = dx.h \
                 dx_camera.h \
                 dx_event_pipe.h \
                 dx_net_discovery.h \
                 dx_net_packet_movie_playback.h \
                 dx_util_lock.h \
                 dx_console.h \
                 dx_file_avi.h \
                 dx_net.h \
                 dx_net_server.h \
                 dx_util_log.h \
                 dx_debug_assert.h \
                 dx_file_movie.h \
                 dx_net_packet_camera_preview.h \
                 dx_util_buffer.h \
                 dx_util_schedule.h \
                 dx_debug_malloc.h \
                 dx_net_packet_file.h \
                 dx_util_clock.h \
                 dx_v4l2.h \
                 dx_event_control.h \
                 dx_net_client.h \
                 dx_net_packet.h \
                 dx_util_file.h \
                 dx_event_mplexer.h \
                 dx_net_dgram.h \
                 dx_net_packet_io.h \
                 dx_util_list.h \
                 dx_util_ioctl.h

# The files to add to the library and to the source distribution
libdx_a_SOURCES = $(libdx_a_HEADERS) \
                  dx_camera.c \
                  dx_file_avi.c \
                  dx_net_packet.c \
                  dx_util_buffer.c \
                  dx_util_schedule.c \
                  dx_console.c \
                  dx_file_avi_parser.c \
                  dx_net_packet_camera_preview.c \
                  dx_util_clock.c \
                  dx_v4l2.c \
                  dx_debug_malloc.c \
                  dx_file_movie.c \
                  dx_net_packet_file.c \
                  dx_util_file.c \
                  dx_event_control.c \
                  dx_net_client.c \
                  dx_net_packet_io.c \
                  dx_util_list.c \
                  dx_event_mplexer.c \
                  dx_net_dgram.c \
                  dx_net_packet_movie_playback.c \
                  dx_util_lock.c \
                  dx_event_pipe.c \
                  dx_net_discovery.c \
                  dx_net_server.c \
                  dx_util_log.c \
                  dx_util_ioctl.c
