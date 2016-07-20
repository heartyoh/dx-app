#include "demo.h"

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

int camera_fds[] = {-1, -1, -1, -1};

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

int demo_4ch_close(char* cmdline) {
	for(int i = 0;i < 4;i++) {
		demo_4ch_close_camera(&camera_fds[i]);
	}
	return 0;
}

int demo_4ch_open(char* cmdline) {

	demo_4ch_close(NULL);

	char path[20];

	for(int i = 0;i < 4;i++) {
		memset(path, 0x0, 20);
		sprintf(path, "/dev/video%d", i);
		if(demo_4ch_open_camera(path, camera_fds + i)) {
			return -1;
		}
	}

	return 0;
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
	for(int i = 0;i < 4;i++) {
		if(camera_fds[i] != -1) {
			dx_camera_capture_stop(camera_fds[i]);
		}
	}
}
