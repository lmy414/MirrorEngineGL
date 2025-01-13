#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include "../Render/camera.h" // 

class InputManager {
public:
    // ���캯�������� Camera ���á��ƶ��ٶȺ����������
    InputManager(Core::Camera& camera, float moveSpeed = 2.5f, float mouseSpeed = 0.1f);

    // ����������루W, A, S, D�ȣ�
    void ProcessInput(GLFWwindow* window, float deltaTime);

    // ��갴���ص�����
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    // ����ƶ��ص�����
    void MouseCallback(GLFWwindow* window, double xpos, double ypos);

private:
    Core::Camera& camera;   // �����������
    bool isRightMousePressed; // �Ҽ��Ƿ񱻰���
    bool firstMouse;          // �Ƿ��ǵ�һ�����ص�
    float lastX, lastY;      // �ϴ��������
    float moveSpeed;         // �ƶ��ٶ�
    float mouseSpeed;        // ���������
};

#endif // INPUTMANAGER_H
