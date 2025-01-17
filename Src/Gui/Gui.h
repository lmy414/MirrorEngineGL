#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"

class ImGuiManager {
public:
    ImGuiManager();
    ~ImGuiManager();

    void Initialize(GLFWwindow* window);
    void BeginFrame();
    void EndFrame();
    void Shutdown();

private:
    bool initialized = false;       
};

#endif // IMGUIMANAGER_H
