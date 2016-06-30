#include "demo.h"

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

int camera_fd = -1;
struct v4l2_buffer v4l2_buffer = {0};

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

int demo_camera_capture_user_handler(dx_event_context_t* pcontext, void* buf) {
	CONSOLE("CAPTURE Event .....\n");
	return 1;
}

void demo_camera_capture(char* cmdline) {
	if(demo_camera_check_open())
		return;

	dx_camera_capture_start(camera_fd, demo_camera_capture_user_handler);

	/*
	dx_video_yuv_t* yuv = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 640, 480);

	uint8_t* buffer;
	int size;

	if(dx_camera_req_bufs(camera_fd, 1))
		return;

	if(dx_camera_query_buf(camera_fd, &buffer, &size))
		return;

	dx_video_yuv_alloc_buffer(yuv, buffer, size);

	dx_camera_capture_image(camera_fd, yuv->buffer);
	*/
}

void demo_camera_start_streaming(char* cmdline) {
	if(demo_camera_check_open())
		return;

//	memset(&v4l2_buffer, 0, sizeof(v4l2_buffer));
//
//  v4l2_buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//	v4l2_buffer.memory = V4L2_MEMORY_MMAP;
//	v4l2_buffer.index = 0;

	dx_camera_stream_on(camera_fd);

//    if(dx_ioctl(camera_fd, VIDIOC_QBUF, &v4l2_buffer)) {
//        ERROR("Query Buffer");
//        return 1;
//    }
}

void demo_camera_stop_streaming(char* cmdline) {
	if(demo_camera_check_open())
		return;

//	if(dx_ioctl(camera_fd, VIDIOC_DQBUF, &v4l2_buffer)) {
//        ERROR("DQ Buffer");
//        return 1;
//	}

	dx_camera_stream_off(camera_fd);
}
