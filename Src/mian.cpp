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
    GLFWwindow* window = InitializeOpenGL(1920, 1080, "MirrorEngine");
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
    matrixManager.SetFixedPerspectiveProjection(45.0f, 0.1f, 100.0f);

    // ���� Shader ���󲢼�����ɫ��
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");

    // ����ģ��
    ModelLoader modelLoader;
    if (!modelLoader.LoadModel("./Assets/obj/text2.fbx")) {
        std::cerr << "Failed to load model!" << std::endl;
        return -1;
    }

    // ��ȡģ���е���������
    std::vector<Mesh> meshes = modelLoader.GetMeshes();

    // ��ʼ�� ImGui
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);


    CreateOpenGLTexture(1920, 1080);


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
        glm::mat4 projection = matrixManager.GetProjectionMatrix();  // ��ȡͶӰ����

        // ����ģ�;��󣬽����ת�Ƕ�
        glm::mat4 model = matrixManager.GetModelMatrix();

        // ���Ե�ǰ��ת�Ƕ�Ӧ����ת�������ۼ�
        model = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // �� X ��
        model = glm::rotate(model, glm::radians(rotationAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // �� Y ��
        model = glm::rotate(model, glm::radians(rotationAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // �� Z ��
        matrixManager.SetModelMatrix(model); // ����ģ�;���

        // ʹ����ɫ������
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // ���´��ڴ�С������ͶӰ����
        matrixManager.SetWindowSize(width, height);

        // ��ȡ��ǰͶӰ����
        projection = matrixManager.GetProjectionMatrix();
        GLuint projectionLocation = glGetUniformLocation(shader.ID, "projection");

        // ����Ⱦ�����д��ݾ�����ɫ��
        shader.use();
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        // �����Ļ
        glClearColor(triangleColor[0], triangleColor[1], triangleColor[2], 1.0f); // ʹ�ö�̬��ɫ
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ��Ⱦÿ������
        for (Mesh& mesh : meshes) {
            mesh.Render(shader, model, view, projection);  // ��Ⱦÿ������
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
