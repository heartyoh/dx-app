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

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

#include "dx-core.h"
#include "dx-video-v4l2.h"

int dx_video_v4l2_open(char* dev_name, int* fd) {
	struct stat st;

	if (-1 == stat(dev_name, &st)) {
		ERROR("Cannot identify '%s': %d, %s\n", dev_name, errno,
				strerror(errno));
		return -1;
	}

	if (!S_ISCHR(st.st_mode)) {
		ERROR("%s is no device\n", dev_name);
		return -1;
	}

	*fd = open(dev_name, O_RDWR /* required */| O_NONBLOCK, 0);

	if (-1 == *fd) {
		ERROR("Cannot open '%s': %d, %s\n", dev_name, errno,
				strerror(errno));
		return -1;
	}

	return 0;
}

int dx_video_v4l2_close(int fd) {
	close(fd);
	return 0;
}

int dx_video_v4l2_init_mmap(int fd, uint8_t** buffer, int* size) {
    struct v4l2_requestbuffers req = {0};
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == dx_ioctl(fd, VIDIOC_REQBUFS, &req)) {
        ERROR("Requesting Buffer");
        return 1;
    }

    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if(-1 == dx_ioctl(fd, VIDIOC_QUERYBUF, &buf)) {
        ERROR("Querying Buffer");
        return 1;
    }

    *buffer = mmap (NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
	*size = buf.bytesused;

    CONSOLE("Length: %d\nAddress: %p\n", buf.length, buffer);
    CONSOLE("Image Length: %d\n", buf.bytesused);

    return 0;
}

int dx_video_v4l2_capture_image(int fd, uint8_t* buffer) {
    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if(-1 == dx_ioctl(fd, VIDIOC_QBUF, &buf)) {
        ERROR("Query Buffer");
        return 1;
    }

    if(-1 == dx_ioctl(fd, VIDIOC_STREAMON, &buf.type)) {
    	ERROR("Start Capture Error %d, %s", errno, strerror(errno));
    	if(errno == EIO)
    		ERROR("You may run this program on virtual machine.")
        return 1;
    }

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    struct timeval tv = {0};
    tv.tv_sec = 2;
    int r = select(fd+1, &fds, NULL, NULL, &tv);
    if(-1 == r) {
    	ERROR("Waiting for Frame");
        return 1;
    }

    if(-1 == dx_ioctl(fd, VIDIOC_DQBUF, &buf)) {
    	ERROR("Retrieving Frame");
        return 1;
    }

    int outfd = open("out.img", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(outfd < 0) {
    	ERROR("File open error : %d, %s", errno, strerror(errno));
    	return 1;
    }
    CONSOLE("Trying to write image file (size: %d)", buf.bytesused);
    write(outfd, buffer, buf.bytesused);
    close(outfd);

    return 0;
}

