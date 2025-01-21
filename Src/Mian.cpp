#include "Common.h"


// 全局相机对象
Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// 控制模型变换的对象
TransformControls transformControls;

// 主渲染循环
int main() {
    // 初始化 OpenGL 和窗口
    GLFWwindow* window = InitializeOpenGL(800, 600, "Basic Mesh Rendering");
    if (!window) return -1;

    // 创建并初始化 ImGui 管理器
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);  // 初始化 ImGui

    // 创建 Shader 对象并加载着色器
    Shader shader("E:/MirrorEngine/MirrorEngine2/Shaders/Model.vs", "E:/MirrorEngine/MirrorEngine2/Shaders/Model.fs");

    // 使用 ModelPool 来加载模型
    std::shared_ptr<Model> model = ModelPool::Instance().LoadModel("cube", "Assets/m/cs2.fbx");  // 通过名称加载模型
    Mesh mesh;

    // 主渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 获取帧时间
        float deltaTime = 0.016f;  // 假设固定帧时间

        // 清空屏幕
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 开始 ImGui 新一帧
        imguiManager.BeginFrame();

        // 绘制 GUI 控件
        ImGui::Begin("Transform Controls");
        transformControls.DrawGUI();  // 处理旋转、缩放、位置控件
        ImGui::End();

        // 获取变换矩阵
        glm::mat4 modelMatrix = transformControls.GetTransformMatrix();

        // 获取矩阵
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // 使用着色器
        shader.use();
        shader.setMat4("model", modelMatrix);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // 渲染模型
        mesh.Render(shader, modelMatrix, view, projection);

        // 渲染 ImGui 界面
        imguiManager.EndFrame();  // 结束 ImGui 渲染

        // 交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 关闭 ImGui
    imguiManager.Shutdown();

    glfwTerminate();
    return 0;
}
