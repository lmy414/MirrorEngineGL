#include "Common.h"

// ����Ⱦѭ��
int main() {
    // ��ʼ�� OpenGL �ʹ���
    GLFWwindow* window = InitializeOpenGL(800, 600, "E Mao Engine");
    if (!window) return -1;

    // ����Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        // �����Ļ
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ��������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
