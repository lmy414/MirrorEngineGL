#include "Common.h"

// ȫ���������
Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // ��ʼ�����λ��

float mouseSpeed = 0.1f; // ���������
float moveSpeed = 0.1f;  // �����ƶ��ٶ�

InputManager* inputManager = nullptr;  // ���������

// ȫ�ֻ���������
unsigned int VBO, VAO, EBO;

int main() {
    // ��ʼ�� OpenGL �ʹ���
    GLFWwindow* window = InitializeOpenGL(800, 600, "MirrorEngine");
    if (!window) return -1;

    // �������������ʵ��
    inputManager = new InputManager(camera, moveSpeed, mouseSpeed);

    // ע������ص�����
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        inputManager->MouseCallback(window, xpos, ypos);
        });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        inputManager->MouseButtonCallback(window, button, action, mods);
        });

    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);

    // ��������������þ���
    MatrixManager matrixManager;
    matrixManager.SetModelMatrix(glm::mat4(1.0f)); // ��λ����
    matrixManager.SetViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // �����
    matrixManager.SetPerspectiveProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // ͸��ͶӰ

    // ���� Shader ���󲢼�����ɫ��
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");

    // ����ģ��
    ModelLoader modelLoader;
    if (!modelLoader.LoadModel("./Assets/obj/text.obj")) {
        std::cerr << "Failed to load model!" << std::endl;
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
        // ��ȡ֡ʱ��
        float deltaTime = 0.016f;  // ����̶�֡ʱ�䣨�����滻Ϊʵ�ʵ� deltaTime��

        // ��������
        inputManager->ProcessInput(window, deltaTime);

        // ��ȡ����
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = matrixManager.GetProjectionMatrix();

        // ����ģ�;��󣬽����ת�Ƕ�
        glm::mat4 model = matrixManager.GetModelMatrix();

        // ���Ե�ǰ��ת�Ƕ�Ӧ����ת�������ۼ�
        model = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // �� X ��
        model = glm::rotate(model, glm::radians(rotationAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // �� Y ��
        model = glm::rotate(model, glm::radians(rotationAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // �� Z ��
        matrixManager.SetModelMatrix(model); // ����ģ�;���

        // ʹ����ɫ������
        shader.use();

        // �����Ļ
        glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ��Ⱦÿ������
        for (const Mesh& mesh : modelLoader.meshes) {
            SetupVertexBuffers(VBO, VAO, EBO, mesh); // ��ʼ�� VBO, VAO, EBO

            // ��������Ԫ
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);  // ������Ҫ������������еĻ�
            glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);  // �����������ɫ��

            // ������ɫֵ����ɫ��
            shader.setVec3("triangleColor", triangleColor[0], triangleColor[1], triangleColor[2]);

            // ���ݾ�����ɫ��
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

            // ��������
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        // ���� ImGui ����
        imguiManager.BeginFrame();

        if (ImGui::Button("Reset Camera")) {
            camera.ResetCamera();  // �����������ʼλ�úͳ���
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
        ImGui::SliderFloat("Mouse Sensitivity", &mouseSpeed, 0.01f, 1.0f); // �������������
        ImGui::SliderFloat("Move Speed", &moveSpeed, 0.1f, 10.0f); // ���÷�Χ�� 0.1 �� 10.0
        ImGui::End();

        imguiManager.EndFrame();

        // ��������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �ͷ���Դ
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);  // �ͷ� EBO

    imguiManager.Shutdown();
    glfwTerminate();
    delete inputManager;
    return 0;
}
