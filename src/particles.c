#include <GL/glew.h>
#include <stdlib.h>
#include <time.h>
#include "particles.h"
#include "shaders.h"
#include "evolution.h"

static Particle *particles = NULL;
static unsigned int particle_count = 0;
static GLuint particle_ssbo = 0;
static GLuint vao = 0;
static GLuint vbo = 0;

void particles_init(unsigned int max_particles)
{
    particle_count = max_particles;
    particles = (Particle *)malloc(sizeof(Particle) * particle_count);
    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < particle_count; i++)
    {
        particles[i].position[0] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
        particles[i].position[1] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
        particles[i].position[2] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
        particles[i].velocity[0] = 0.0f;
        particles[i].velocity[1] = 0.0f;
        particles[i].velocity[2] = 0.0f;
        particles[i].color[0] = ((float)rand() / (float)RAND_MAX);
        particles[i].color[1] = ((float)rand() / (float)RAND_MAX);
        particles[i].color[2] = ((float)rand() / (float)RAND_MAX);
        particles[i].life = 1.0f;
        for (int j = 0; j < 4; j++)
        {
            particles[i].traits[j] = ((float)rand() / (float)RAND_MAX);
        }
    }
    glGenBuffers(1, &particle_ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, particle_count * sizeof(Particle), particles, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float), NULL, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindVertexArray(0);
}

void particles_update(float dt)
{
    glUseProgram(shaders_get_compute_program());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_ssbo);
    glUniform1f(glGetUniformLocation(shaders_get_compute_program(), "uDeltaTime"), dt);
    glDispatchCompute((particle_count + 127) / 128, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glBindBuffer(GL_COPY_READ_BUFFER, particle_ssbo);
    glGetBufferSubData(GL_COPY_READ_BUFFER, 0, particle_count * sizeof(Particle), particles);
    evolution_update(particles, particle_count, dt);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, particle_count * sizeof(Particle), particles);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void particles_render()
{
    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_POINTS, 0, 1, particle_count);
    glBindVertexArray(0);
}

void particles_cleanup()
{
    if (particles)
    {
        free(particles);
        particles = NULL;
    }
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &particle_ssbo);
    glDeleteVertexArrays(1, &vao);
}

unsigned int particles_get_count()
{
    return particle_count;
}
