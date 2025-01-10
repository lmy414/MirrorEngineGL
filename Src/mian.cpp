#include "../Src/gui/gui.h"
#include "../Src/Render/opengl_utils.h"
#include "../Src/Render/shader.h"
#include"../Src/Render/vertex_buffer.h"
#include <iostream>

int main() {
    // 初始化 OpenGL 和窗口
    GLFWwindow* window = InitializeOpenGL(800, 600, "MirrorEngine");
    if (!window) return -1;

	
    // 创建 Shader 对象并加载着色器
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");

    // 设置顶点数据和缓冲
    unsigned int VBO, VAO;
    SetupVertexBuffers(VBO, VAO);  // 使用新函数设置顶点缓冲
    
    // 初始化 ImGui
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);

    // 初始颜色值
    float triangleColor[3] = { 0.5f, 0.2f, 0.8f };


    // 主渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 输入处理
        processInput(window);

        // 使用着色器程序
        shader.use();
        // 传递颜色值到着色器
        int colorLocation = glGetUniformLocation(shader.ID, "triangleColor");
        if (colorLocation == -1) {
            //std::cerr << "ERROR::SHADER::UNIFORM::triangleColor not found" << std::endl;
        }
        shader.setVec3("triangleColor", triangleColor[0], triangleColor[1], triangleColor[2]);
        

        // 清空屏幕
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制三角形
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 启动 ImGui 界面
        imguiManager.BeginFrame();

        ImGui::Begin("Triangle Color Control");
        ImGui::Text("Use sliders to change the triangle color:");
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
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    imguiManager.Shutdown();
    glfwTerminate();
    return 0;
}
