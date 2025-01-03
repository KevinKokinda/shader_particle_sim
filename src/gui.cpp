#include "gui.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

void gui_init(void *window_ptr)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)window_ptr, true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void gui_new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void gui_render()
{
    ImGui::Begin("Particle System Controls");
    ImGui::Text("Adjust simulation parameters here.");
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void gui_shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
