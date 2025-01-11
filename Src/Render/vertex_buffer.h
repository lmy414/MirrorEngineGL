#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <vector>

// 顶点和索引数据


void SetupVertexBuffers(
    unsigned int& VBO,
    unsigned int& VAO,
    unsigned int& EBO,
    const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices);

#endif
