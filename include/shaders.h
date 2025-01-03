#ifndef SHADERS_H
#define SHADERS_H

unsigned int shaders_load_program(const char *vertex_path, const char *fragment_path);
unsigned int shaders_load_compute_program(const char *compute_path);
unsigned int shaders_get_compute_program();
void shaders_cleanup();

#endif
