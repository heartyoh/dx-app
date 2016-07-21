#include "demo.h"

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#define CAMERA_COUNT 4
#define ROWS 2
#define COLUMNS 2

int camera_fds[] = {-1, -1, -1, -1};

dx_video_yuv_t* yuyv_2ch[] = {NULL, NULL, NULL, NULL};
dx_video_yuv_t* i420_2ch = NULL;

int width_2ch = 640;
int height_2ch = 480;
int framerate_2ch = 15;

int i420_2ch_fd = -1;

dx_schedule_t* demo_2ch_stream_schedule = NULL;

int demo_2ch_open_camera(char* path, int *camera_fd) {

	CONSOLE("%s 장치를 오픈합니다.\n", path);
	dx_camera_open(path, camera_fd);
	if(*camera_fd == -1) {
		ERROR("Camera Device(%s) 오픈에 실패하였습니다.", path);
		return -1;
	}
	return 0;
}

int demo_2ch_close_camera(int* camera_fd) {
	if(*camera_fd == -1)
		return 0;
	dx_camera_close(*camera_fd);
	*camera_fd = -1;
	return 0;
}

void demo_2ch_close(char* cmdline) {
	for(int i = 0;i < CAMERA_COUNT;i++) {
		demo_2ch_close_camera(&camera_fds[i]);
	}
	return;
}

void demo_2ch_open(char* cmdline) {

	demo_2ch_close(NULL);

	char path[20];

	for(int i = 0;i < CAMERA_COUNT;i++) {
		memset(path, 0x0, 20);
		sprintf(path, "/dev/video%d", i);
		if(demo_2ch_open_camera(path, camera_fds + i)) {
			return;
		}
	}
}

int demo_2ch_check_open() {
	for(int i = 0;i < CAMERA_COUNT;i++) {
		if(camera_fds[i] == -1) {
			ERROR("Camera %d Open Please.", i);
			return -1;
		}
	}

	return 0;
}

void demo_2ch_stop(char* cmdline) {
	if(demo_2ch_stream_schedule != NULL && demo_2ch_stream_schedule->next_schedule != 0) {
		/* 스케쥴러를 취소합니다. */
		dx_schedule_cancel(demo_2ch_stream_schedule);
		demo_2ch_stream_schedule = NULL;
	}

	for(int i = 0;i < CAMERA_COUNT;i++) {
		if(camera_fds[i] != -1) {
			dx_camera_capture_stop(camera_fds[i]);
		}
	}
}

int _xxxx = 0;
clock_t _start_time = 0;

int demo_2ch_schedule_callback(void* pdata) {

	if(++_xxxx % 10 == 0) {
		CONSOLE("2CH Handler [%d : %d]\n", _xxxx, _xxxx / ((clock() - _start_time) / CLOCKS_PER_SEC));
	}

	dx_video_yuv_merge(yuyv_2ch, i420_2ch, ROWS, COLUMNS);

	write(i420_2ch_fd, i420_2ch->buffer, i420_2ch->buffer_size);

	//CONSOLE("Done.\n");
	return 0;
}

int demo_2ch_handler(dx_event_context_t* pcontext, void* pdata) {
	//dx_video_yuv_t* yuyv = pdata;
	/*
	if(pcontext->fd == camera_fds[1]) {
		CONSOLE("2CH Handler [%d]...\n", _xxxx++);
		dx_video_yuv_merge(yuyv_2ch, i420_2ch, ROWS, COLUMNS);
		//write(i420_2ch_fd, i420_2ch->buffer, i420_2ch->buffer_size);
		//CONSOLE("Done.\n");
	}
	*/

	CONSOLE("-----%d-----\n", pcontext->fd);
		
	return 0;
}

void demo_2ch_start(char* cmdline) {

	if(demo_2ch_check_open())
		return;

	i420_2ch_fd = open("1280x480.i420", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(i420_2ch_fd < 0) {
		ERRORNO("File open error");
		return;
	}

	i420_2ch = dx_video_yuv_create(DX_YUV_TYPE_I420, width_2ch * COLUMNS, height_2ch * ROWS);
	dx_video_yuv_alloc_buffer(i420_2ch, 0, -1, 0);

	CONSOLE("Start Capture from 4CH Cameras...");
	for(int i = 0;i < CAMERA_COUNT;i++) {
		int width = width_2ch;
		int height = height_2ch;
		int framerate = framerate_2ch;
		dx_camera_set_fmt(camera_fds[i], "YUYV", &width, &height, &framerate);
		dx_camera_capture_start(camera_fds[i], demo_2ch_handler);
		yuyv_2ch[i] = dx_get_event_context(camera_fds[i])->pdata;
	}
	CONSOLE("Done\n");

	/* 만약 현재 동작중인 스케쥴러가 있으면, 동작하지 않음 */
	if(demo_2ch_stream_schedule != NULL && demo_2ch_stream_schedule->next_schedule != 0) {
		ERROR("이미 동작중인 스트리밍 스케쥴러가 있습니다.");
		return;
	}

	/* 새로운 스트리밍 스케쥴러를 등록하고, 바로 시작합니다. */
	demo_2ch_stream_schedule = dx_schedule_register(0, 1000 / 30 /* 30 frames */, 1, demo_2ch_schedule_callback, (void*)NULL);
	dx_event_mplexer_wakeup();

	_start_time = clock();
}
