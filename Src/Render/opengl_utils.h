#ifndef OPENGL_UTILS_H
#define OPENGL_UTILS_H
#define GLFW_INCLUDE_NONE // ���� GLFW �Զ����� OpenGL ��ͷ�ļ�

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"


// ��ʼ�� OpenGL �ʹ�������
GLFWwindow* InitializeOpenGL(int width, int height, const char* title);

// ֡�����С�ص�
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// ���봦����

#endif // OPENGL_UTILS_H
#pragma once
