#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>

// 顶点和索引数据
extern float vertices[];
extern unsigned int indices[];

void SetupVertexBuffers(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO);

#endif
