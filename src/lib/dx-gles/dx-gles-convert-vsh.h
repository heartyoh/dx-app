#ifndef __DX_GLES_CONVERT_VSH_H
#define __DX_GLES_CONVERT_VSH_H

#include "dx-gles.h"

static const char* dx_convert_vsh_src = STR(
// Attributes
attribute vec4 a_position;
attribute vec2 a_texture_coord;

// Varyings
varying vec2 v_texture_coord;

void main(void) {
	gl_Position = a_position;
	v_texture_coord = a_texture_coord;
}

);

#endif /* __DX_GLES_CONVERT_VSH_H */
