#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

// 静态变量初始化
std::map<std::string, Model*> Model::LoadedModel;

Model::Model(std::string const& path, bool gamma)
    : gammaCorrection(gamma), mesh_path(path) {
    // 获取模型文件的目录路径
    directory = path.substr(0, path.find_last_of('/'));
    
    std::cout << "Model constructor: Loading model from path: " << path << std::endl;
    
    // 加载模型数据
    loadModel();
}

Model::~Model() {
    std::cout << "Model destructor: Cleaning up model resources" << std::endl;

    // 释放加载的纹理
    for (auto& texture : textures_loaded) {
        delete texture;
    }
    // 释放网格对象
    for (auto& mesh : meshes) {
        delete mesh;
    }
}

// 加载模型文件
void Model::loadModel() {
    // 如果模型已加载过，直接引用已加载的模型
    if (LoadedModel.find(mesh_path) != LoadedModel.end()) {
        std::cout << "Model already loaded, reusing cached model for path: " << mesh_path << std::endl;
        *this = *(LoadedModel[mesh_path]);
        return;
    }

    std::cout << "Loading model from disk: " << mesh_path << std::endl;

    // 使用 Assimp 加载模型
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(mesh_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    std::cout << "Model loaded successfully, processing nodes..." << std::endl;

    // 递归处理模型的根节点
    processNode(scene->mRootNode, scene);

    // 将模型存入静态映射
    LoadedModel[mesh_path] = this;
    std::cout << "Model processed and cached: " << mesh_path << std::endl;
}

// 递归处理每个节点
void Model::processNode(aiNode* node, const aiScene* scene) {
    std::cout << "Processing node: " << node->mName.C_Str() << std::endl;

    // 遍历当前节点的所有网格
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        std::cout << "Processing mesh " << i << " in node: " << node->mName.C_Str() << std::endl;
        meshes.push_back(processMesh(mesh, scene)); // 处理并存储网格
    }

    // 递归处理子节点
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

// 处理单个网格并提取必要信息
Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::cout << "Processing mesh with " << mesh->mNumVertices << " vertices and " << mesh->mNumFaces << " faces." << std::endl;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D*> textures;

    // 处理顶点数据
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
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

    // 处理索引数据
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // 加载材质纹理
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::cout << "Loading textures for material index " << mesh->mMaterialIndex << std::endl;
        std::vector<Texture2D*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    // 返回网格对象
    return new Mesh(vertices, indices, textures);
}

// 加载材质中的纹理
std::vector<Texture2D*> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type) {
    std::vector<Texture2D*> textures;

    std::cout << "Loading textures of type: " << type << std::endl;

    // 遍历材质中的纹理
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        // 检查纹理是否已加载
        for (auto& loadedTexture : textures_loaded) {
            if (loadedTexture->getPath() == str.C_Str()) {
                textures.push_back(loadedTexture);
                skip = true;
                break;
            }
        }

        // 如果纹理没有加载过，则加载
        if (!skip) {
            Texture2D* texture = new Texture2D(std::string (str.C_Str()));
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}
