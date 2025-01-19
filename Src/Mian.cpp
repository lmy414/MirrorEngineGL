#include "Common.h"

// ȫ���������
Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // ��ʼ�����λ��

DirectionalLight dirLight(
    glm::vec3(-0.2f, -1.0f, -0.3f),   // ��Դ����
    glm::vec3(1.0f, 1.0f, 1.0f),       // ��ɫ��Դ
    1.0f                               // ����ǿ��
);

float mouseSpeed = 0.1f; // ���������
float moveSpeed = 0.1f;  // �����ƶ��ٶ�

InputManager* inputManager = nullptr;  // ���������

// ȫ�ֻ���������
unsigned int VBO, VAO, EBO;

int main() {
    // ��ʼ�� OpenGL �ʹ���
    GLFWwindow* window = InitializeOpenGL(800, 600, "E Mao Engine");
    if (!window) return -1;

    // ������������������ó�ʼ����
    MatrixManager matrixManager;
    //matrixManager.SetWindowSize(1920, 1080); // ���ô��ڴ�С

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
    Shader shader("E:/MirrorEngine/MirrorEngine2/Shaders/Model.vs", "E:/MirrorEngine/MirrorEngine2/Shaders/Model.fs");
    // ʹ��ָ��·������ Texture2D ���󣬲�ָ����������
    Texture2D* diffuseTexture = new Texture2D("Assets/tex/cs3.png", Texture2D::ETexType::SRGB, false);
    // ����ģ��
    Model* models = new Model();  // ������Ҫ���ص�ģ��·��

    // ��ʼ�� ImGui
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);
    
    // ��ʼ��ɫֵ����ת�Ƕ�
    float triangleColor[3] = { 1.0f, 1.0f, 1.0f };
    float rotationAngles[3] = { 0.0f, 0.0f, 0.0f }; // X, Y, Z �����ת�Ƕ�

    shader.setVec3("viewPos", camera.Position); // ��ȡ���λ��

    // ����Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        // ��ȡ֡ʱ��
        float deltaTime = 0.016f;  // ����̶�֡ʱ�䣨�����滻Ϊʵ�ʵ� deltaTime��

        // ��������
        inputManager->ProcessInput(window, deltaTime);

        // ��ȡ����
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = matrixManager.GetProjectionMatrix();  // ��ȡͶӰ����

        
        shader.use();
        dirLight.SetLightUniforms(shader);  // ���ù�Դ uniform ����ɫ��
        
        // �����Ļ
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // ��ɫ
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        // ����ģ�;���
        glm::mat4 model = glm::mat4(1.0f); // ��ʼ��Ϊ��λ����

        // Ӧ���� X, Y, Z �����ת
        model = glm::rotate(model, glm::radians(rotationAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // �� X ����ת
        model = glm::rotate(model, glm::radians(rotationAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // �� Y ����ת
        model = glm::rotate(model, glm::radians(rotationAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // �� Z ����ת
        
        // ��Ⱦģ��
        for (Mesh* mesh : models->meshes)
        {
            mesh->Render(shader,model,view,projection);
        }

        // ���� ImGui ����
        imguiManager.BeginFrame();


        ImGui::Begin(u8"�˵�");
        // ���ð�ť�������ð�ť��С
        if (ImGui::Button(u8"�������", ImVec2(60, 30))) {
                camera.ResetCamera();  // �����������ʼλ�úͳ���
        }
        if (ImGui::Button(u8"����ģ��", ImVec2(60, 30))) {
                // ���ļ�ѡ��Ի���
                ImGuiFileDialog::Instance()->OpenDialog("ChooseModelDlgKey", "Choose a model file", ".obj,.fbx");
        }
        ImGui::End();
        
        // ����ļ�ѡ��Ի���򿪲���ѡ�����ļ�
        if (ImGuiFileDialog::Instance()->Display("ChooseModelDlgKey")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();  // ��ȡ�ļ�·��
                std::cout << "Selected model: " << filePath << std::endl;

                // ����ѡ���ģ���ļ�
                Model* newModel = new Model(filePath);
                if (newModel != nullptr) {
                    models = newModel;  // ���µ�ǰģ��
                } else {
                    std::cerr << "Failed to load selected model!" << std::endl;
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

        ImGui::Begin("Lighting Control");
        // �޸Ĺ��շ���
        ImGui::SliderFloat("Light Direction X", &dirLight.direction.x, -1.0f, 1.0f);
        ImGui::SliderFloat("Light Direction Y", &dirLight.direction.y, -1.0f, 1.0f);
        ImGui::SliderFloat("Light Direction Z", &dirLight.direction.z, -1.0f, 1.0f);
        dirLight.SetDirection(dirLight.direction);  // ʹ���·���

        // �޸Ĺ�Դ��ɫ
        ImGui::ColorEdit3("Light Color", &dirLight.color[0]);
        dirLight.SetColor(dirLight.color);  // ʹ���·���

        // �޸Ĺ���ǿ��
        ImGui::SliderFloat("Light Intensity", &dirLight.intensity, 0.0f, 10.0f);
        dirLight.SetIntensity(dirLight.intensity);  // ʹ���·���

        ImGui::End();

        imguiManager.EndFrame();

        // ��������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �ͷ���Դ
    delete models;  // ɾ��ģ��

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);  // �ͷ� EBO

    imguiManager.Shutdown();
    glfwTerminate();
    delete inputManager;
    return 0;
}
