#include "InputManager.h"

InputManager::InputManager(Core::Camera& camera, float moveSpeed, float mouseSpeed)
    : camera(camera), moveSpeed(moveSpeed), mouseSpeed(mouseSpeed), isRightMousePressed(false), firstMouse(true), lastX(0.0f), lastY(0.0f) {
}

// ����������룬�ƶ����
void InputManager::ProcessInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // ����ÿһ֡���ƶ��ٶ�
    float velocity = moveSpeed * deltaTime;

    // ���� WASD �� Q/E ��������
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
        camera.ProcessKeyboard(Core::CameraMovement::DOWN, velocity);  // �����ƶ�
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(Core::CameraMovement::UP, velocity);  // �����ƶ�
    }
}

// ��갴���ص�����
void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            isRightMousePressed = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ���ز��������
        }
        else if (action == GLFW_RELEASE) {
            isRightMousePressed = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // �ָ������ʾ
        }
    }
}

// ����ƶ��ص�����
void InputManager::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (!isRightMousePressed) {
        firstMouse = true;  // ���û�а�ס�Ҽ������õ�һ�����ص���־
        return;
    }

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // �������ƫ����
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;  // Y�᷽���Ƿ���
    lastX = xpos;
    lastY = ypos;

    // ������������ȵ��������ת�ٶ�
    xoffset *= mouseSpeed;
    yoffset *= mouseSpeed;

    // ����������룬��������ĳ���
    camera.ProcessMouseMovement(xoffset, yoffset);
}
