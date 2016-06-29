#include "demo.h"

//dx_camera_context_t* demo_camera_context = NULL;
int camera_fd = -1;

void demo_camera_open(char* cmdline) {

	char* path = NULL;

	if(cmdline == NULL || (path = strtok(cmdline, " \t\n\f")) == NULL) {
		ERROR("오픈하고자 하는 Camera Device 이름을 입력해주세요.");
		return;
	}

	if(camera_fd != -1) {
		dx_video_v4l2_close(camera_fd);
		camera_fd = -1;
	}

	dx_video_v4l2_open(path, &camera_fd);

	if(camera_fd == -1) {
		ERROR("Camera Device 오픈에 실패하였습니다.");
		return;
	}
}

void demo_camera_close(char* cmdline) {
	if(camera_fd != -1) {
		dx_video_v4l2_close(camera_fd);
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

	dx_video_v4l2_query_cap(camera_fd);
}

void demo_camera_enum_fmt(char* cmdline) {
	if(demo_camera_check_open())
		return;

	dx_video_v4l2_enum_fmt(camera_fd);
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

	if(0 == dx_video_v4l2_set_fmt(camera_fd, fourcc, &width, &height))
		CONSOLE("Camera Pixel Format Set : %.*s, %d, %d\n", 4, fourcc, width, height);
}

void demo_camera_capture(char* cmdline) {
	if(demo_camera_check_open())
		return;

	dx_video_yuv_t* yuv = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 640, 480);

	uint8_t* buffer;
	int size;

	if(dx_video_v4l2_init_mmap(camera_fd, &buffer, &size))
		return;

	dx_video_yuv_alloc_buffer(yuv, buffer, size);

	dx_video_v4l2_capture_image(camera_fd, yuv->buffer);
}
