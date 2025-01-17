#include "Gui.h"

ImGuiManager::ImGuiManager() : initialized(false) {}

ImGuiManager::~ImGuiManager() {
    if (initialized) {
        Shutdown();
    }
}

void ImGuiManager::Initialize(GLFWwindow* window) {
    if (initialized) {
        return; // 避免重复初始化
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // 初始化平台和渲染器绑定
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("c:/windows/Fonts/simhei.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());//加载中文字体
    initialized = true;
}

void ImGuiManager::BeginFrame() {
    if (!initialized) return;

    // 开始新帧
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::EndFrame() {
    if (!initialized) return;

    // 渲染并结束帧
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Shutdown() {
    if (!initialized) return;

    // 清理平台和渲染器绑定
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    // 销毁 ImGui 上下文
    ImGui::DestroyContext();
    initialized = false;
}
