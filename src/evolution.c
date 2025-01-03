#include <math.h>
#include "evolution.h"

void evolution_update(Particle *particles, unsigned int count, float dt)
{
    for (unsigned int i = 0; i < count; i++)
    {
        float speedFactor = particles[i].traits[0] * 0.5f;
        float lifeFactor = particles[i].traits[1] * 0.5f;
        particles[i].velocity[0] += speedFactor * dt;
        particles[i].velocity[1] += speedFactor * dt;
        particles[i].velocity[2] += speedFactor * dt;
        particles[i].life -= lifeFactor * dt;
        if (particles[i].life < 0.0f)
        {
            particles[i].life = 1.0f;
            particles[i].position[0] = 0.0f;
            particles[i].position[1] = 0.0f;
            particles[i].position[2] = 0.0f;
            particles[i].velocity[0] = 0.0f;
            particles[i].velocity[1] = 0.0f;
            particles[i].velocity[2] = 0.0f;
        }
    }
}
