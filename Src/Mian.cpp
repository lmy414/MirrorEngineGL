#include "Common.h"

// 主渲染循环
int main() {
    // 初始化 OpenGL 和窗口
    GLFWwindow* window = InitializeOpenGL(800, 600, "E Mao Engine");
    if (!window) return -1;

    // 主渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 清空屏幕
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
