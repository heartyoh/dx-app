// Copyright (c) 2015 - 2015 All Right Reserved, http://hatiolab.com
//
// This source is subject to the Hatio, Lab. Permissive License.
// Please see the License.txt file for more information.
// All other rights reserved.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WIHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/epoll.h>

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

#include "dx-core.h"
#include "dx-camera.h"
#include "dx-video-yuv.h"

int dx_camera_readable_handler(dx_event_context_t* pcontext); 
int dx_camera_destroy_handler(void* pdata);

int dx_camera_open(char* dev_name, int* fd) {
	struct stat st;

	if (-1 == stat(dev_name, &st)) {
		ERRORNO("Cannot identify '%s'", dev_name);
		return -1;
	}

	if (!S_ISCHR(st.st_mode)) {
		ERROR("%s is no device\n", dev_name);
		return -1;
	}

	*fd = open(dev_name, O_RDWR /* required */| O_NONBLOCK, 0);

	if (-1 == *fd) {
		ERRORNO("Cannot open '%s'", dev_name );
		return -1;
	}

	return 0;
}

int dx_camera_close(int fd) {
	if(!CHECK_FILE_CLOSED(fd)) {
		close(fd);
	}

	return 0;
}

int dx_camera_set_fmt(int dev, char* fourcc, int* width, int* height, int* framerate) {
	struct v4l2_format fmt = {0};

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = *width;
	fmt.fmt.pix.height = *height;
	fmt.fmt.pix.pixelformat = v4l2_fourcc(fourcc[0], fourcc[1], fourcc[2], fourcc[3]);
	fmt.fmt.pix.field = V4L2_FIELD_NONE;

	if (IOCTL(dev, VIDIOC_S_FMT, &fmt)) {
		ERROR("Setting Pixel Format");
		return 1;
	}

	*width = fmt.fmt.pix.width;
	*height = fmt.fmt.pix.height;

	if(*framerate > 0) {
		struct v4l2_streamparm parm;

		parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		parm.parm.capture.timeperframe.numerator = 1;
		parm.parm.capture.timeperframe.denominator = *framerate;
		parm.parm.capture.capturemode = 0;
		if (IOCTL(dev, VIDIOC_S_PARM, &parm) < 0) {
		        ERROR("VIDIOC_S_PARM failed");
		        return 1;
		}
		*framerate = parm.parm.capture.timeperframe.denominator;
	}

	CONSOLE("Set Camera Format:\n"
			"  Width: %d\n"
			"  Height: %d\n"
			"  PixFmt: %.*s\n"
			"  Field: %d\n"
			"  FrameRate: %d\n",
			fmt.fmt.pix.width,
			fmt.fmt.pix.height,
			4,
			(char*)&fmt.fmt.pix.pixelformat,
			fmt.fmt.pix.field,
			*framerate);

	return 0;
}

int dx_camera_get_fmt(int dev, char* fourcc, int* width, int* height, int* framerate) {
	struct v4l2_format fmt = {0};
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (IOCTL(dev, VIDIOC_G_FMT, &fmt)) {
		ERROR("Getting Pixel Format");
		return 1;
	}

	memset(fourcc, 0x0, 5);
	strncpy(fourcc, (char*)&fmt.fmt.pix.pixelformat, 4); 
	*width = fmt.fmt.pix.width;
	*height = fmt.fmt.pix.height;

	struct v4l2_streamparm parm;

	parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (IOCTL(dev, VIDIOC_G_PARM, &parm) < 0) {
	        ERROR("VIDIOC_G_PARM failed");
	        return 1;
	}
	*framerate = parm.parm.capture.timeperframe.denominator;

	CONSOLE("Get Camera Format:\n"
			"  Width: %d\n"
			"  Height: %d\n"
			"  PixFmt: %.*s\n"
			"  Field: %d\n"
			"  FrameRate: %d\n",
			fmt.fmt.pix.width,
			fmt.fmt.pix.height,
			4,
			(char*)&fmt.fmt.pix.pixelformat,
			fmt.fmt.pix.field,
			*framerate);

	return 0;
}

