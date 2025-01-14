#ifndef MESH_H
#define MESH_H

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <glad/glad.h>
#include "shader.h" // ��������һ�� Shader ��
#include <glm/gtc/type_ptr.hpp>


// ���ڱ�ʾ�����е�һ������
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int boneIDs[4]; // ����ID
    float weights[4]; // Ȩ��
};

class Mesh {
public:
    std::vector<Vertex> vertices;  // ��������
    std::vector<unsigned int> indices;  // ��������
    unsigned int VAO, VBO, EBO;

    // ���캯������ Assimp �� aiMesh ��� Mesh ����
    Mesh(const aiMesh* mesh) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            // ����λ��
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            // ���㷨��
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            // ������������
            if (mesh->mTextureCoords[0]) {
                vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            else {
                vertex.texCoords = glm::vec2(0.0f, 0.0f); // Ĭ��ֵ
            }
            // �����븱����
            if (mesh->mTangents) {
                vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            }
            if (mesh->mBitangents) {
                vertex.bitangent = glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
            }
            // �������� (�������4������Ӱ��һ������)
            for (int j = 0; j < 4; j++) {
                vertex.boneIDs[j] = -1;
                vertex.weights[j] = 0.0f;
            }
            vertices.push_back(vertex);
        }

        // ��������
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        setupMesh();
    }

    // ��Ⱦ����
    void Render(Shader& shader, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
        shader.use();
        // ���ݱ任������ɫ��
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // �� VAO
        glBindVertexArray(VAO);
        // ��������
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        // ��� VAO
        glBindVertexArray(0);
    }

    // �����������ݣ������Ȩ�ظ��µȣ�
    void UpdateMeshData(const std::vector<Vertex>& newVertices, const std::vector<unsigned int>& newIndices) {
        vertices = newVertices;
        indices = newIndices;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
    }

private:
    // ����OpenGL������
    void setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // ���ö�������ָ��
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs));

        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));

        glBindVertexArray(0);
    }
};

#endif
