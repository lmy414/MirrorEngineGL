#ifndef MESH_H
#define MESH_H

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;

    // 构造函数，根据Assimp的aiMesh填充数据
    Mesh(const aiMesh* mesh) {
        // 顶点数据
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            vertices.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
            normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
            if (mesh->mTextureCoords[0]) {
                texCoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
            }
            else {
                texCoords.push_back(glm::vec2(0.0f, 0.0f));  // 如果没有纹理坐标，则使用默认值
            }
        }

        // 索引数据
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
    }
};

#endif