int dx_camera_req_bufs(int fd, int count) {
    struct v4l2_requestbuffers req = {0};
    req.count = 0;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == dx_ioctl(fd, VIDIOC_REQBUFS, &req)) {
        ERROR("Release Buffer");
        return 1;
    }

    req.count = count;

    if (-1 == dx_ioctl(fd, VIDIOC_REQBUFS, &req)) {
        ERROR("Release Buffer");
        return 1;
    }

	return 0;
}

int dx_camera_query_buf(int fd, struct v4l2_buffer* buf) {

    if(-1 == dx_ioctl(fd, VIDIOC_QUERYBUF, buf)) {
        ERRORNO("Querying Buffer");
        return 1;
    }

	return 0;
}

int dx_camera_queue_buf(int fd, struct v4l2_buffer* buf) {

    if(dx_ioctl(fd, VIDIOC_QBUF, buf)) {
        ERRORNO("Queue Buffer");
        return 1;
    }

	return 0;
}

int dx_camera_dqueue_buf(int fd, struct v4l2_buffer* buf) {

    if(dx_ioctl(fd, VIDIOC_DQBUF, buf)) {
        ERRORNO("Dequeue Buffer");
        return 1;
    }

	return 0;
}

int dx_camera_stream_on(int fd) {
	int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(dx_ioctl(fd, VIDIOC_STREAMON, &type)) {
    	ERRORNO("Stream On");
    	if(errno == EIO)
    		ERROR("You may run this program on virtual machine.")
        return 1;
    }
	
	return 0;
}

int dx_camera_stream_off(int fd) {
	int type = V4L2_BUF_TYPE_VIDEO_CAPTURE; 

    if(dx_ioctl(fd, VIDIOC_STREAMOFF, &type)) {
    	ERRORNO("Stream Off");
        return 1;
    }
	
	return 0;
}

int dx_camera_capture_start(int fd, dx_camera_event_handler handler) {

	if(dx_camera_req_bufs(fd, 1))
		return 1;

	struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;

	if(dx_camera_query_buf(fd, &buf))
		return 1;

	CONSOLE("Query Buffer Size : %d\n", buf.length);

	char fourcc[5];
	int width = 0;
	int height = 0;
	int framerate = 0;

	if(dx_camera_get_fmt(fd, fourcc, &width, &height, &framerate)) {
		ERRORNO("Get Format ..");
		return 1;
	}

	int type = dx_video_yuv_get_type(fourcc);
	if(type == -1) {
		ERROR("Unknown YUV Type : [%s]", fourcc);
		return 1;
	}
	dx_video_yuv_t* yuv = dx_video_yuv_create(type, width, height);
	dx_video_yuv_alloc_buffer(yuv, buf.length, fd, buf.m.offset);

	dx_camera_queue_buf(fd, &buf);

	if(dx_camera_stream_on(fd))
		return 1;

	/* register event context */

	dx_event_context_t* pcontext = dx_event_context_create();

	pcontext->fd = fd;
	pcontext->readable_handler = dx_camera_readable_handler;
	pcontext->writable_handler = NULL;
	pcontext->error_handler = NULL;
	pcontext->pdata = yuv;
	pcontext->on_destroy = dx_camera_destroy_handler;

	pcontext->user_handler = handler;
	
	dx_add_event_context(pcontext, EPOLLIN);	

	return 0;
}

int dx_camera_capture_stop(int fd) {
	if(fd == -1)
		return 0;

	dx_camera_stream_off(fd);
	dx_camera_close(fd);

	dx_event_context_t* pcontext = dx_get_event_context(fd);
	if(pcontext)
		dx_del_event_context(pcontext);
	return 0;
}

int dx_camera_destroy_handler(void* yuv) {
	dx_video_yuv_destroy(yuv);
	return 0;
}

int dx_camera_readable_handler(dx_event_context_t* pcontext) {
	// pcontext->fd
	// pcontext->user_handler ..
	// 1. DQBUF
	// 2. call user_handler with buffer
	// 3. QBUF
	// 4. dx_del_event_context if user_handler returns the value other than 0
	//    - streamoff

	struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

	if(dx_camera_dqueue_buf(pcontext->fd, &buf))
		return 1;

	if(((dx_camera_event_handler) pcontext->user_handler)(pcontext, pcontext->pdata))
		return 1;

	dx_camera_queue_buf(pcontext->fd, &buf);

	return 0;
}
