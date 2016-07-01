#ifndef _DX_VIDEO_YUV_CONVERT_H
#define _DX_VIDEO_YUV_CONVERT_H

int dx_video_yuv_convert(dx_video_yuv_t* src, dx_video_yuv_t* dest);
int dx_video_yuv_merge(dx_video_yuv_t** srcs, dx_video_yuv_t* dest, int rows, int cols);

#endif //_DX_VIDEO_YUV_CONVERT_H
