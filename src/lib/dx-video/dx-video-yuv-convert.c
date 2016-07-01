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

	uint8_t Y = 0, U = 0, V = 0;

	for(i = 0;i < src->height;i++) {
		for(j = 0;j < src->width;j++) {
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

int dx_video_yuv_merge(dx_video_yuv_t** srcs, dx_video_yuv_t* dst, int rows, int cols) {
	int i, j, r, c;

	uint8_t** SYS = MALLOC(sizeof(uint8_t*) * rows * cols);
	uint8_t** SUS = MALLOC(sizeof(uint8_t*) * rows * cols);
	uint8_t** SVS = MALLOC(sizeof(uint8_t*) * rows * cols);

	for(i = 0;i < rows;i++) {
		for(j = 0;j < cols;j++) {
			int x = i * rows + j;
			SYS[x] = (*(srcs + x))->plane[0];
			SUS[x] = (*(srcs + x))->plane[1];
			SVS[x] = (*(srcs + x))->plane[2];
		}
	}

	uint8_t *DY = dst->plane[0];
	uint8_t *DU = dst->plane[1];
	uint8_t *DV = dst->plane[2];
	
	int di, dj;
	uint8_t Y = 0, U = 0, V = 0;
	uint8_t *SY, *SU, *SV;

	int height = srcs[0]->height;
	int width = srcs[0]->width;

	dx_video_yuv_t* src = NULL;

	ERROR("Start Merge.\n");

	for(r = 0;r < rows;r++) {
		for(i = 0;i < height;i++) {
			for(c = 0;c < cols;c++) {
				for(j = 0;j < width;j++) {

					// i : source row, j : source column
					// di : dest row, dj : dest column
					di = (r * height) + i;
					dj = (c * width) + j;

					SY = SYS[r * rows + c];
					SU = SUS[r * rows + c];
					SV = SVS[r * rows + c];

					src = *(srcs + (r * rows + c));

					if(!(i % src->spec->sample_period_y_v) && !(j % src->spec->sample_period_y_h)) {
						Y = *SY;
						SY += src->spec->stride_y;
					}
					if(!(di % dst->spec->sample_period_y_v) && !(dj % dst->spec->sample_period_y_h)) {
						*DY = Y;
						DY += dst->spec->stride_y;
					}
		
					if(!(i % src->spec->sample_period_u_v) && !(j % src->spec->sample_period_u_h)) {
						U = *SU;
						SU += src->spec->stride_u;
					}
					if(!(di % dst->spec->sample_period_u_v) && !(dj % dst->spec->sample_period_u_h)) {
						*DU = U;
						DU += dst->spec->stride_u;
					}
		
					if(!(i % src->spec->sample_period_v_v) && !(j % src->spec->sample_period_v_h)) {
						V = *SV;
						SV += src->spec->stride_v;
					}
					if(!(di % dst->spec->sample_period_v_v) && !(dj % dst->spec->sample_period_v_h)) {
						*DV = V;
						DV += dst->spec->stride_v;
					}
				}
			}
		}
	}

	FREE(SYS);
	FREE(SUS);
	FREE(SVS);

	return 0;
}
