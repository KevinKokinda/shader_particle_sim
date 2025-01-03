#include <GLFW/glfw3.h>
#include <stdio.h>

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    fprintf(stderr, "GLFW initialized successfully\n");

    GLFWwindow *window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    fprintf(stderr, "Window created successfully\n");

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    fprintf(stderr, "Program terminated successfully\n");
    return 0;
}
