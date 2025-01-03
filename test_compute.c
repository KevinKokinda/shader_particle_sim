#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Error: Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Compute Shader Test", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Error: Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    if (glewIsSupported("GL_ARB_compute_shader"))
    {
        printf("Compute shaders are supported!\n");
    }
    else
    {
        printf("Compute shaders are NOT supported.\n");
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
