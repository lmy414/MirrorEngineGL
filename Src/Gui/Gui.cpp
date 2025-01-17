#include "Gui.h"

ImGuiManager::ImGuiManager() : initialized(false) {}

ImGuiManager::~ImGuiManager() {
    if (initialized) {
        Shutdown();
    }
}

void ImGuiManager::Initialize(GLFWwindow* window) {
    if (initialized) {
        return; // �����ظ���ʼ��
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ��ʼ��ƽ̨����Ⱦ����
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("c:/windows/Fonts/simhei.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());//������������
    initialized = true;
}

void ImGuiManager::BeginFrame() {
    if (!initialized) return;

    // ��ʼ��֡
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::EndFrame() {
    if (!initialized) return;

    // ��Ⱦ������֡
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Shutdown() {
    if (!initialized) return;

    // ����ƽ̨����Ⱦ����
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    // ���� ImGui ������
    ImGui::DestroyContext();
    initialized = false;
}
