#include "Common.h"

// 全局相机对象
Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // 初始化相机位置

DirectionalLight dirLight(
    glm::vec3(-0.2f, -1.0f, -0.3f),   // 光源方向
    glm::vec3(1.0f, 1.0f, 1.0f),       // 白色光源
    1.0f                               // 光照强度
);

float mouseSpeed = 0.1f; // 鼠标灵敏度
float moveSpeed = 0.1f;  // 键盘移动速度

InputManager* inputManager = nullptr;  // 输入管理器


//全局缓冲对象变量
unsigned int VBO, VAO, EBO;

int main() {
    // 初始化 OpenGL 和窗口
    GLFWwindow* window = InitializeOpenGL(1920, 1080, "E Mao Engine");
    if (!window) return -1;

    // 创建矩阵管理器并设置初始矩阵
    MatrixManager matrixManager;
    matrixManager.SetWindowSize(1920, 1080); // 设置窗口大小

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

    // 设置矩阵
    matrixManager.SetModelMatrix(glm::mat4(1.0f)); // 单位矩阵
    matrixManager.SetViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // 摄像机
    matrixManager.SetFixedPerspectiveProjection(45.0f, 0.1f, 100.0f, 1920.0f / 1080.0f); // 设置投影矩阵

    // 设置矩阵管理器为窗口的用户数据
    glfwSetWindowUserPointer(window, &matrixManager);

    // 创建 Shader 对象并加载着色器
    Shader shader("Shaders/VertexShader.glsl", "Shaders/PixelShader.glsl");
    unsigned int diffuseTexture = TextureLoader::LoadTexture("Assets/tex/cs3.png");//加载纹理

    // 加载模型
    modelLoader modelLoader;
    const auto& allMeshes = modelLoader.GetAllMeshes();  // 获取所有加载的网格数据

    // 初始化 ImGui
    ImGuiManager imguiManager;
    imguiManager.Initialize(window);
    
    // 初始颜色值和旋转角度
    float triangleColor[3] = { 0.0f, 0.0f, 0.0f };
    float rotationAngles[3] = { 0.0f, 0.0f, 0.0f }; // X, Y, Z 轴的旋转角度

    shader.setVec3("viewPos", camera.Position);//获取相机位置

    // 主渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 获取帧时间
        float deltaTime = 0.016f;  // 假设固定帧时间（可以替换为实际的 deltaTime）

        // 处理输入
        inputManager->ProcessInput(window, deltaTime);

        // 获取矩阵
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = matrixManager.GetProjectionMatrix();  // 获取投影矩阵

        dirLight.SetLightUniforms(shader);  // 设置光源 uniform 到着色器
        Material mat(glm::vec3(triangleColor[0], triangleColor[1], triangleColor[2]), diffuseTexture);
        mat.SetMaterialUniforms(shader);//创建材质实例
       

        // 使用着色器程序
        shader.use();
        
        // 清空屏幕
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 黑色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 渲染每个网格
        for (const auto& modelMeshes : allMeshes) {
            for (const auto& mesh : modelMeshes) {
                // 创建模型矩阵，结合旋转角度
                glm::mat4 model = glm::mat4(1.0f); // 重置为单位矩阵

                // 应用旋转变换
                model = glm::rotate(model, glm::radians(rotationAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕 X 轴旋转
                model = glm::rotate(model, glm::radians(rotationAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕 Y 轴旋转
                model = glm::rotate(model, glm::radians(rotationAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕 Z 轴旋转

                // 渲染网格
                mesh.Render(shader, model, view, projection);
            }
        }

        // 启动 ImGui 界面
        imguiManager.BeginFrame();

        if (ImGui::Button("Reset Camera")) {
            camera.ResetCamera();  // 重置相机到初始位置和朝向
        }

        if (ImGui::Button("Open Model")) {
            // 打开文件选择对话框
            ImGuiFileDialog::Instance()->OpenDialog("ChooseModelDlgKey", "Choose a model file", ".obj,.fbx");
        }

        // 如果文件选择对话框打开并且选择了文件
        if (ImGuiFileDialog::Instance()->Display("ChooseModelDlgKey")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();  // 获取文件路径
                std::cout << "Selected model: " << filePath << std::endl;

                // 加载选择的模型文件
                std::vector<std::string> newModelPaths = { filePath };
                if (!modelLoader.LoadModels(newModelPaths)) {
                    std::cerr << "Failed to load selected model!" << std::endl;
                }
                else {
                    std::cout << "Model loaded successfully!" << std::endl;
                }
            }
            ImGuiFileDialog::Instance()->Close();  // 关闭对话框
        }

        // Cube 控制面板
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
        
        ImGui::Begin("Lighting Control");
        // 修改光照方向
        ImGui::SliderFloat("Light Direction X", &dirLight.direction.x, -1.0f, 1.0f);
        ImGui::SliderFloat("Light Direction Y", &dirLight.direction.y, -1.0f, 1.0f);
        ImGui::SliderFloat("Light Direction Z", &dirLight.direction.z, -1.0f, 1.0f);
        
        // 修改光源颜色
        ImGui::ColorEdit3("Light Color", &dirLight.color[0]);
        
        // 修改光照强度
        ImGui::SliderFloat("Light Intensity", &dirLight.intensity, 0.0f, 10.0f);
        
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
