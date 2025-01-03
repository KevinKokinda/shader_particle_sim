#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"

static unsigned int computeProgram = 0;

static char *read_file(const char *path)
{
    FILE *file = fopen(path, "rb");
    if (!file)
    {
        fprintf(stderr, "Error: Failed to open file: %s\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char *)malloc(length + 1);
    if (!buffer)
    {
        fprintf(stderr, "Error: Memory allocation failed for file buffer\n");
        fclose(file);
        return NULL;
    }
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

static unsigned int compile_shader(const char *source, GLenum type, const char *shader_path)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        fprintf(stderr, "Error: Shader compilation failed for %s\n%s\n", shader_path, infoLog);
        return 0;
    }
    fprintf(stderr, "Shader compiled successfully: %s\n", shader_path);
    return shader;
}

unsigned int shaders_load_program(const char *vertex_path, const char *fragment_path)
{
    fprintf(stderr, "Loading shaders: Vertex = %s, Fragment = %s\n", vertex_path, fragment_path);

    char *vertexSource = read_file(vertex_path);
    char *fragmentSource = read_file(fragment_path);
    if (!vertexSource || !fragmentSource)
    {
        fprintf(stderr, "Error: Failed to read shader files\n");
        free(vertexSource);
        free(fragmentSource);
        return 0;
    }

    unsigned int vertexShader = compile_shader(vertexSource, GL_VERTEX_SHADER, vertex_path);
    unsigned int fragmentShader = compile_shader(fragmentSource, GL_FRAGMENT_SHADER, fragment_path);
    free(vertexSource);
    free(fragmentSource);

    if (!vertexShader || !fragmentShader)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        fprintf(stderr, "Error: Shader program linking failed\n%s\n", infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    fprintf(stderr, "Shader program linked successfully\n");
    return program;
}

unsigned int shaders_load_compute_program(const char *compute_path)
{
    fprintf(stderr, "Loading compute shader: %s\n", compute_path);

    char *computeSource = read_file(compute_path);
    if (!computeSource)
    {
        fprintf(stderr, "Error: Failed to read compute shader file\n");
        return 0;
    }

    unsigned int shader = compile_shader(computeSource, GL_COMPUTE_SHADER, compute_path);
    free(computeSource);

    if (!shader)
    {
        glDeleteShader(shader);
        return 0;
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        fprintf(stderr, "Error: Compute shader program linking failed\n%s\n", infoLog);
        glDeleteShader(shader);
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(shader);
    computeProgram = program;

    fprintf(stderr, "Compute shader program linked successfully\n");
    return program;
}

unsigned int shaders_get_compute_program()
{
    return computeProgram;
}

void shaders_cleanup()
{
    if (computeProgram)
    {
        glDeleteProgram(computeProgram);
        computeProgram = 0;
    }
}
