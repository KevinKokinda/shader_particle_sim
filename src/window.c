#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"

static GLFWwindow *window = NULL;
static int width = 800;
static int height = 600;

void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

int window_init(const char *title, int w, int h)
{
    fprintf(stderr, "Initializing GLFW\n");
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "Error: GLFW initialization failed\n");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    fprintf(stderr, "Creating GLFW window\n");
    window = glfwCreateWindow(w, h, title, NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Error: Failed to create GLFW window\n");
        glfwTerminate();
        return 0;
    }

    width = w;
    height = h;
    glfwMakeContextCurrent(window);

    fprintf(stderr, "Initializing GLEW\n");
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Error: GLEW initialization failed: %s\n", glewGetErrorString(err));
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }

    glfwSwapInterval(1);
    fprintf(stderr, "GLFW and GLEW initialized successfully\n");
    return 1;
}

int window_should_close()
{
    return glfwWindowShouldClose(window);
}

void window_poll_events()
{
    glfwPollEvents();
}

void window_swap_buffers()
{
    glfwSwapBuffers(window);
}

void window_terminate()
{
    fprintf(stderr, "Terminating window and GLFW\n");
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

int window_get_width()
{
    return width;
}

int window_get_height()
{
    return height;
}

GLFWwindow *window_get_handle()
{
    return window;
}
