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
    // �洢���м��ص�ģ�͵�����
    std::vector<std::vector<Mesh>> allMeshes;  // ÿ��ģ�͵� Meshs �б�

    // ���ض��·����ģ��
    bool LoadModels(const std::vector<std::string>& paths) {
        for (const auto& path : paths) {
            std::vector<Mesh> modelMeshes;
            if (!LoadModel(path, modelMeshes)) {
                return false;  // �������ĳ��ģ��ʧ�ܣ��򷵻� false
            }
            allMeshes.push_back(modelMeshes);  // ��ÿ�����ص�ģ����ӵ�������
        }
        return true;
    }

    // ��ȡ���м��ص�����
    const std::vector<std::vector<Mesh>>& GetAllMeshes() const {
        return allMeshes;
    }

private:
    // ���ص���ģ�ͣ�����������洢�� modelMeshes ��
    bool LoadModel(const std::string& path, std::vector<Mesh>& modelMeshes) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return false;
        }

        return true;
    }


    // ��ȡ���ص�����
    const std::vector<Mesh>& GetMeshes() const {
        return meshes;
    }



private:
    // ����ڵ��е�ÿ������
    void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& modelMeshes) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            modelMeshes.push_back(Mesh(mesh));  // ����ǰ������ӵ� modelMeshes ������
        }

        // �ݹ鴦��ÿ���ӽڵ�
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene, modelMeshes);
        }
    }
};

#endif
