#ifndef _DX_VIDEO_YUV
#define _DX_VIDEO_YUV

#define DX_YUV_TYPE_YUYV 	0x00
#define DX_YUV_TYPE_YUNV 	0x00
#define DX_YUV_TYPE_V422 	0x00
#define DX_YUV_TYPE_YUY2 	0x00

#define DX_YUV_TYPE_UYVY 	0x01
#define DX_YUV_TYPE_Y422 	0x01
#define DX_YUV_TYPE_UYNV 	0x01

#define DX_YUV_TYPE_YV12	0x02

#define DX_YUV_TYPE_NV12	0x03

#define DX_YUV_TYPE_NV21	0x04

#define DX_YUV_TYPE_IYUV	0x05
#define DX_YUV_TYPE_I420	0x05

typedef struct dx_video_yuv_spec {
	int sample_period_y_h;
	int sample_period_y_v;
	int sample_period_u_h;
	int sample_period_u_v;
	int sample_period_v_h;
	int sample_period_v_v;
} dx_video_yuv_spec_t;

typedef struct dx_video_yuv {
	int type;
	int width;
	int height;
	int luma_size;
	int chroma_size;
	int stride_y;
	int stride_u;
	int stride_v;
	uint8_t* buffer;
	uint8_t* plane[4];
} dx_video_yuv_t;

dx_video_yuv_t* dx_video_yuv_create();
int dx_video_yuv_destroy(dx_video_yuv_t* yuv);
int (*dx_video_yuv_capture)(dx_video_yuv_t* yuv);

#endif // _DX_VIDEO_YUV
