#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include "../Render/camera.h" // 

class InputManager {
public:
    // 构造函数，传入 Camera 引用、移动速度和鼠标灵敏度
    InputManager(Core::Camera& camera, float moveSpeed = 2.5f, float mouseSpeed = 0.1f);

    // 处理键盘输入（W, A, S, D等）
    void ProcessInput(GLFWwindow* window, float deltaTime);

    // 鼠标按键回调函数
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    // 鼠标移动回调函数
    void MouseCallback(GLFWwindow* window, double xpos, double ypos);

private:
    Core::Camera& camera;   // 引用相机对象
    bool isRightMousePressed; // 右键是否被按下
    bool firstMouse;          // 是否是第一次鼠标回调
    float lastX, lastY;      // 上次鼠标坐标
    float moveSpeed;         // 移动速度
    float mouseSpeed;        // 鼠标灵敏度
};

#endif // INPUTMANAGER_H
