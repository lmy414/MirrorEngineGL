#include "../Src/gui/gui.h"
#include "../Src/Render/opengl_utils.h"
#include "../Src/Render/shader.h"
#include"../Src/Render/vertex_buffer.h"
#include <iostream>

int main() {
    // ��ʼ�� OpenGL �ʹ���
    GLFWwindow* window = InitializeOpenGL(800, 600, "MirrorEngine");
    if (!window) return -1;

	
    // ���� Shader ���󲢼�����ɫ��
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");

    // ���ö������ݺͻ���
    unsigned int VBO, VAO;
    SetupVertexBuffers(VBO, VAO);  // ʹ���º������ö��㻺��
    
    // ��ʼ�� ImGui
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);

    // ��ʼ��ɫֵ
    float triangleColor[3] = { 0.5f, 0.2f, 0.8f };


    // ����Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        // ���봦��
        processInput(window);

        // ʹ����ɫ������
        shader.use();
        // ������ɫֵ����ɫ��
        int colorLocation = glGetUniformLocation(shader.ID, "triangleColor");
        if (colorLocation == -1) {
            //std::cerr << "ERROR::SHADER::UNIFORM::triangleColor not found" << std::endl;
        }
        shader.setVec3("triangleColor", triangleColor[0], triangleColor[1], triangleColor[2]);
        

        // �����Ļ
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ����������
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ���� ImGui ����
        imguiManager.BeginFrame();

        ImGui::Begin("Triangle Color Control");
        ImGui::Text("Use sliders to change the triangle color:");
        ImGui::SliderFloat("Red", &triangleColor[0], 0.0f, 1.0f);
        ImGui::SliderFloat("Green", &triangleColor[1], 0.0f, 1.0f);
        ImGui::SliderFloat("Blue", &triangleColor[2], 0.0f, 1.0f);
        ImGui::End();

        imguiManager.EndFrame();

        // ��������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �ͷ���Դ
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    imguiManager.Shutdown();
    glfwTerminate();
    return 0;
}
