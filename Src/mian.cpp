#include "Common.h"

// ȫ���������
Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // ��ʼ�����λ��

float mouseSpeed = 0.1f; // ���������
float moveSpeed = 0.1f;  // �����ƶ��ٶ�

InputManager* inputManager = nullptr;  // ���������

//ȫ�ֻ���������
unsigned int VBO, VAO, EBO;

int main() {
    // ��ʼ�� OpenGL �ʹ���
    GLFWwindow* window = InitializeOpenGL(1920, 1080, "E Mao Engine");
    if (!window) return -1;

    // ������������������ó�ʼ����
    MatrixManager matrixManager;
    matrixManager.SetWindowSize(1920, 1080); // ���ô��ڴ�С

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

    // ���þ���
    matrixManager.SetModelMatrix(glm::mat4(1.0f)); // ��λ����
    matrixManager.SetViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // �����
    matrixManager.SetFixedPerspectiveProjection(45.0f, 0.1f, 100.0f, 1920.0f / 1080.0f); // ����ͶӰ����

    // ���þ��������Ϊ���ڵ��û�����
    glfwSetWindowUserPointer(window, &matrixManager);

    // ���� Shader ���󲢼�����ɫ��
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");

    // ����ģ��
    ModelLoader modelLoader;
    const auto& allMeshes = modelLoader.GetAllMeshes();  // ��ȡ���м��ص���������

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
        glm::mat4 projection = matrixManager.GetProjectionMatrix();  // ��ȡͶӰ����

        // ʹ����ɫ������
        shader.use();

        // �����Ļ
        glClearColor(triangleColor[0], triangleColor[1], triangleColor[2], 1.0f); // ʹ�ö�̬��ɫ
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ��Ⱦÿ������
        for (const auto& modelMeshes : allMeshes) {
            for (const auto& mesh : modelMeshes) {
                // ����ģ�;��󣬽����ת�Ƕ�
                glm::mat4 model = glm::mat4(1.0f); // ����Ϊ��λ����

                // Ӧ����ת�任
                model = glm::rotate(model, glm::radians(rotationAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // �� X ����ת
                model = glm::rotate(model, glm::radians(rotationAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // �� Y ����ת
                model = glm::rotate(model, glm::radians(rotationAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // �� Z ����ת

                // ��Ⱦ����
                mesh.Render(shader, model, view, projection);
            }
        }

        // ���� ImGui ����
        imguiManager.BeginFrame();

        if (ImGui::Button("Reset Camera")) {
            camera.ResetCamera();  // �����������ʼλ�úͳ���
        }

        if (ImGui::Button("Open Model")) {
            // ���ļ�ѡ��Ի���
            ImGuiFileDialog::Instance()->OpenDialog("ChooseModelDlgKey", "Choose a model file", ".obj,.fbx");
        }

        // ����ļ�ѡ��Ի���򿪲���ѡ�����ļ�
        if (ImGuiFileDialog::Instance()->Display("ChooseModelDlgKey")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();  // ��ȡ�ļ�·��
                std::cout << "Selected model: " << filePath << std::endl;

                // ����ѡ���ģ���ļ�
                std::vector<std::string> newModelPaths = { filePath };
                if (!modelLoader.LoadModels(newModelPaths)) {
                    std::cerr << "Failed to load selected model!" << std::endl;
                }
                else {
                    std::cout << "Model loaded successfully!" << std::endl;
                }
            }
            ImGuiFileDialog::Instance()->Close();  // �رնԻ���
        }

        // Cube �������
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
