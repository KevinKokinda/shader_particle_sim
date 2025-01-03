CC       = gcc
CXX      = g++
CFLAGS   = -Iinclude -Iimgui -Iimgui/backends -Wall -g -std=c++17
LIBS     = -lGLEW -lglfw -lGL -lstdc++

C_SRC    = src/main.c \
           src/window.c \
           src/particles.c \
           src/shaders.c \
           src/evolution.c

CPP_SRC  = src/gui.cpp \
           imgui/imgui.cpp \
           imgui/imgui_draw.cpp \
           imgui/imgui_tables.cpp \
           imgui/imgui_widgets.cpp \
           imgui/backends/imgui_impl_glfw.cpp \
           imgui/backends/imgui_impl_opengl3.cpp

C_OBJ    = $(C_SRC:.c=.o)
CPP_OBJ  = $(CPP_SRC:.cpp=.o)
OBJ      = $(C_OBJ) $(CPP_OBJ)

EXEC     = particle_shader_system

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
