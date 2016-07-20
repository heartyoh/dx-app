#include "demo.h"

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

extern int camera_fds[];
extern int demo_4ch_check_open();

dx_video_yuv_t* yuyv_4ch[] = {NULL, NULL, NULL, NULL};
dx_video_yuv_t* i420_4ch = NULL;

int width_4ch = 640;
int height_4ch = 480;

int i420_4ch_fd = -1;

int demo_4ch_x264_handler(dx_event_context_t* pcontext, void* pdata) {

	//dx_video_yuv_t* yuyv = pdata;

	CONSOLE("4CH Handler for %d...\n", pcontext->fd);

	CONSOLE("Start Merge...\n");
	for(int i = 0;i < 4;i++) {
		if(yuyv_4ch[i])
			CONSOLE("%d : %d.\n", i, yuyv_4ch[i]->buffer_size);
	}
//	dx_video_yuv_merge(yuyv_4ch, i420_4ch, 2, 2);

	CONSOLE("Write for i420_4CH ... %d\n", i420_4ch->buffer_size);
//	write(i420_4ch_fd, i420_4ch->buffer, i420_4ch->buffer_size);

	CONSOLE("Done.\n");
	return 0;
}

int demo_4ch_x264_start(char* cmdline) {

	if(demo_4ch_check_open())
		return -1;

	i420_4ch_fd = open("1280x960.i420", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(i420_4ch_fd < 0) {
		ERRORNO("File open error");
		return 1;
	}

	i420_4ch = dx_video_yuv_create(DX_YUV_TYPE_I420, width_4ch * 2, height_4ch * 2);
	dx_video_yuv_alloc_buffer(i420_4ch, 0, -1, 0);

	CONSOLE("Start Capture from 4CH Cameras...");
	for(int i = 0;i < 4;i++) {
		dx_camera_set_fmt(camera_fds[i], "YUYV", &width_4ch, &height_4ch);
		dx_camera_capture_start(camera_fds[i], demo_4ch_x264_handler);
		yuyv_4ch[i] = dx_get_event_context(camera_fds[i])->pdata;
	}
	CONSOLE("Done\n");

	return 0;
}
