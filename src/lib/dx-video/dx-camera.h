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

#ifndef __DX_CAMERA_H
#define __DX_CAMERA_H

/*
 * Definitions
 */

typedef int(*dx_camera_event_handler)(dx_event_context_t* pcontext, void* pdata);

/* APIs */

int dx_camera_open(char* dev_name, int* fd);
int dx_camera_close(int fd);
int dx_camera_set_fmt(int fd, char* fourcc, int* width, int* height);
int dx_camera_req_bufs(int fd, int count);
int dx_camera_capture_image(int fd, uint8_t* buffer);
int dx_camera_stream_on(int fd); 
int dx_camera_stream_off(int fd);
int dx_camera_capture_start(int fd, dx_camera_event_handler handler);

#endif /* __DX_CAMERA_H */
