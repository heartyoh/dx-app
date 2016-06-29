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

#ifndef __DX_VIDEO_V4L2_H
#define __DX_VIDEO_V4L2_H

int dx_video_v4l2_open(char* dev_name, int* fd);
int dx_video_v4l2_close(int fd);
int dx_video_v4l2_set_fmt(int fd, char* fourcc, int* width, int* height);
int dx_video_v4l2_init_mmap(int fd, uint8_t** buffer, int* size);
int dx_video_v4l2_capture_image(int fd, uint8_t* buffer);

#endif /* __DX_VIDEO_V4L2_H */
