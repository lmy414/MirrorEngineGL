#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

class ModelLoader {
public:
    std::vector<Mesh> meshes;

    bool LoadModel(const std::string& path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return false;
        }

        // 递归处理模型的节点
        ProcessNode(scene->mRootNode, scene);
        return true;
    }


    // 获取加载的网格
    const std::vector<Mesh>& GetMeshes() const {
        return meshes;
    }



private:
    // 处理节点中的每个网格
    void ProcessNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(Mesh(mesh)); // 将模型的网格添加到 meshes 向量中
        }

        // 递归处理每个子节点
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }
};

#endif
