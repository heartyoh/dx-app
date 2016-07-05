#ifndef __DX_GLES_CONVERT_FSH_H
#define __DX_GLES_CONVERT_FSH_H

#include "dx-gles.h"

static const char* dx_convert_fsh_src = STR(

precision mediump float;

// Varyings
varying vec2 v_texture_coord;

// Uniforms
uniform sampler2D s_luma_map;
uniform sampler2D s_chroma_map;

void main(void) {
	vec4 front_color;
	vec4 to_color;

	gl_FragColor = to_color;
}

);

#endif /* __DX_GLES_CONVERT_FSH_H */
