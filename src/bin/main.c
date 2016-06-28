#include "stdio.h"

#include "dx-core.h"
#include "dx-video.h"

extern dx_video_yuv_spec_t YUV_SPEC[];

int main() {
	/* open v4l2 device */
//	dx_video_v4l2_open();
//	dx_video_v4l2_query();
//	dx_video_v4l2_close();



	dx_video_yuv_t* yuyv;
	dx_video_yuv_t* nv12;

	yuyv = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 1024, 768);
	nv12 = dx_video_yuv_create(DX_YUV_TYPE_NV12, 1024, 768);

	CONSOLE("YUYV : Luma SIze(%d), Chroma Size(%d)\n", yuyv->luma_size, yuyv->chroma_size);
	CONSOLE("NV12 : Luma SIze(%d), Chroma Size(%d)\n", nv12->luma_size, nv12->chroma_size);

	dx_video_yuv_alloc_buffer(yuyv, NULL, 0);
	dx_video_yuv_alloc_buffer(nv12, NULL, 0);

	CONSOLE("YUYV : planes : (%x, %x, %x), Buffer(%x)\n", yuyv->plane[0], yuyv->plane[1], yuyv->plane[2], yuyv->buffer);
	CONSOLE("NV12 : planes : (%x, %x, %x), Buffer(%x)\n", nv12->plane[0], nv12->plane[1], nv12->plane[2], nv12->buffer);

	dx_video_yuv_fill_plane(yuyv, 0, 1);
	dx_video_yuv_fill_plane(yuyv, 1, 2);
	dx_video_yuv_fill_plane(yuyv, 2, 3);
	
	for(int i = 0;i < 100;i++)
		dx_video_yuv_convert(yuyv, nv12);

	for(int i = 0;i < 100;i++) 
		CONSOLE("YUYV : %d\n", yuyv->buffer[i]);

	CONSOLE("NV12 : %d, %d\n", nv12->buffer[0], nv12->buffer[nv12->buffer_size - 1]);

	dx_video_yuv_destroy(yuyv);
	dx_video_yuv_destroy(nv12);
}
