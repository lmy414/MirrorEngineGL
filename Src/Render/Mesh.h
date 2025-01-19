#ifndef MESH_H
#define MESH_H

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <glad/glad.h>
#include "Shader.h"
#include "../Resources/Texture.h"
#include "Material/Material.h"

// 用于表示网格中的一个顶点
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int boneIDs[4];  // 骨骼ID
    float weights[4];  // 权重
};

class Mesh {
public:
    std::vector<Vertex> vertices;  // 顶点数据
    std::vector<unsigned int> indices;  // 索引数据
    std::vector<Texture2D*> textures; // 纹理数据
    unsigned int VAO, VBO, EBO;
    Material* material = nullptr; // 材质

    // 构造函数：接受顶点、索引和纹理数据
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture2D*>& textures);

    // 渲染网格
    void Render(Shader& shader, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;

private:
    // 设置OpenGL缓冲区
    void setupMesh();

    // 绑定纹理到材质
    //void bindTexturesToMaterial();
};

#endif
