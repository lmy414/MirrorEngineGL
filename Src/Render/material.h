#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Material {
public:
    // 材质属性
    glm::vec3 ambient;   // 环境光颜色
    glm::vec3 diffuse;   // 漫反射颜色
    glm::vec3 specular;  // 高光反射颜色
    float shininess;     // 光泽度

    // 构造函数，初始化材质参数
    Material(const glm::vec3& ambient = glm::vec3(0.2f, 0.2f, 0.2f),
        const glm::vec3& diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
        const glm::vec3& specular = glm::vec3(1.0f, 1.0f, 1.0f),
        float shininess = 32.0f)
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {
    }

    // 设置材质的 uniform 参数
    void SetMaterialUniforms(Shader& shader) {
        // 设置环境光颜色
        shader.setUniform("material.ambient", ambient);
        // 设置漫反射颜色
        shader.setUniform("material.diffuse", diffuse);
        // 设置高光反射颜色
        shader.setUniform("material.specular", specular);
        // 设置光泽度
        shader.setUniform("material.shininess", shininess);
    }
};

#endif // MATERIAL_H
#pragma once
