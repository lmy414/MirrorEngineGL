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

        // �ݹ鴦��ģ�͵Ľڵ�
        ProcessNode(scene->mRootNode, scene);
        return true;
    }


    // ��ȡ���ص�����
    const std::vector<Mesh>& GetMeshes() const {
        return meshes;
    }



private:
    // ����ڵ��е�ÿ������
    void ProcessNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(Mesh(mesh)); // ��ģ�͵�������ӵ� meshes ������
        }

        // �ݹ鴦��ÿ���ӽڵ�
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }
};

#endif
