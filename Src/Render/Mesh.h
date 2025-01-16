#ifndef MESH_H
#define MESH_H

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <glad/glad.h>
//#include "Tool/math.h"  
#include "Shader.h"

// 用于表示网格中的一个顶点
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int boneIDs[4]; // 骨骼ID
    float weights[4]; // 权重
};

class Mesh {
public:
    std::vector<Vertex> vertices;  // 顶点数据
    std::vector<unsigned int> indices;  // 索引数据
    unsigned int VAO, VBO, EBO;

    // 构造函数：从 Assimp 的 aiMesh 填充 Mesh 数据
    Mesh(const aiMesh* mesh) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            // 顶点位置
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            // 顶点法线
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            // 顶点纹理坐标
            if (mesh->mTextureCoords[0]) {
                // 检查纹理坐标是否有效，确保在 [0, 1] 范围内
                float u = mesh->mTextureCoords[0][i].x;
                float v = mesh->mTextureCoords[0][i].y;

                //std::cout << "Vertex " << i << ": UV (" << u << ", " << v << ")\n";

                // 如果超出了有效范围 [0, 1]，可以设置为默认值或进行修正
                //u = math::clamp(u, 0.0f, 1.0f);
                //v = math::clamp(v, 0.0f, 1.0f);

                vertex.texCoords = glm::vec2(u,  1.0f - v);//blender创建的uv和opengl的uv坐标系不同，需要翻转v轴
            } else {
                // 如果没有纹理坐标，则提供一个默认值 (如 0, 0)
                vertex.texCoords = glm::vec2(0.0f, 0.0f);
            }
            // 切线与副切线
            if (mesh->mTangents) {
                vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            }
            if (mesh->mBitangents) {
                vertex.bitangent = glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
            }
            // 骨骼数据 (假设最多4个骨骼影响一个顶点)
            for (int j = 0; j < 4; j++) {
                vertex.boneIDs[j] = -1;
                vertex.weights[j] = 0.0f;
            }
            vertices.push_back(vertex);
        }

        // 索引数据
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        setupMesh();
    }

    // 渲染网格
    void Render( Shader& shader, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
        shader.use();
        // 传递变换矩阵到着色器
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        // 绑定 VAO
        glBindVertexArray(VAO);
        // 绘制网格
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        // 解绑 VAO
        glBindVertexArray(0);
    }

    // 更新网格数据（如骨骼权重更新等）
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
    // 设置OpenGL缓冲区
    void setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // 设置顶点属性指针
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