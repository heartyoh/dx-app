
#ifndef __DX_GLES_MERGE_VSH_H
#define __DX_GLES_MERGE_VSH_H

#include "dx-gles.h"

static const char* dx_convert_vsh_src = STR(
// Attributes
attribute vec4 a_position;
attribute vec2 a_texture_coord_1;
attribute vec2 a_texture_coord_2;
attribute vec2 a_texture_coord_3;
attribute vec2 a_texture_coord_4;
attribute vec2 a_mask_coord;

// Varyings
varying vec2 v_texture_coord_1;
varying vec2 v_texture_coord_2;
varying vec2 v_texture_coord_3;
varying vec2 v_texture_coord_4;
varying vec2 v_mask_coord;

void main(void) {
	gl_Position = a_position;
	v_texture_coord_1 = a_texture_coord_1;
	v_texture_coord_2 = a_texture_coord_2;
	v_texture_coord_3 = a_texture_coord_3;
	v_texture_coord_4 = a_texture_coord_4;
}

);

#endif /* __DX_GLES_MERGE_VSH_H */
