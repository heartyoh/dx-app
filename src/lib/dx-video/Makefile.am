if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib/dx-core -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib/dx-core -Wall
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SQLITE3_CFLAGS)

# The libraries to build
noinst_LIBRARIES = libdx-video.a
noinst_HEADERS = dx-video.h

# The files to add to the library and to the source distribution
libdx_video_a_SOURCES = $(libdx_video_a_HEADERS) \
                        dx-video.c \
                        dx-video-yuv.c \
                        dx-video-yuv-convert.c \
                        dx-video-v4l2.c \
                        dx-video-v4l2-query.c 
