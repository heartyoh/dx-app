#include "dx-core.h"
#include "dx-video-yuv.h"
#include "dx-video-yuv-convert.h"

int dx_video_yuv_convert(dx_video_yuv_t* src, dx_video_yuv_t* dst) {

	uint8_t *SY = src->plane[0];
	uint8_t *SU = src->plane[1];
	uint8_t *SV = src->plane[2];

	uint8_t *DY = dst->plane[0];
	uint8_t *DU = dst->plane[1];
	uint8_t *DV = dst->plane[2];
	
	int i, j;

	uint8_t Y, U, V;

	for(i = 0;i < src->height;i++) {
		for(j = 0;j < (src->width + 7) / 8;j++) {
			if(!(i % src->spec->sample_period_y_v) && !(j % src->spec->sample_period_y_h)) {
				Y = *SY;
				SY += src->spec->stride_y;
			}
			if(!(i % dst->spec->sample_period_y_v) && !(j % dst->spec->sample_period_y_h)) {
				*DY = Y;
				DY += dst->spec->stride_y;
			}

			if(!(i % src->spec->sample_period_u_v) && !(j % src->spec->sample_period_u_h)) {
				U = *SU;
				SU += src->spec->stride_u;
			}
			if(!(i % dst->spec->sample_period_u_v) && !(j % dst->spec->sample_period_u_h)) {
				*DU = U;
				DU += dst->spec->stride_u;
			}

			if(!(i % src->spec->sample_period_v_v) && !(j % src->spec->sample_period_v_h)) {
				V = *SV;
				SV += src->spec->stride_v;
			}
			if(!(i % dst->spec->sample_period_v_v) && !(j % dst->spec->sample_period_v_h)) {
				*DV = V;
				DV += dst->spec->stride_v;
			}
		}
	}

	return 0;
}

