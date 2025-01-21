#ifndef MESH_H
#define MESH_H

#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include "../Resources/Texture.h"    // 引入纹理管理类

class Mesh {
   
public:
    // 顶点结构体
    struct Vertex {
        glm::vec3 position;    // 顶点位置
        glm::vec3 normal;      // 法线
        glm::vec2 texCoords;   // 纹理坐标
        glm::vec3 tangent;     // 切线
        glm::vec3 bitangent;   // 位切线
        int boneIDs[4];        // 骨骼ID
        float weights[4];      // 骨骼权重
    };

    // 构造函数：自动加载模型并设置为网格
    Mesh();

    // 渲染方法：渲染所有网格
    void Render(Shader& shader, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;

    // 渲染单个网格（初始化一次后，直接使用VAO进行渲染）
    void RenderMesh() const;

private:
    GLuint m_vao, m_vbo, m_ebo;  // VAO: 顶点数组对象，VBO: 顶点缓冲对象，EBO: 索引缓冲对象
    std::vector<Vertex> m_vertices; // 顶点数据
    std::vector<unsigned int> m_indices; // 索引数据
    std::vector<std::shared_ptr<Texture>> m_textures; // 纹理数据

    // 设置 OpenGL 缓冲区（初始化一次）
    void setupMesh();

    // 加载所有模型的网格
    void LoadAllMeshes();
};

#endif // MESH_H
