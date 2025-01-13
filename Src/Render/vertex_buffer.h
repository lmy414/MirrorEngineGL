#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <vector>
#include "../Utils/mesh.h"

// 使用 Mesh 类创建顶点和索引缓冲区
void SetupVertexBuffers(
    unsigned int& VBO,
    unsigned int& VAO,
    unsigned int& EBO,
    const Mesh& mesh);  // 传入 Mesh 类的实例

#endif
