#include "demo.h"

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

extern int camera_fd;
extern int demo_camera_check_open();

dx_video_yuv_t* i420 = NULL;

int width = 640;
int height = 480;
int framerate = 30;

int i420_fd = -1;

int demo_camera_x264_handler(dx_event_context_t* pcontext, void* pdata) {

	dx_video_yuv_t* yuyv = pdata;

	if(i420 == NULL) {
		i420 = dx_video_yuv_create(DX_YUV_TYPE_I420, width * 2, height * 2);

		dx_video_yuv_alloc_buffer(i420, 0, -1, 0);

		//i420_fd = open("640x480.i420", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		i420_fd = open("1280x960.i420", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(i420_fd < 0) {
			ERRORNO("File open error");
			return 1;
		}
	}

	//dx_video_yuv_convert(yuyv, i420);

	CONSOLE("SIZE %d\n", i420->buffer_size);

	dx_video_yuv_t* srcs[] = { yuyv, yuyv, yuyv, yuyv };
	dx_video_yuv_merge(srcs, i420, 2, 2);


	write(i420_fd, i420->buffer, i420->buffer_size);

	return 0;
}

void demo_camera_x264_start(char* cmdline) {

	if(demo_camera_check_open())
		return;

	dx_camera_set_fmt(camera_fd, "YUYV", &width, &height, &framerate);

	dx_camera_capture_start(camera_fd, demo_camera_x264_handler);
}
