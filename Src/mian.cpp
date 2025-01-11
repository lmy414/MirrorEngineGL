#include "Common.h"

int main() {
    // 初始化 OpenGL 和窗口
    GLFWwindow* window = InitializeOpenGL(800, 600, "MirrorEngine");
    if (!window) return -1;

    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    // 创建矩阵对象并设置矩阵
    MatrixManager matrixManager;
    matrixManager.SetModelMatrix(glm::mat4(1.0f)); // 单位矩阵
    matrixManager.SetViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // 摄像机
    matrixManager.SetPerspectiveProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // 透视投影

    // 创建 Shader 对象并加载着色器
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");

    Cube cube; // 创建立方体对象
    const auto& cubeVertices = cube.GetVertices();
    const auto& cubeIndices = cube.GetIndices();

    // 设置顶点数据和缓冲
    unsigned int cubeVBO, cubeVAO, cubeEBO;
    SetupVertexBuffers(cubeVBO, cubeVAO, cubeEBO, cubeVertices, cubeIndices);

    // 加载纹理
    unsigned int texture1 = TextureLoader::LoadTexture("./Assets/tex/6-1948-生气2.png");
    if (texture1 == 0) {
        std::cerr << "Failed to load texture!" << std::endl;
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
        // 输入处理
        processInput(window);

        // 获取矩阵
        glm::mat4 view = matrixManager.GetViewMatrix();
        glm::mat4 projection = matrixManager.GetProjectionMatrix();

        // 创建模型矩阵，结合旋转角度
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotationAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕 X 轴
        model = glm::rotate(model, glm::radians(rotationAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕 Y 轴
        model = glm::rotate(model, glm::radians(rotationAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕 Z 轴

        // 使用着色器程序
        shader.use();

        // 激活纹理单元 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); // 将纹理传递给着色器

        // 传递颜色值到着色器
        shader.setVec3("triangleColor", triangleColor[0], triangleColor[1], triangleColor[2]);

        // 传递矩阵到着色器
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // 清空屏幕
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 绘制立方体
        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(cubeIndices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // 启动 ImGui 界面
        imguiManager.BeginFrame();

        ImGui::Begin("Cube Control");
        ImGui::Text("Adjust cube rotation:");
        ImGui::SliderFloat("Rotate X", &rotationAngles[0], 0.0f, 360.0f);
        ImGui::SliderFloat("Rotate Y", &rotationAngles[1], 0.0f, 360.0f);
        ImGui::SliderFloat("Rotate Z", &rotationAngles[2], 0.0f, 360.0f);
        ImGui::Text("Change color:");
        ImGui::SliderFloat("Red", &triangleColor[0], 0.0f, 1.0f);
        ImGui::SliderFloat("Green", &triangleColor[1], 0.0f, 1.0f);
        ImGui::SliderFloat("Blue", &triangleColor[2], 0.0f, 1.0f);
        ImGui::End();

        imguiManager.EndFrame();

        // 交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放资源
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    imguiManager.Shutdown();
    glfwTerminate();
    return 0;
}
