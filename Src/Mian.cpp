#include "Common.h"


// ȫ���������
Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// ����ģ�ͱ任�Ķ���
TransformControls transformControls;

// ����Ⱦѭ��
int main() {
    // ��ʼ�� OpenGL �ʹ���
    GLFWwindow* window = InitializeOpenGL(800, 600, "Basic Mesh Rendering");
    if (!window) return -1;

    // ��������ʼ�� ImGui ������
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);  // ��ʼ�� ImGui

    // ���� Shader ���󲢼�����ɫ��
    Shader shader("E:/MirrorEngine/MirrorEngine2/Shaders/Model.vs", "E:/MirrorEngine/MirrorEngine2/Shaders/Model.fs");

    // ʹ�� ModelPool ������ģ��
    std::shared_ptr<Model> model = ModelPool::Instance().LoadModel("cube", "Assets/m/cs2.fbx");  // ͨ�����Ƽ���ģ��
    Mesh mesh;

    // ����Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        // ��ȡ֡ʱ��
        float deltaTime = 0.016f;  // ����̶�֡ʱ��

        // �����Ļ
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ��ʼ ImGui ��һ֡
        imguiManager.BeginFrame();

        // ���� GUI �ؼ�
        ImGui::Begin("Transform Controls");
        transformControls.DrawGUI();  // ������ת�����š�λ�ÿؼ�
        ImGui::End();

        // ��ȡ�任����
        glm::mat4 modelMatrix = transformControls.GetTransformMatrix();

        // ��ȡ����
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // ʹ����ɫ��
        shader.use();
        shader.setMat4("model", modelMatrix);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // ��Ⱦģ��
        mesh.Render(shader, modelMatrix, view, projection);

        // ��Ⱦ ImGui ����
        imguiManager.EndFrame();  // ���� ImGui ��Ⱦ

        // ��������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �ر� ImGui
    imguiManager.Shutdown();

    glfwTerminate();
    return 0;
}
