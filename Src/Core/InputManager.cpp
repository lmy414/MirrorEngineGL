#include "InputManager.h"

InputManager::InputManager(Core::Camera& camera, float moveSpeed, float mouseSpeed)
    : camera(camera), moveSpeed(moveSpeed), mouseSpeed(mouseSpeed), isRightMousePressed(false), firstMouse(true), lastX(0.0f), lastY(0.0f) {
}

// 处理键盘输入，移动相机
void InputManager::ProcessInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // 计算每一帧的移动速度
    float velocity = moveSpeed * deltaTime;

    // 处理 WASD 和 Q/E 键的输入
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(Core::CameraMovement::FORWARD, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(Core::CameraMovement::BACKWARD, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(Core::CameraMovement::LEFT, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(Core::CameraMovement::RIGHT, velocity);
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(Core::CameraMovement::DOWN, velocity);  // 向下移动
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(Core::CameraMovement::UP, velocity);  // 向上移动
    }
}

// 鼠标按键回调函数
void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            isRightMousePressed = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏并锁定光标
        }
        else if (action == GLFW_RELEASE) {
            isRightMousePressed = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // 恢复光标显示
        }
    }
}

// 鼠标移动回调函数
void InputManager::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (!isRightMousePressed) {
        firstMouse = true;  // 如果没有按住右键，重置第一次鼠标回调标志
        return;
    }

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // 计算鼠标偏移量
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;  // Y轴方向是反的
    lastX = xpos;
    lastY = ypos;

    // 根据鼠标灵敏度调整相机旋转速度
    xoffset *= mouseSpeed;
    yoffset *= mouseSpeed;

    // 处理鼠标输入，更新相机的朝向
    camera.ProcessMouseMovement(xoffset, yoffset);
}
