#ifndef _DX_VIDEO_SAMPLER
#define _DX_VIDEO_SAMPLER

typedef struct dx_video_sampler {
	void* buffer;
	uint16_t width;
	uint16_t height;
	void (*sampler)();	
} dx_video_sampler_t;


dx_video_sampler_t* dx_video_sampler_init();
int dx_video_sampler_start(dx_video_sampler_t* sampelr);
int dx_video_sampler_stop(dx_video_sampler_t* sampelr);
int dx_video_sampler_destroy(dx_video_sampler_t* sampelr);



#endif // _DX_VIDEO_SAMPLER
