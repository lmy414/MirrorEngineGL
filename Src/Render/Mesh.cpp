#include "Mesh.h"
#include "../Tool/ToString.h"
#include <iostream>

// 构造函数：接受顶点、索引和纹理数据
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture2D*>& textures)
    : vertices(vertices), indices(indices), textures(textures) {
    std::cout << "Creating Mesh..." << std::endl;
    setupMesh();
    //bindTexturesToMaterial();
    std::cout << "Mesh Created!" << std::endl;
}

// 渲染网格
void Mesh::Render(Shader& shader, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
    //std::cout << "Rendering Mesh..." << std::endl;

    shader.use();
    //std::cout << "Shader used" << std::endl;

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

// 设置OpenGL缓冲区
void Mesh::setupMesh() {
    std::cout << "Generating OpenGL buffers..." << std::endl;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    std::cout << "Generated VAO: " << VAO << ", VBO: " << VBO << ", EBO: " << EBO << std::endl;

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    std::cout << "Vertex buffer data uploaded" << std::endl;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    std::cout << "Index buffer data uploaded" << std::endl;

    // 设置顶点属性指针
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    std::cout << "Position attribute set" << std::endl;

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    std::cout << "Normal attribute set" << std::endl;

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    std::cout << "Texture coordinates attribute set" << std::endl;

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    std::cout << "Tangent attribute set" << std::endl;

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    std::cout << "Bitangent attribute set" << std::endl;

    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs));
    std::cout << "Bone IDs attribute set" << std::endl;

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));
    std::cout << "Bone weights attribute set" << std::endl;

    glBindVertexArray(0);
    std::cout << "VAO unbound" << std::endl;
}

// 绑定纹理到材质
/*void Mesh::bindTexturesToMaterial() {
    std::cout << "Binding textures to material..." << std::endl;

    if (!material) {
        material = new SimpleMaterial(0, "default", nullptr, 0, 0, 0.0f, 0.0f); // 默认简单材质
        std::cout << "Created default material" << std::endl;
    }

    // 将所有纹理绑定到材质
    for (size_t i = 0; i < textures.size(); ++i) {
        // 每个纹理的类型分别是diffuseTexture、normalTexture等，你可以根据纹理的顺序指定
        std::string textureName = (i == 0) ? "diffuseTexture" : "normalTexture";  // 这里只是一个示例
        material->SetTexture(textureName, textures[i]->GetID());
        std::cout << "Texture bound - Type: " << textureName << ", TextureID: " << textures[i]->GetID() << std::endl;
    }

    std::cout << "Textures bound to material" << std::endl;
}
*/