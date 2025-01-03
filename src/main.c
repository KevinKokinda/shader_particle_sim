#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "particles.h"
#include "shaders.h"
#include "gui.h"

int main()
{
    fprintf(stderr, "Starting Particle Shader System\n");

    if (!window_init("Particle Shader System", 1280, 720))
    {
        fprintf(stderr, "Error: Failed to initialize window\n");
        return -1;
    }
    fprintf(stderr, "Window initialized successfully\n");

    unsigned int renderProgram = shaders_load_program("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    if (!renderProgram)
    {
        fprintf(stderr, "Error: Failed to load render program\n");
        window_terminate();
        return -1;
    }
    fprintf(stderr, "Render program loaded successfully\n");

    if (!shaders_load_compute_program("shaders/compute_shader.glsl"))
    {
        fprintf(stderr, "Error: Failed to load compute shader program\n");
        window_terminate();
        return -1;
    }
    fprintf(stderr, "Compute shader program loaded successfully\n");

    particles_init(1000);
    fprintf(stderr, "Particles initialized\n");

    gui_init(window_get_handle());
    fprintf(stderr, "GUI initialized\n");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    static double lastTime = 0.0;

    fprintf(stderr, "Entering main loop\n");
    while (!window_should_close())
    {
        window_poll_events();
        gui_new_frame();
        double currentTime = glfwGetTime();
        float dt = (float)(currentTime - lastTime);
        lastTime = currentTime;

        particles_update(dt);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(renderProgram);
        particles_render();
        glUseProgram(0);
        gui_render();
        window_swap_buffers();
    }

    fprintf(stderr, "Exiting main loop\n");
    gui_shutdown();
    particles_cleanup();
    shaders_cleanup();
    window_terminate();

    fprintf(stderr, "Program terminated successfully\n");
    return 0;
}
