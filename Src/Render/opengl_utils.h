#ifndef OPENGL_UTILS_H
#define OPENGL_UTILS_H
#define GLFW_INCLUDE_NONE // 避免 GLFW 自动包含 OpenGL 的头文件

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"


// 初始化 OpenGL 和创建窗口
GLFWwindow* InitializeOpenGL(int width, int height, const char* title);

// 帧缓冲大小回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// 输入处理函数

#endif // OPENGL_UTILS_H
#pragma once
