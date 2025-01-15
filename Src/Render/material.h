#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Material {
public:
    glm::vec3 diffuse;  // 漫反射颜色
    unsigned int diffuseTexture;  // 漫反射纹理

    // 构造函数，初始化材质参数
    Material(const glm::vec3& diffuse = glm::vec3(0.8f, 0.8f, 0.8f), unsigned int diffuseTexture = 0)
        : diffuse(diffuse), diffuseTexture(diffuseTexture) {}

    // 设置材质的 uniform 参数
    void SetMaterialUniforms(Shader& shader) {
        // 设置漫反射颜色
        shader.setVec3("diffuse", diffuse);

        // 绑定漫反射纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture);
        shader.setInt("diffuseTexture", 0);
    }
};

#endif // MATERIAL_H
