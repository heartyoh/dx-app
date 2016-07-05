#ifndef __DX_GLES_H
#define __DX_GLES_H

#define STR(A) #A

typedef struct dx_gles_program {
	int screen_width;
	int screen_height;
	int video_width;
	int video_height;
	GLfloat* vertices;
	GLushort* indices;

	GLuint program;

	GLint loc_position;
	GLint loc_texture[4];
	GLint loc_mask;

	GLint loc_luma_map;
	GLint loc_chroma_map;
	GLint loc_mask_map;

	GLint texture_luma;
	GLint texture_chroma;
	
} dx_gles_program;

#endif /* __DX_GLES_H */
