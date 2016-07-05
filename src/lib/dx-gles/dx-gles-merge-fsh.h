#ifndef __DX_GLES_MERGE_FSH_H
#define __DX_GLES_MERGE_FSH_H

#include "dx-gles.h"

static const char* dx_merge_fsh_src = STR(

struct pixel_in {
	vec2 texcoord1: TEXCOORD0;
	vec2 texcoord2: TEXCOORD1;
	vec2 texcoord3: TEXCOORD2;
	vec2 texcoord4: TEXCOORD3;

	uniform samplerRECT texture1: TEXUNIT0;
	uniform samplerRECT texture2: TEXUNIT1;
	uniform samplerRECT texture3: TEXUNIT2;
	uniform samplerRECT texture4: TEXUNIT3;
	
	float	y : COLOR0;
	float	u : COLOR1;
	float	v : COLOR2;
}

struct pixel_out {
	float	y : COLOR0;
	float	u : COLOR1;
	float	v : COLOR2;
}

void main(pixel_in in) {
	pixel_out out;

	float x = texcoord1.x;
	float y = texcoord1.y;

	float4 color;

	if(x < 640) {
		if(y < 480)
			color = COLOR(texture1, texcoord1);
		else
			color = COLOR(texture2, texcoord2);	
	} else {
		if(y < 480)
			color = COLOR(texture3, texcoord3);
		else
			color = COLOR(texture4, texcoord4);	
	}

	out.y = color.r;
	out.u = color.g;
	out.v = color.a;

	return out;
}

);

