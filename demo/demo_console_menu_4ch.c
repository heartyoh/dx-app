#include "demo.h"

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

int camera_fds[] = {-1, -1, -1, -1};

dx_video_yuv_t* yuyv_4ch[] = {NULL, NULL, NULL, NULL};
dx_video_yuv_t* i420_4ch = NULL;

int width_4ch = 640;
int height_4ch = 480;

int i420_4ch_fd = -1;

dx_schedule_t* demo_4ch_stream_schedule = NULL;

int demo_4ch_open_camera(char* path, int *camera_fd) {

	CONSOLE("%s 장치를 오픈합니다.\n", path);
	dx_camera_open(path, camera_fd);
	if(*camera_fd == -1) {
		ERROR("Camera Device(%s) 오픈에 실패하였습니다.", path);
		return -1;
	}
	return 0;
}

int demo_4ch_close_camera(int* camera_fd) {
	if(*camera_fd == -1)
		return 0;
	dx_camera_close(*camera_fd);
	*camera_fd = -1;
	return 0;
}

void demo_4ch_close(char* cmdline) {
	for(int i = 0;i < 4;i++) {
		demo_4ch_close_camera(&camera_fds[i]);
	}
	return;
}

void demo_4ch_open(char* cmdline) {

	demo_4ch_close(NULL);

	char path[20];

	for(int i = 0;i < 4;i++) {
		memset(path, 0x0, 20);
		sprintf(path, "/dev/video%d", i);
		if(demo_4ch_open_camera(path, camera_fds + i)) {
			return;
		}
	}
}

int demo_4ch_check_open() {
	for(int i = 0;i < 4;i++) {
		if(camera_fds[i] == -1) {
			ERROR("Camera %d Open Please.", i);
			return -1;
		}
	}

	return 0;
}

void demo_4ch_stop(char* cmdline) {
	if(demo_4ch_stream_schedule != NULL && demo_4ch_stream_schedule->next_schedule != 0) {
		/* 스케쥴러를 취소합니다. */
		dx_schedule_cancel(demo_4ch_stream_schedule);
		demo_4ch_stream_schedule = NULL;
	}

//	for(int i = 0;i < 4;i++) {
//		if(camera_fds[i] != -1) {
//			dx_camera_capture_stop(camera_fds[i]);
//		}
//	}
}

int demo_4ch_capture_image(int fd) {

	struct v4l2_buffer buf = {0};
    	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    	buf.memory = V4L2_MEMORY_MMAP;
	buf.index = 0;

	dx_camera_queue_buf(fd, &buf);

    	if(-1 == IOCTL(fd, VIDIOC_STREAMON, &buf.type)) {
        	ERRORNO("Start Capture %d", fd);
	        return 1;
    	}

    	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(fd, &fds);
    	struct timeval tv = {0};
    	tv.tv_sec = 2;
    	int r = select(fd+1, &fds, NULL, NULL, &tv);
    	if(-1 == r) {
	        perror("Waiting for Frame");
       		return 1;
    	}

	if(dx_camera_dqueue_buf(fd, &buf))
		return 1;

    	if(-1 == IOCTL(fd, VIDIOC_STREAMOFF, &buf.type)) {
        	ERRORNO("Stop Capture");
	        return 1;
    	}

    	return 0;
}

int _xxxx = 0;
int demo_4ch_schedule_callback(void* pdata) {

	//dx_video_yuv_t* yuyv = pdata;

	CONSOLE("4CH Handler [%d]...\n", _xxxx++);

	for(int i = 0;i < 4;i++) {
		//if(yuyv_4ch[i])
		//	CONSOLE("%d : %d.\n", i, yuyv_4ch[i]->buffer_size);
		demo_4ch_capture_image(camera_fds[i]);
	}
	dx_video_yuv_merge(yuyv_4ch, i420_4ch, 2, 2);

//	CONSOLE("Write for i420_4CH ... %d\n", i420_4ch->buffer_size);
	write(i420_4ch_fd, i420_4ch->buffer, i420_4ch->buffer_size);

	CONSOLE("Done.\n");
	return 0;
}

int demo_4ch_ready(int fd, dx_video_yuv_t** pyuv) {

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

	if(dx_camera_get_fmt(fd, fourcc, &width, &height)) {
		ERRORNO("Get Format ..");
		return 1;
	}

	int type = dx_video_yuv_get_type(fourcc);
	if(type == -1) {
		ERROR("Unknown YUV Type : [%s]", fourcc);
		return 1;
	}
	*pyuv = dx_video_yuv_create(type, width, height);
	dx_video_yuv_alloc_buffer(*pyuv, buf.length, fd, buf.m.offset);

//	dx_camera_queue_buf(fd, &buf);

	return 0;
}

void demo_4ch_start(char* cmdline) {

	if(demo_4ch_check_open())
		return;

	i420_4ch_fd = open("1280x960.i420", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(i420_4ch_fd < 0) {
		ERRORNO("File open error");
		return;
	}

	i420_4ch = dx_video_yuv_create(DX_YUV_TYPE_I420, width_4ch * 2, height_4ch * 2);
	dx_video_yuv_alloc_buffer(i420_4ch, 0, -1, 0);

	CONSOLE("Start Capture from 4CH Cameras...");
	for(int i = 0;i < 4;i++) {
		dx_camera_set_fmt(camera_fds[i], "YUYV", &width_4ch, &height_4ch);
		demo_4ch_ready(camera_fds[i], &yuyv_4ch[i]);
//		dx_camera_capture_start(camera_fds[i], demo_4ch_x264_handler);
//		yuyv_4ch[i] = dx_get_event_context(camera_fds[i])->pdata;
	}
	CONSOLE("Done\n");

	/* 만약 현재 동작중인 스케쥴러가 있으면, 동작하지 않음 */
	if(demo_4ch_stream_schedule != NULL && demo_4ch_stream_schedule->next_schedule != 0) {
		ERROR("이미 동작중인 스트리밍 스케쥴러가 있습니다.");
		return;
	}

	/* 새로운 스트리밍 스케쥴러를 등록하고, 바로 시작합니다. */
	demo_4ch_stream_schedule = dx_schedule_register(0, 5000 /* 30 frames */, 1, demo_4ch_schedule_callback, (void*)NULL);
	dx_event_mplexer_wakeup();
}
