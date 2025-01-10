#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#define GLFW_INCLUDE_NONE // 避免 GLFW 自动包含 OpenGL 的头文件

#include <glad/glad.h>

extern float vertices[9];  // 3 * 3 的三角形顶点数据

void SetupVertexBuffers(unsigned int& VBO, unsigned int& VAO);

#endif // VERTEX_BUFFER_H
#pragma once
