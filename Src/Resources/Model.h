#ifndef MODEL_H
#define MODEL_H

#include "../Render/Mesh.h"  // 引入 Mesh.h 以访问 Mesh::Vertex 类型
#include <assimp/scene.h>
#include <vector>
#include <string>
#include "Texture.h"
#include "TexturePool.h"
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <iostream>  // 引入输出头文件


class Model {
public:
    // 构造函数：接受模型名称和路径
    Model(const std::string& name, const std::string& path)
        : m_name(name), m_path(path), m_id(GenerateID()) {
        LoadModel(path);
    }

    // 加载模型
    void LoadModel(const std::string& path) {
        std::cout << "Loading model from path: " << path << std::endl;  // 输出调试信息
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }
        std::cout << "Model loaded successfully, processing nodes..." << std::endl;  // 输出调试信息
        // 递归处理模型的节点
        ProcessNode(scene->mRootNode, scene);
    }

    // 处理节点
    void ProcessNode(aiNode* node, const aiScene* scene) {
        std::cout << "Processing node: " << node->mName.C_Str() << std::endl;  // 输出调试信息
        // 处理当前节点的所有网格（模型）
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            std::cout << "Processing mesh " << i << " from node " << node->mName.C_Str() << std::endl;  // 输出调试信息
            ProcessMesh(mesh, scene);
        }
        // 递归处理所有子节点
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    // 处理网格数据
    void ProcessMesh(aiMesh* mesh, const aiScene* scene) {
        std::cout << "Processing mesh with " << mesh->mNumVertices << " vertices and " << mesh->mNumFaces << " faces." << std::endl;  // 输出调试信息
        std::vector<Mesh::Vertex> vertices;  // 使用 Mesh::Vertex 类型
        std::vector<unsigned int> indices;
        std::vector<std::shared_ptr<Texture>> textures;

        // 获取顶点数据
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Mesh::Vertex vertex;  // 创建 Mesh::Vertex 对象
            
            // 设置顶点属性
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            if (mesh->mTextureCoords[0]) {
                vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, 1.0f - mesh->mTextureCoords[0][i].y);  // 翻转v轴
            } else {
                vertex.texCoords = glm::vec2(0.0f, 0.0f); // 默认值
            }

            if (mesh->mTangents) {
                vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            }
            if (mesh->mBitangents) {
                vertex.bitangent = glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
            }

            // 默认骨骼数据（没有骨骼数据时）
            for (int j = 0; j < 4; j++) {
                vertex.boneIDs[j] = -1;
                vertex.weights[j] = 0.0f;
            }

            vertices.push_back(vertex);
        }
        

        // 获取索引数据
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        // 获取材质纹理数据
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<std::shared_ptr<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
        std::vector<std::shared_ptr<Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // 保存数据到成员变量
        m_vertices = vertices;
        m_indices = indices;
        m_textures = textures;

        std::cout << "Mesh processed with " << vertices.size() << " vertices and " << indices.size() << " indices." << std::endl;  // 输出调试信息
    }

    // 从材质中加载纹理
    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type) {
        std::cout << "Loading textures of type " << type << std::endl;  // 输出调试信息
        std::vector<std::shared_ptr<Texture>> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            std::string texturePath = str.C_Str();
            std::cout << "Texture path: " << texturePath << std::endl;  // 输出调试信息
            if (texturePath != "") {
                std::string textureName = ExtractFileName(texturePath);
                Texture::TextureType textureType = (type == aiTextureType_DIFFUSE) ? Texture::TextureType::DIFFUSE : Texture::TextureType::SPECULAR;
                Texture::TextureChannelType channelType = Texture::TextureChannelType::RGB;
                textures.push_back(std::make_shared<Texture>(textureName, texturePath, textureType, channelType));
            }
        }
        std::cout << "Loaded " << textures.size() << " textures." << std::endl;  // 输出调试信息
        return textures;
    }

    // 提取文件名
    std::string ExtractFileName(const std::string& path) {
        std::cout << "Extracting file name from path: " << path << std::endl;  // 输出调试信息
        size_t found = path.find_last_of("/\\");
        return path.substr(found + 1);
    }

    // 获取模型名称
    const std::string& GetName() const { return m_name; }

    // 获取模型ID
    GLuint GetID() const { return m_id; }

    // 获取模型的顶点数据
    const std::vector<Mesh::Vertex>& GetVertices() const { return m_vertices; }

    // 获取模型的索引数据
    const std::vector<unsigned int>& GetIndices() const { return m_indices; }

    // 获取模型的纹理数据
    const std::vector<std::shared_ptr<Texture>>& GetTextures() const { return m_textures; }

private:
    std::string m_name;  // 模型名称
    std::string m_path;  // 模型路径
    GLuint m_id;         // 模型ID
    std::vector<Mesh::Vertex> m_vertices;  // 顶点数据
    std::vector<unsigned int> m_indices;  // 索引数据
    std::vector<std::shared_ptr<Texture>> m_textures;  // 纹理数据

    // 自动生成唯一ID
    static GLuint GenerateID() {
        static GLuint idCounter = 0;
        return idCounter++;
    }
};

#endif // MODEL_H
