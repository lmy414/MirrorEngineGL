#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <vector>
#include "../Utils/mesh.h"

// ʹ�� Mesh �ഴ�����������������
void SetupVertexBuffers(
    unsigned int& VBO,
    unsigned int& VAO,
    unsigned int& EBO,
    const Mesh& mesh);  // ���� Mesh ���ʵ��

#endif
