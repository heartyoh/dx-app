// Copyright (c) 2015 - 2015 All Right Reserved, http://hatiolab.com
//
// This source is subject to the Hatio Lab. Permissive License.
// Please see the License.txt file for more information.
// All other rights reserved.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WIHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

#include "demo-const.h"

//dx_movie_context_t* demo_live_context = NULL;
int live_camera_fd = -1;
dx_schedule_t* demo_live_stream_schedule = NULL;

int demo_live_stream_idx = 0;

uint8_t* demo_live_buffer = NULL;
struct v4l2_buffer demo_live_v4l2_buffer = {0};

int demo_live_schedule_callback(void* sender_fd) {

	while(1) {

		/*
		 * TODO 여기서 프레임버퍼로 Capture
		 */

		dx_camera_capture_image(live_camera_fd, demo_live_buffer);

		if(demo_live_buffer == NULL)
			demo_live_buffer = MALLOC(3 * 1024 * 1024);

		if(-1 == dx_packet_send_stream((int)sender_fd, DX_STREAM_LIVE, 0 /* enctype */,
			0, demo_live_stream_idx++, demo_live_buffer, demo_live_v4l2_buffer.bytesused)) {
			/* Network Error */
			break;
		}

		return 0;
	}

	demo_live_stream_idx = 0;
	dx_schedule_cancel(demo_live_stream_schedule);

	if(demo_live_buffer != NULL) {
		FREE(demo_live_buffer);
		demo_live_buffer = NULL;
	}

	CONSOLE("Live Stream End.\n");
	return 0;
}

void demo_on_live_start(int fd) {

	/* 만약 현재 동작중인 스케쥴러가 있으면, 동작하지 않음 */
	if(demo_live_stream_schedule != NULL && demo_live_stream_schedule->next_schedule != 0) {
		ERROR("이미 동작중인 스트리밍 스케쥴러가 있습니다.");
		return;
	}

	if(live_camera_fd != -1) {
		dx_camera_close(live_camera_fd);
		CONSOLE("현재 열려있는 비디오 파일을 닫았습니다.\n");
		live_camera_fd = -1;
	}

	demo_live_stream_idx = 0;

	// Camera Open
	dx_camera_open("/dev/video0", &live_camera_fd);

	if(live_camera_fd == -1) {
		ERROR("동영상 파일 오픈에 실패하였습니다.");
		return;
	}

//    demo_live_v4l2_buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    demo_live_v4l2_buffer.memory = V4L2_MEMORY_MMAP;
//    demo_live_v4l2_buffer.index = 0;
//    if(-1 == dx_ioctl(fd, VIDIOC_QBUF, &demo_live_v4l2_buffer)) {
//        ERROR("Query Buffer");
//        return 1;
//    }

	// Start Stream
	dx_camera_stream_on(live_camera_fd);

	/* 새로운 스트리밍 스케쥴러를 등록하고, 바로 시작합니다. */
	demo_live_stream_schedule = dx_schedule_register(0, 1000/30 /* 30 frames */, 1, demo_live_schedule_callback, (void*)fd);
	dx_event_mplexer_wakeup();
}

void demo_on_live_stop(int fd) {
	if(demo_live_stream_schedule != NULL && demo_live_stream_schedule->next_schedule != 0) {
		/* 스케쥴러를 취소합니다. */
		dx_schedule_cancel(demo_live_stream_schedule);
		demo_live_stream_schedule = NULL;
	}

	if(live_camera_fd != -1) {
		dx_camera_stream_off(live_camera_fd);
		dx_camera_close(live_camera_fd);
		live_camera_fd = -1;
	}

	demo_live_stream_idx = 0;
}
