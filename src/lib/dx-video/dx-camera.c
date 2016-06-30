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

int dx_camera_readable_handler(dx_event_context_t* pcontext); 
int dx_camera_destroy_handler(void* pbuf);

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
	close(fd);
	return 0;
}

int dx_camera_set_fmt(int dev, char* fourcc, int* width, int* height) {
	struct v4l2_format fmt = {0};

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = *width;
	fmt.fmt.pix.height = *height;
	fmt.fmt.pix.pixelformat = v4l2_fourcc(fourcc[0], fourcc[1], fourcc[2], fourcc[3]);
	fmt.fmt.pix.field = V4L2_FIELD_NONE;

	if (-1 == IOCTL(dev, VIDIOC_S_FMT, &fmt)) {
		ERROR("Setting Pixel Format");
		return 1;
	}

	CONSOLE("Selected Camera Mode:\n"
			"  Width: %d\n"
			"  Height: %d\n"
			"  PixFmt: %.*s\n"
			"  Field: %d\n",
			fmt.fmt.pix.width,
			fmt.fmt.pix.height,
			4,
			(char*)&fmt.fmt.pix.pixelformat,
			fmt.fmt.pix.field);

	*width = fmt.fmt.pix.width;
	*height = fmt.fmt.pix.height;

	return 0;
}

int dx_camera_req_bufs(int fd, int count) {
    struct v4l2_requestbuffers req = {0};
    req.count = count;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == dx_ioctl(fd, VIDIOC_REQBUFS, &req)) {
        ERROR("Requesting Buffer");
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

int dx_camera_capture_image(int fd, uint8_t* buffer) {
//    struct v4l2_buffer buf = {0};
//    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    buf.memory = V4L2_MEMORY_MMAP;
//    buf.index = 0;
//    if(-1 == dx_ioctl(fd, VIDIOC_QBUF, &buf)) {
//        ERROR("Query Buffer");
//        return 1;
//    }
//
//	if(0 != dx_camera_stream_on(fd))
//		return 1;
//
//    fd_set fds;
//    FD_ZERO(&fds);
//    FD_SET(fd, &fds);
//    struct timeval tv = {0};
//    tv.tv_sec = 2;
//    int r = select(fd+1, &fds, NULL, NULL, &tv);
//    if(-1 == r) {
//    	ERROR("Waiting for Frame");
//        return 1;
//    }
//
//    if(-1 == dx_ioctl(fd, VIDIOC_DQBUF, &buf)) {
//    	ERROR("Retrieving Frame");
//        return 1;
//    }
//
//    int outfd = open("out.img", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
//    if(outfd < 0) {
//    	ERROR("File open error : %d, %s", errno, strerror(errno));
//    	return 1;
//    }
//    CONSOLE("Trying to write image file (size: %d)", buf.bytesused);
//    write(outfd, buffer, buf.bytesused);
//    close(outfd);
//
//	dx_camera_stream_off(fd);
//
    return 0;
}

int dx_camera_capture_start(int fd, dx_camera_event_handler handler) {

	if(dx_camera_req_bufs(fd, 1))
		return 1;

    struct v4l2_buffer* buf = MALLOC(sizeof(struct v4l2_buffer));
    buf->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf->memory = V4L2_MEMORY_MMAP;
    buf->index = 0;

	if(dx_camera_query_buf(fd, buf))
		return 1;

	if(dx_camera_queue_buf(fd, buf))
		return 1;

	if(dx_camera_stream_on(fd))
		return 1;

	/* register event context */

	dx_event_context_t* pcontext = dx_event_context_create();

	pcontext->fd = fd;
	pcontext->readable_handler = dx_camera_readable_handler;
	pcontext->writable_handler = NULL;
	pcontext->error_handler = NULL;
	pcontext->pdata = buf;
	pcontext->on_destroy = dx_camera_destroy_handler;

	pcontext->user_handler = handler;
	
	dx_add_event_context(pcontext, EPOLLIN);	

	return 0;
}

int dx_camera_destroy_handler(void* pbuf) {
	FREE(pbuf);
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

	dx_camera_dqueue_buf(pcontext->fd, pcontext->pdata);

	if(((dx_camera_event_handler) pcontext->user_handler)(pcontext, pcontext->pdata)) {
		dx_camera_stream_off(pcontext->fd);
		dx_del_event_context(pcontext);
		return 0;
	}

	dx_camera_queue_buf(pcontext->fd, pcontext->pdata);

	return 0;
}