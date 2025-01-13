#include "Common.h"

// 全局相机对象
Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // 初始化相机位置

float mouseSpeed = 0.1f; // 鼠标灵敏度
float moveSpeed = 0.1f;  // 键盘移动速度

InputManager* inputManager = nullptr;  // 输入管理器

// 全局缓冲对象变量
unsigned int VBO, VAO, EBO;

int main() {
    // 初始化 OpenGL 和窗口
    GLFWwindow* window = InitializeOpenGL(800, 600, "MirrorEngine");
    if (!window) return -1;

    // 创建输入管理器实例
    inputManager = new InputManager(camera, moveSpeed, mouseSpeed);

    // 注册输入回调函数
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        inputManager->MouseCallback(window, xpos, ypos);
        });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        inputManager->MouseButtonCallback(window, button, action, mods);
        });

    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    // 创建矩阵对象并设置矩阵
    MatrixManager matrixManager;
    matrixManager.SetModelMatrix(glm::mat4(1.0f)); // 单位矩阵
    matrixManager.SetViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // 摄像机
    matrixManager.SetPerspectiveProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // 透视投影

    // 创建 Shader 对象并加载着色器
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");

    // 加载模型
    ModelLoader modelLoader;
    if (!modelLoader.LoadModel("./Assets/obj/text.obj")) {
        std::cerr << "Failed to load model!" << std::endl;
        return -1;
    }

    // 初始化 ImGui
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);

    // 初始颜色值和旋转角度
    float triangleColor[3] = { 0.5f, 0.2f, 0.8f };
    float rotationAngles[3] = { 0.0f, 0.0f, 0.0f }; // X, Y, Z 轴的旋转角度

    // 主渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 获取帧时间
        float deltaTime = 0.016f;  // 假设固定帧时间（可以替换为实际的 deltaTime）

        // 处理输入
        inputManager->ProcessInput(window, deltaTime);

        // 获取矩阵
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = matrixManager.GetProjectionMatrix();

        // 创建模型矩阵，结合旋转角度
        glm::mat4 model = matrixManager.GetModelMatrix();

        // 仅对当前旋转角度应用旋转，而不累加
        model = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕 X 轴
        model = glm::rotate(model, glm::radians(rotationAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕 Y 轴
        model = glm::rotate(model, glm::radians(rotationAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕 Z 轴
        matrixManager.SetModelMatrix(model); // 更新模型矩阵

        // 使用着色器程序
        shader.use();

        // 清空屏幕
        glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 渲染每个网格
        for (const Mesh& mesh : modelLoader.meshes) {
            SetupVertexBuffers(VBO, VAO, EBO, mesh); // 初始化 VBO, VAO, EBO

            // 激活纹理单元
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);  // 这里需要加载纹理，如果有的话
            glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);  // 传递纹理给着色器

            // 传递颜色值到着色器
            shader.setVec3("triangleColor", triangleColor[0], triangleColor[1], triangleColor[2]);

            // 传递矩阵到着色器
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

            // 绘制网格
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        // 启动 ImGui 界面
        imguiManager.BeginFrame();

        if (ImGui::Button("Reset Camera")) {
            camera.ResetCamera();  // 重置相机到初始位置和朝向
        }

        ImGui::Begin("Cube Control");
        ImGui::Text("Adjust cube rotation:");
        ImGui::SliderFloat("Rotate X", &rotationAngles[0], 0.0f, 360.0f);
        ImGui::SliderFloat("Rotate Y", &rotationAngles[1], 0.0f, 360.0f);
        ImGui::SliderFloat("Rotate Z", &rotationAngles[2], 0.0f, 360.0f);
        ImGui::Text("Change color:");
        ImGui::SliderFloat("Red", &triangleColor[0], 0.0f, 1.0f);
        ImGui::SliderFloat("Green", &triangleColor[1], 0.0f, 1.0f);
        ImGui::SliderFloat("Blue", &triangleColor[2], 0.0f, 1.0f);
        ImGui::Text("Mouse Speed:");
        ImGui::SliderFloat("Mouse Sensitivity", &mouseSpeed, 0.01f, 1.0f); // 控制鼠标灵敏度
        ImGui::SliderFloat("Move Speed", &moveSpeed, 0.1f, 10.0f); // 设置范围从 0.1 到 10.0
        ImGui::End();

        imguiManager.EndFrame();

        // 交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);  // 释放 EBO

    imguiManager.Shutdown();
    glfwTerminate();
    delete inputManager;
    return 0;
}
