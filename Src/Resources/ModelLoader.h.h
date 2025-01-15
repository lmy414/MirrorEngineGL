#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <iostream>

class ModelLoader {
public:
    // 存储所有加载的模型的网格
    std::vector<std::vector<Mesh>> allMeshes;  // 每个模型的 Meshs 列表

    // 加载多个路径的模型
    bool LoadModels(const std::vector<std::string>& paths) {
        for (const auto& path : paths) {
            std::vector<Mesh> modelMeshes;
            if (!LoadModel(path, modelMeshes)) {
                return false;  // 如果加载某个模型失败，则返回 false
            }
            allMeshes.push_back(modelMeshes);  // 将每个加载的模型添加到容器中
        }
        return true;
    }

    // 获取所有加载的网格
    const std::vector<std::vector<Mesh>>& GetAllMeshes() const {
        return allMeshes;
    }

private:
    // 加载单个模型，并将其网格存储到 modelMeshes 中
    bool LoadModel(const std::string& path, std::vector<Mesh>& modelMeshes) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return false;
        }

        return true;
    }


    // 获取加载的网格
    const std::vector<Mesh>& GetMeshes() const {
        return meshes;
    }



private:
    // 处理节点中的每个网格
    void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& modelMeshes) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            modelMeshes.push_back(Mesh(mesh));  // 将当前网格添加到 modelMeshes 向量中
        }

        // 递归处理每个子节点
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene, modelMeshes);
        }
    }
};

#endif
