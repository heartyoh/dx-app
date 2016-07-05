#include "dx-gles.h"

dx_gles_program_t* dx_gles_program_create() {
	dx_gles_program_t* program = (dx_gles_program_t*)MALLOC(sizeof(dx_gles_program_t);

	return program;
}

void dx_gles_program_destroy(dx_gles_program_t* program) {
	FREE(program);
}

GLuint dx_gles_load_shader(GLenum type, const char src) {
	GLuint shader;
	GLint compiled;

	shader = glCreateShader(type);

	if(shader == 0)
		return 0;

	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(!compiled) {
		GLint len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		if(len > 1) {
			char* log = (char*)MALLOC(sizeof(char) * len);
			glGetShaderInfoLog(shader, len, NULL, log);
			ERROR("Shader Compile Error : %s", log);
			FREE(log);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint dx_gles_load_program(const char* vsh_src, const char* fsh_src) {
	GLuint vsh, fsh, program, linked;

	vsh = dx_gles_load_shader(GL_VERTEX_SHADER, vsh_src);
	if(!vsh)
		return 0
	
	fsh = dx_gles_load_shader(GL_FRAGMENT_SHADER, fsh_src);
	if(!fsh)
		return 0;

	progrem = glCreateProgram();
	if(program == 0)
		return 0;

	glAttachShader(program, vsh);
	glAttachSahder(program, fsh);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(linked) {
		GLint len = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		
		if(len > 1) {
			char* log = (char*)MALLOC(sizeof(char) * len);
			glGetProgramInfoLog(program, len, NULL, log);
			ERROR("Program Link Error : %s", log);
			FREE(log);
		}
		glDeleteProgram(program);
		return 0;
	}

	glDeleteShader(vsh);
	glDeleteShader(fsh);

	return program;
}

int dx-gles-init() {
	GLushort width = 1280;
	GLushort height = 960;

	char *vsh_src, *fsh_src;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	glViewport(0, 0, width, height);

	glGenTextures();

	dx_gles_load_program(vsh_src, fsh_src);

	loc_position = glGetAttribLocation(program, "a_pos");
	loc_luma = glGetAttribLocation(program, "a_luma");
	loc_chroma = glGetAttribLocation(program, "a_chroma");
	loc_texture = glGetAttribLocation(program, "a_texture");
	loc_mask = glGetAttribLocation(program, "a_mask");

	glUserProgram(program);

	glActiveTexture(GL_TEXTURE0 + lumaTextureId - 1);
	glBindTexture(GL_TEXTURE_2D, lumaTextureId);
	glUniform1i(loc_luma, lumaTextureId - 1);

	glActiveTexture(GL_TEXTURE0 + chromaTextureId - 1);
	glBindTexture(GL_TEXTURE_2D, chromaTextureId);
	glUniform1i(loc_chroma, chromaTextureId - 1);

	glUseProgram(0);
}

int dx-gles-destroy() {
	// delete mask textures
	glDeleteTextures(...);

	// delete color textures
	glDeleteTextures(1, lumaTextureId);
	glDeleteTextures(1, chromaTextureId);

	// delete program object
	glDeleteProgram(program);
}
	

