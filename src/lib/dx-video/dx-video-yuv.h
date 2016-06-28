#ifndef _DX_VIDEO_YUV 
#define _DX_VIDEO_YUV

/* YUV Format Definitions */

#define DX_YUV_FORMAT_PACKED					0x00
#define DX_YUV_FORMAT_PLANAR_INTERLEAVED		0x01
#define DX_YUV_FORMAT_PLANAR_NON_INTERLEAVED	0x02

/* YUV Chroma Data Order */

#define DX_YUV_ORDER_UV	0x00
#define DX_YUV_ORDER_VU	0x01

/* YUV Types */

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

/* YUV format Specifications. */

typedef struct dx_video_yuv_spec {
	int format;
	int interleave_order;
	int sample_period_y_h;
	int sample_period_y_v;
	int sample_period_u_h;
	int sample_period_u_v;
	int sample_period_v_h;
	int sample_period_v_v;
	int stride_y;
	int stride_u;
	int stride_v;
} dx_video_yuv_spec_t;

/* YUV Buffer informations. */

typedef struct dx_video_yuv {
	int type;
	dx_video_yuv_spec_t* spec;
	int width;
	int height;
	int luma_size;
	int chroma_size;
	int buffer_allocated_by_self;
	int buffer_size;
	uint8_t* buffer;
	uint8_t* plane[4];
} dx_video_yuv_t;

/*
 * API Functions.
 */

dx_video_yuv_t* dx_video_yuv_create();
int dx_video_yuv_destroy(dx_video_yuv_t* yuv);

int dx_video_yuv_alloc_buffer(dx_video_yuv_t* yuv, uint8_t* buffer, int size);
int dx_video_yuv_fill_plane(dx_video_yuv_t* yuv, int plane_idx, uint8_t value);

int (*dx_video_yuv_capture)(dx_video_yuv_t* yuv);

#endif // _DX_VIDEO_YUV
