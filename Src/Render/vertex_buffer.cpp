#include "vertex_buffer.h"

void SetupVertexBuffers(
    unsigned int& VBO,
    unsigned int& VAO,
    unsigned int& EBO,
    const Mesh& mesh) // ֱ��ʹ�� Mesh ��
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices = mesh.indices;

    // ��䶥�����ݣ�λ�á����ߡ���������
    for (size_t i = 0; i < mesh.vertices.size(); ++i) {
        const glm::vec3& vertex = mesh.vertices[i];
        const glm::vec3& normal = mesh.normals[i];
        const glm::vec2& texCoord = mesh.texCoords[i];

        // ÿ�����������λ�ã�3�������ߣ�3�����������꣨2��������ÿ�������� 8 �� float
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

    // ���㻺�����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // �����������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // ���ö������ԣ�λ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);                // λ��
    glEnableVertexAttribArray(0);

    // ���ö������ԣ�����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // ����
    glEnableVertexAttribArray(1);

    // ���ö������ԣ���������
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // ��������
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);  // ��� VAO
}
