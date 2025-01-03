#ifndef PARTICLES_H
#define PARTICLES_H

typedef struct
{
    float position[3];
    float velocity[3];
    float color[3];
    float life;
    float traits[4];
} Particle;

void particles_init(unsigned int max_particles);
void particles_update(float dt);
void particles_render();
void particles_cleanup();
unsigned int particles_get_count();

#endif
