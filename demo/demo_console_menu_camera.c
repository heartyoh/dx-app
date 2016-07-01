#include "demo.h"

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

int camera_fd = -1;

void demo_camera_open(char* cmdline) {

	char* path = NULL;

	if(cmdline == NULL || (path = strtok(cmdline, " \t\n\f")) == NULL) {
		path = "/dev/video0";
		CONSOLE("/dev/video0 장치를 오픈합니다.\n");
	}

	if(camera_fd != -1) {
		dx_camera_close(camera_fd);
		camera_fd = -1;
	}

	dx_camera_open(path, &camera_fd);

	if(camera_fd == -1) {
		ERROR("Camera Device 오픈에 실패하였습니다.");
		return;
	}
}

void demo_camera_close(char* cmdline) {
	if(camera_fd != -1) {
		dx_camera_close(camera_fd);
		camera_fd = -1;
	}
}

int demo_camera_check_open() {
	if(camera_fd == -1) {
		ERROR("Camera Open Please.");
		return 1;
	}

	return 0;
}

void demo_camera_query_cap(char* cmdline) {
	if(demo_camera_check_open())
		return;

	dx_camera_query_cap(camera_fd);
}

void demo_camera_enum_fmt(char* cmdline) {
	if(demo_camera_check_open())
		return;

	dx_camera_enum_fmt(camera_fd);
}

void demo_camera_set_fmt(char* cmdline) {
	if(demo_camera_check_open())
		return;

	char* fourcc = strtok(cmdline, " \t\n\f");
	char* str_width = strtok(NULL, " \t\n\f");
	char* str_height = strtok(NULL, " \t\n\f");

	int width, height;

	if(fourcc == NULL)
		fourcc = "YUYV";
	if(str_width == NULL)
		width = 640;
	else
		width = atoi(str_width);
	if(str_height == NULL)
		height = 480;
	else
		height = atoi(str_height);

	if(dx_camera_set_fmt(camera_fd, fourcc, &width, &height)) {
		ERROR("SETFMT");
		return;
	}

	CONSOLE("Camera Pixel Format Set : %.*s, %d, %d\n", 4, fourcc, width, height);
}

int demo_camera_capture_user_handler(dx_event_context_t* pcontext, void* pdata) {
	dx_video_yuv_t* yuv = (dx_video_yuv_t*)pdata;

	int outfd = open("out.img", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(outfd < 0) {
		ERRORNO("File open error");
		return 1;
	}

	CONSOLE("Trying to write image file (size: %d)", yuv->buffer_size);

	write(outfd, yuv->buffer, yuv->buffer_size);
	close(outfd);

	return 1; /* return 1 immediately, after save image file */
}

void demo_camera_capture_start(char* cmdline) {

	if(demo_camera_check_open())
		return;

	dx_camera_capture_start(camera_fd, demo_camera_capture_user_handler);
}

void demo_camera_stop(char* cmdline) {
	if(demo_camera_check_open())
		return;

	dx_camera_capture_stop(camera_fd);
}

int demo_camera_streaming_user_handler(dx_event_context_t* pcontext, void* pdata) {
	dx_video_yuv_t* yuv = (dx_video_yuv_t*)pdata;

	CONSOLE("STREAMING - BUFFER SIZE %d\n", yuv->buffer_size);

	return 0; /* run continously .. */
}

void demo_camera_streaming_start(char* cmdline) {
	if(demo_camera_check_open())
		return;

	dx_camera_capture_start(camera_fd, demo_camera_streaming_user_handler);
}
