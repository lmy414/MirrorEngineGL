#include "Common.h"

int main() {
    // ��ʼ�� OpenGL �ʹ���
    GLFWwindow* window = InitializeOpenGL(800, 600, "MirrorEngine");
    if (!window) return -1;

    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);

    // ��������������þ���
    MatrixManager matrixManager;
    matrixManager.SetModelMatrix(glm::mat4(1.0f)); // ��λ����
    matrixManager.SetViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // �����
    matrixManager.SetPerspectiveProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // ͸��ͶӰ

    // ���� Shader ���󲢼�����ɫ��
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");

    Cube cube; // �������������
    const auto& cubeVertices = cube.GetVertices();
    const auto& cubeIndices = cube.GetIndices();

    // ���ö������ݺͻ���
    unsigned int cubeVBO, cubeVAO, cubeEBO;
    SetupVertexBuffers(cubeVBO, cubeVAO, cubeEBO, cubeVertices, cubeIndices);

    // ��������
    unsigned int texture1 = TextureLoader::LoadTexture("./Assets/tex/6-1948-����2.png");
    if (texture1 == 0) {
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
    }

    // ��ʼ�� ImGui
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);

    // ��ʼ��ɫֵ����ת�Ƕ�
    float triangleColor[3] = { 0.5f, 0.2f, 0.8f };
    float rotationAngles[3] = { 0.0f, 0.0f, 0.0f }; // X, Y, Z �����ת�Ƕ�

    // ����Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        // ���봦��
        processInput(window);

        // ��ȡ����
        glm::mat4 view = matrixManager.GetViewMatrix();
        glm::mat4 projection = matrixManager.GetProjectionMatrix();

        // ����ģ�;��󣬽����ת�Ƕ�
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotationAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // �� X ��
        model = glm::rotate(model, glm::radians(rotationAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // �� Y ��
        model = glm::rotate(model, glm::radians(rotationAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // �� Z ��

        // ʹ����ɫ������
        shader.use();

        // ��������Ԫ 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); // �������ݸ���ɫ��

        // ������ɫֵ����ɫ��
        shader.setVec3("triangleColor", triangleColor[0], triangleColor[1], triangleColor[2]);

        // ���ݾ�����ɫ��
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // �����Ļ
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ����������
        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(cubeIndices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // ���� ImGui ����
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

        // ��������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �ͷ���Դ
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    imguiManager.Shutdown();
    glfwTerminate();
    return 0;
}
