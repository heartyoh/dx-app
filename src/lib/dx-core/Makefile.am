if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib/dx-core -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib/dx-core -Wall
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SQLITE3_CFLAGS)

# The libraries to build
noinst_LIBRARIES = libdx-core.a
noinst_HEADERS = dx_debug_assert.h \
                 dx_debug_malloc.h \
                 dx_util_lock.h \
                 dx_util_log.h \
                 dx_util_buffer.h \
                 dx_util_schedule.h \
                 dx_util_list.h \
                 dx_util_clock.h \
                 dx_util_file.h \
                 dx_util_ioctl.h \
                 dx_event_control.h \
                 dx_event_mplexer.h \
                 dx_event_pipe.h \
                 dx_console.h \
                 dx-core.h

# The files to add to the library and to the source distribution
libdx_core_a_SOURCES = $(noinst_HEADERS) \
                  dx_debug_malloc.c \
                  dx_util_buffer.c \
                  dx_util_schedule.c \
                  dx_util_clock.c \
                  dx_util_file.c \
                  dx_util_list.c \
                  dx_util_lock.c \
                  dx_util_log.c \
                  dx_util_ioctl.c \
                  dx_event_control.c \
                  dx_event_mplexer.c \
                  dx_event_pipe.c \
                  dx_console.c
