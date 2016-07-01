#include "stdio.h"

#include "dx-core.h"
#include "dx-video.h"

extern dx_video_yuv_spec_t YUV_SPEC[];

int convert() {
	dx_video_yuv_t* yuyv;
	dx_video_yuv_t* i420;

	yuyv = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 1024, 768);
	i420 = dx_video_yuv_create(DX_YUV_TYPE_I420, 1024, 768);

	CONSOLE("YUYV : Luma SIze(%d), Chroma Size(%d)\n", yuyv->luma_size, yuyv->chroma_size);
	CONSOLE("I420 : Luma SIze(%d), Chroma Size(%d)\n", i420->luma_size, i420->chroma_size);

	dx_video_yuv_alloc_buffer(yuyv, 0, -1, 0);
	dx_video_yuv_alloc_buffer(i420, 0, -1, 0);

	CONSOLE("YUYV : planes : (%x, %x, %x), Buffer(%x)\n", yuyv->plane[0], yuyv->plane[1], yuyv->plane[2], yuyv->buffer);
	CONSOLE("I420 : planes : (%x, %x, %x), Buffer(%x)\n", i420->plane[0], i420->plane[1], i420->plane[2], i420->buffer);

	dx_video_yuv_fill_plane(yuyv, 0, 1);
	dx_video_yuv_fill_plane(yuyv, 1, 2);
	dx_video_yuv_fill_plane(yuyv, 2, 3);
	
	for(int i = 0;i < 100;i++)
		dx_video_yuv_convert(yuyv, i420);

	for(int i = 0;i < 100;i++) 
		CONSOLE("YUYV : %d\n", yuyv->buffer[i]);

	CONSOLE("I420 : %d, %d\n", i420->buffer[0], i420->buffer[i420->buffer_size - 1]);

	dx_video_yuv_destroy(yuyv);
	dx_video_yuv_destroy(i420);

	return 0;
}

int merge() {
	dx_video_yuv_t* yuyv1;
	dx_video_yuv_t* yuyv2;
	dx_video_yuv_t* yuyv3;
	dx_video_yuv_t* yuyv4;
	dx_video_yuv_t* i420;

	yuyv1 = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 1024, 768);
	yuyv2 = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 1024, 768);
	yuyv3 = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 1024, 768);
	yuyv4 = dx_video_yuv_create(DX_YUV_TYPE_YUYV, 1024, 768);

	i420 = dx_video_yuv_create(DX_YUV_TYPE_I420, 2048, 1536);

	CONSOLE("YUYV : Luma SIze(%d), Chroma Size(%d)\n", yuyv1->luma_size, yuyv1->chroma_size);
	CONSOLE("I420 : Luma SIze(%d), Chroma Size(%d)\n", i420->luma_size, i420->chroma_size);

	dx_video_yuv_alloc_buffer(yuyv1, 0, -1, 0);
	dx_video_yuv_alloc_buffer(yuyv2, 0, -1, 0);
	dx_video_yuv_alloc_buffer(yuyv3, 0, -1, 0);
	dx_video_yuv_alloc_buffer(yuyv4, 0, -1, 0);
	dx_video_yuv_alloc_buffer(i420, 0, -1, 0);

	CONSOLE("YUYV : planes : (%x, %x, %x), Buffer(%x)\n", yuyv1->plane[0], yuyv1->plane[1], yuyv1->plane[2], yuyv1->buffer);
	CONSOLE("I420 : planes : (%x, %x, %x), Buffer(%x)\n", i420->plane[0], i420->plane[1], i420->plane[2], i420->buffer);

	dx_video_yuv_fill_plane(yuyv1, 0, 1);
	dx_video_yuv_fill_plane(yuyv1, 1, 2);
	dx_video_yuv_fill_plane(yuyv1, 2, 3);

	dx_video_yuv_fill_plane(yuyv2, 0, 1);
	dx_video_yuv_fill_plane(yuyv2, 1, 2);
	dx_video_yuv_fill_plane(yuyv2, 2, 3);
	
	dx_video_yuv_fill_plane(yuyv3, 0, 1);
	dx_video_yuv_fill_plane(yuyv3, 1, 2);
	dx_video_yuv_fill_plane(yuyv3, 2, 3);
	
	dx_video_yuv_fill_plane(yuyv4, 0, 1);
	dx_video_yuv_fill_plane(yuyv4, 1, 2);
	dx_video_yuv_fill_plane(yuyv4, 2, 3);
	
	dx_video_yuv_t* yuyvs[] = { yuyv1, yuyv2, yuyv3, yuyv4 };

	dx_video_yuv_merge(yuyvs, i420, 2, 2);

	for(int i = 0;i < 100;i++) 
		CONSOLE("YUYV : %d\n", yuyv1->buffer[i]);

	for(int i = 0;i < 100;i++) 
		CONSOLE("I420 : %d, %d\n", i420->buffer[i], i420->buffer[i420->buffer_size - i]);

	dx_video_yuv_destroy(yuyv1);
	dx_video_yuv_destroy(yuyv2);
	dx_video_yuv_destroy(yuyv3);
	dx_video_yuv_destroy(yuyv4);
	dx_video_yuv_destroy(i420);

	return 0;
}

int main() {
//	convert();
	merge();

	/* open v4l2 device */
//	dx_video_v4l2_open();
//	dx_video_v4l2_query();
//	dx_video_v4l2_close();
}

