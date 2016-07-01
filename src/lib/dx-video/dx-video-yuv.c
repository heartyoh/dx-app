#include "dx-core.h"
#include "dx-video-yuv.h"

#include <sys/mman.h>

char* YUV_FOURCC[] = {
    [DX_YUV_TYPE_YUYV] = "YUYV",
    [DX_YUV_TYPE_UYVY] = "UYVY",
    [DX_YUV_TYPE_YV12] = "YV12",
    [DX_YUV_TYPE_NV12] = "NV12",
    [DX_YUV_TYPE_NV21] = "NV21",
    [DX_YUV_TYPE_I420] = "I420",
	NULL
};

dx_video_yuv_spec_t YUV_SPEC[] = {
    [DX_YUV_TYPE_YUYV] = { DX_YUV_FORMAT_PACKED, DX_YUV_ORDER_UV,
		1, 1, 2, 1, 2, 1, 2, 4, 4 },
    [DX_YUV_TYPE_UYVY] = { DX_YUV_FORMAT_PACKED, DX_YUV_ORDER_UV,
		1, 1, 2, 1, 2, 1, 2, 4, 4 },
    [DX_YUV_TYPE_YV12] = { DX_YUV_FORMAT_PLANAR_NON_INTERLEAVED, DX_YUV_ORDER_VU,
		1, 1, 2, 2, 2, 2, 1, 1, 1 },
    [DX_YUV_TYPE_NV12] = { DX_YUV_FORMAT_PLANAR_INTERLEAVED, DX_YUV_ORDER_UV,
		1, 1, 2, 2, 2, 2, 1, 2, 2 },
    [DX_YUV_TYPE_NV21] = { DX_YUV_FORMAT_PLANAR_INTERLEAVED, DX_YUV_ORDER_VU,
		1, 1, 2, 2, 2, 2, 1, 2, 2 },
    [DX_YUV_TYPE_I420] = { DX_YUV_FORMAT_PLANAR_NON_INTERLEAVED, DX_YUV_ORDER_UV,
		1, 1, 2, 2, 2, 2, 1, 1, 1 }
};

int dx_video_yuv_get_type(char* fourcc) {
	int idx = 0;
	while(NULL != YUV_FOURCC[idx]) {
		if(!strncmp(fourcc, YUV_FOURCC[idx], 4))
			return idx;
		idx++;
	}
	return -1;
}

dx_video_yuv_t* dx_video_yuv_create(int type, int width, int height) {
	dx_video_yuv_t* yuv = MALLOC(sizeof(dx_video_yuv_t));
	
	yuv->type = type;
	yuv->spec = &YUV_SPEC[type];
	yuv->width = width;
	yuv->height = height;

	dx_video_yuv_spec_t* spec = yuv->spec;

	/* 모든 YUV 포맷의 Cr, Cb의 샘플링 주기는 같기 때문에, chroma size는 Cr, Cb 가 같다고 전제한다. */
	if(spec->format == DX_YUV_FORMAT_PACKED) {
		/* TODO packed formate 에서 자투리 픽셀과 관련한 바운드 처리 방법을 확인 필요 */
		yuv->luma_size = ((int)(width / spec->sample_period_y_h)) * (height / spec->sample_period_y_v);
		yuv->chroma_size = ((int)(width / spec->sample_period_u_h)) * (height / spec->sample_period_u_v);
	} else {
		yuv->luma_size = ((int)(width / spec->sample_period_y_h)) * (height / spec->sample_period_y_v);
		yuv->chroma_size = ((int)(width / spec->sample_period_u_h)) * (height / spec->sample_period_u_v);
	}

	return yuv;
}

int dx_video_yuv_alloc_buffer(dx_video_yuv_t* yuv, int size, int fd, int offset) {

	if(yuv->buffer != NULL && yuv->buffer_allocated_by_self)
		FREE(yuv->buffer);

	if(fd != -1) {
		yuv->buffer_size = size;
		yuv->buffer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
		yuv->buffer_allocated_by_self = 0;
	} else {
		yuv->buffer_size = yuv->luma_size + yuv->chroma_size * 2;
		yuv->buffer = MALLOC(yuv->buffer_size);
		yuv->buffer_allocated_by_self = 1;
	}

	switch(yuv->type) {
	case DX_YUV_TYPE_YUYV:
		yuv->plane[0] = yuv->buffer;
		yuv->plane[1] = yuv->buffer + 1;
		yuv->plane[2] = yuv->buffer + 3;
		break;

	case DX_YUV_TYPE_UYVY:
		yuv->plane[0] = yuv->buffer + 1;
		yuv->plane[1] = yuv->buffer;
		yuv->plane[2] = yuv->buffer + 3;
		break;

	case DX_YUV_TYPE_YV12:
		yuv->plane[0] = yuv->buffer;
		yuv->plane[1] = yuv->buffer + yuv->luma_size + yuv->chroma_size;
		yuv->plane[2] = yuv->buffer + yuv->luma_size;
		break;

	case DX_YUV_TYPE_NV12:
		yuv->plane[0] = yuv->buffer;
		yuv->plane[1] = yuv->buffer + yuv->luma_size;
		yuv->plane[2] = yuv->buffer + yuv->luma_size + 1;
		break;

	case DX_YUV_TYPE_NV21:
		yuv->plane[0] = yuv->buffer;
		yuv->plane[1] = yuv->buffer + yuv->luma_size + 1;
		yuv->plane[2] = yuv->buffer + yuv->luma_size;
		break;

	case DX_YUV_TYPE_I420:
		yuv->plane[0] = yuv->buffer;
		yuv->plane[1] = yuv->buffer + yuv->luma_size;
		yuv->plane[2] = yuv->buffer + yuv->luma_size + yuv->chroma_size;
		break;
	}

	return 0;
}

int dx_video_yuv_fill_plane(dx_video_yuv_t* yuv, int plane_idx, uint8_t value) {
	uint8_t* p = yuv->plane[plane_idx];
	int size = (plane_idx == 0) ? yuv->luma_size : yuv->chroma_size;
	int stride = (plane_idx == 0) ? yuv->spec->stride_y 
		: (plane_idx == 1 ? yuv->spec->stride_u : yuv->spec->stride_v); 

	for(int i = 0;i < size;i++) {
		*p = value;
		p += stride;
	}

	return 0;
}

int dx_video_yuv_destroy(dx_video_yuv_t* yuv) {
	if(yuv->buffer_allocated_by_self)
		FREE(yuv->buffer);
	else
		munmap(yuv->buffer, yuv->buffer_size);	

	FREE(yuv);

	return 0;
}
