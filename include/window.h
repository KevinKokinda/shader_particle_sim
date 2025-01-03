#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

int window_init(const char *title, int width, int height);
int window_should_close();
void window_poll_events();
void window_swap_buffers();
void window_terminate();
int window_get_width();
int window_get_height();
GLFWwindow *window_get_handle();

#endif
