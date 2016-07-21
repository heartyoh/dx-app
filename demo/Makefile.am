AM_CFLAGS = -I$(top_srcdir)/demo
AM_CFLAGS += -I$(top_srcdir)/src/lib/dx-core
AM_CFLAGS += -I$(top_srcdir)/src/lib/dx-net
AM_CFLAGS += -I$(top_srcdir)/src/lib/dx-parser
AM_CFLAGS += -I$(top_srcdir)/src/lib/dx-video

if DEBUG
  AM_CFLAGS += -Wall -g -O3
else
  AM_CFLAGS += -Wall -O3
endif

THREAD_CFLAGS = -pthread
THREAD_LIBS = -lpthread

AM_CFLAGS += $(THREAD_CFLAG)
AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SQLITE3_CFLAGS)

bin_PROGRAMS = dx-demo
dx_demo_SOURCES = main.c \
                  demo_console_menu_camera.c \
                  demo_console_menu_camera_x264.c \
                  demo_console_menu_2ch.c \
                  demo_console_menu_client.c \
                  demo_console_menu_movie.c \
                  demo_console_menu_server.c \
                  demo_console_menu_start.c \
                  demo_console_menu_video_file.c \
                  server_handler_event.c \
                  client_handler_event.c \
                  server_handler_file.c \
                  client_handler_file.c \
                  server_handler_get_setting.c \
                  client_handler_get_setting.c \
                  server_handler_get_state.c \
                  client_handler_get_state.c \
                  server_handler_hb.c \
                  client_handler_hb.c \
                  server_handler_movie.c \
                  client_handler_movie.c \
                  server_handler_set_setting.c \
                  client_handler_set_setting.c \
                  server.c \
                  server_handler_set_state.c \
                  client_handler_set_state.c \
                  server_handler.c \
                  client.c \
                  client_handler_stream.c \
                  server_handler_command.c \
                  client_handler.c \
                  server_handler_command_playback.c \
                  server_handler_command_live.c \
                  client_handler_command.c

dx_demo_LDADD = $(top_builddir)/src/lib/dx-core/libdx-core.a
dx_demo_LDADD += $(top_builddir)/src/lib/dx-net/libdx-net.a
dx_demo_LDADD += $(top_builddir)/src/lib/dx-parser/libdx-parser.a
dx_demo_LDADD += $(top_builddir)/src/lib/dx-video/libdx-video.a
dx_demo_LDADD += $(AM_LDFLAGS)
dx_demo_LDADD += $(THREAD_LIBS)
dx_demo_LDADD += $(GLIB_LIBS)
dx_demo_LDADD += $(SQLITE3_LIBS)
