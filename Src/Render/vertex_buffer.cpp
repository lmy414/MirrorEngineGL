#include "vertex_buffer.h"

void SetupVertexBuffers(
    unsigned int& VBO,
    unsigned int& VAO,
    unsigned int& EBO,
    const Mesh& mesh) // 直接使用 Mesh 类
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices = mesh.indices;

    // 填充顶点数据：位置、法线、纹理坐标
    for (size_t i = 0; i < mesh.vertices.size(); ++i) {
        const glm::vec3& vertex = mesh.vertices[i];
        const glm::vec3& normal = mesh.normals[i];
        const glm::vec2& texCoord = mesh.texCoords[i];

        // 每个顶点包含：位置（3），法线（3），纹理坐标（2），所以每个顶点有 8 个 float
        vertices.push_back(vertex.x);
        vertices.push_back(vertex.y);
        vertices.push_back(vertex.z);

        vertices.push_back(normal.x);
        vertices.push_back(normal.y);
        vertices.push_back(normal.z);

        vertices.push_back(texCoord.x);
        vertices.push_back(texCoord.y);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // 顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // 索引缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // 设置顶点属性：位置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);                // 位置
    glEnableVertexAttribArray(0);

    // 设置顶点属性：法线
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // 法线
    glEnableVertexAttribArray(1);

    // 设置顶点属性：纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // 纹理坐标
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);  // 解绑 VAO
}
