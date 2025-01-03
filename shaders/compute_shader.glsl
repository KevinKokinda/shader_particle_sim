#version 410 core

layout(local_size_x = 128) in;

void main()
{
    uint gid = gl_GlobalInvocationID.x;
    // TODO: add real logic
}
