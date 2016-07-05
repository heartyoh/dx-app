
#include "dx_gles.h"

int main() {


	dx_gles_program_t* program = dx_gles_program_create();	

	program->screen_width = 1280;
	program->screen_height = 960;

	dx_gles_init();

	while(1) {
	}

	dx_gles_program_destroy(program);
	dx_gles_destroy();
}
