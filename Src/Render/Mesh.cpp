#include "Mesh.h"
#include "../Resources/ModelPool.h"  // 引入模型池
#include <iostream>  // 用于打印调试信息

// 构造函数：自动加载模型并设置为网格
Mesh::Mesh() {
    std::cout << "Mesh constructor called, loading all meshes..." << std::endl;  // 调试信息
    LoadAllMeshes();  // 加载所有模型并初始化网格
}


void Mesh::RenderMesh() const {
    // 绑定 VAO
    glBindVertexArray(m_vao);

    // 绘制网格
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);

    // 解绑 VAO
    glBindVertexArray(0);
    
}

// 渲染方法：渲染所有网格
void Mesh::Render(Shader& shader, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
    std::cout << "Rendering mesh..." << std::endl;  // 调试信息
    
    // 使用着色器
    shader.use();
    
    // 传递变换矩阵到着色器
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    RenderMesh();
}

// 设置 OpenGL 缓冲区（初始化一次）
void Mesh::setupMesh() {
    std::cout << "Setting up mesh..." << std::endl;  // 调试信息

    // 生成并绑定 VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // 生成并绑定 VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    // 生成并绑定 EBO
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, bitangent));
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(5, 4, GL_INT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, boneIDs));
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, weights));
    glEnableVertexAttribArray(6);

    // 解绑定 VAO 和 VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// 加载所有模型的网格
void Mesh::LoadAllMeshes() {
    std::cout << "Loading all meshes from model pool..." << std::endl;

    // 获取模型池中的所有模型
    auto& models = ModelPool::Instance().GetModels();

    // 检查模型池是否为空
    if (models.empty()) {
        std::cout << "Error: No models found in the pool!" << std::endl;
        return;
    }

    // 遍历模型池中的所有模型
    for (const auto& pair : models) {
        auto model = pair.second;
        if (!model) {
            std::cout << "Error: Found a null model in the pool!" << std::endl;
            continue;
        }

        // 获取模型的顶点、索引和纹理数据
        m_vertices = model->GetVertices();
        m_indices = model->GetIndices();
        m_textures = model->GetTextures();

        std::cout << "Loaded model " << pair.first << " with " << m_vertices.size() << " vertices and " << m_indices.size() << " indices." << std::endl;

        // 打印前10个顶点信息
        static bool printed = false;
        if (!printed) {
            for (int i = 0; i < std::min(10, static_cast<int>(m_vertices.size())); ++i) {
                const auto& vertex = m_vertices[i];
                std::cout << "Vertex " << i << ": Position (" 
                          << vertex.position.x << ", "
                          << vertex.position.y << ", "
                          << vertex.position.z << ")\n";
            }
            printed = true; // 只打印一次
        }

        // 初始化 OpenGL 缓冲区
        setupMesh();
    }
}


