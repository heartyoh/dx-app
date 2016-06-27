#include "dx-core.h"
#include "dx-video-yuv.h"

const dx_video_yuv_spec_t YUV_SPEC[] = {
    [DX_YUV_TYPE_YUYV] = { 1, 1, 2, 1, 2, 1 },
    [DX_YUV_TYPE_UYVY] = { 1, 1, 2, 1, 2, 1 },
    [DX_YUV_TYPE_YV12] = { 1, 1, 2, 2, 2, 2 },
    [DX_YUV_TYPE_NV12] = { 1, 1, 2, 2, 2, 2 },
    [DX_YUV_TYPE_NV21] = { 1, 1, 2, 2, 2, 2 },
    [DX_YUV_TYPE_I420] = { 1, 1, 2, 2, 2, 2 }
};

dx_video_yuv_t* dx_video_yuv_create(int type, int width, int height) {
	dx_video_yuv_t* yuv = MALLOC(sizeof(dx_video_yuv_t));
	dx_video_yuv_spec_t spec = YUV_SPEC[type];
	
	yuv->type = type;
	yuv->width = width;
	yuv->height = height;

	yuv->luma_size = ((int)(width + 7) / 8) * height;
	int sample_period_y = spec.sample_period_y_h * spec.sample_period_y_v;
	int sample_period_u = spec.sample_period_u_h * spec.sample_period_u_v;
	int sample_period_v = spec.sample_period_v_h * spec.sample_period_v_v;
	yuv->chroma_size = yuv->luma_size / sample_period_u / sample_period_y
		+ yuv->luma_size / sample_period_v / sample_period_y;

	switch(type) {
	case DX_YUV_TYPE_YUYV:
		yuv->stride_y = 2;
		yuv->stride_u = 4;
		yuv->stride_v = 4;
		break;

	case DX_YUV_TYPE_UYVY:
		yuv->stride_y = 2;
		yuv->stride_u = 4;
		yuv->stride_v = 4;
		break;

	case DX_YUV_TYPE_YV12:
		yuv->stride_y = 1;
		yuv->stride_u = 2;
		yuv->stride_v = 2;
		break;

	case DX_YUV_TYPE_NV12:
		yuv->stride_y = 1;
		yuv->stride_u = 1;
		yuv->stride_v = 1;
		break;

	default:
		break;
	}

	return yuv;
}

int dx_video_yuv_destroy(dx_video_yuv_t* yuv) {
	FREE(yuv);
	return 0;
}
