#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#define GLFW_INCLUDE_NONE // ���� GLFW �Զ����� OpenGL ��ͷ�ļ�

#include <glad/glad.h>

extern float vertices[9];  // 3 * 3 �������ζ�������

void SetupVertexBuffers(unsigned int& VBO, unsigned int& VAO);

#endif // VERTEX_BUFFER_H
#pragma once
