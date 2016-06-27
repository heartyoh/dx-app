#include "stdio.h"

#include "dx-video.h"

extern dx_video_yuv_spec_t YUV_SPEC[];

int main() {
	dx_video_yuv_t* yuyv;
	dx_video_yuv_t* nv12;

	yuyv = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 1024, 768);
	nv12 = dx_video_yuv_create(DX_YUV_TYPE_NV12, 1024, 768);


	CONSOLE("YUYV : Luma SIze(%d), Chroma Size(%d)\n", yuyv->luma_size, yuyv->chroma_size);
	CONSOLE("NV12 : Luma SIze(%d), Chroma Size(%d)\n", nv12->luma_size, nv12->chroma_size);

	dx_video_yuv_convert_yuyv_nv12(yuyv, nv12);

	dx_video_yuv_destroy(yuyv);
	dx_video_yuv_destroy(nv12);
}
