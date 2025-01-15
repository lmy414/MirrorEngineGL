#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Material {
public:
    // 材质属性
    glm::vec3 diffuse;   // 漫反射颜色
    // 构造函数，初始化材质参数
    Material(
        const glm::vec3& diffuse = glm::vec3(0.8f, 0.8f, 0.8f))
        :  diffuse(diffuse) {
    }

    // 设置材质的 uniform 参数
    void SetMaterialUniforms(Shader& shader) {
        // 设置漫反射颜色
        shader.setVec3("diffuse", diffuse);
        // 设置高光反射颜色
    }
};

#endif // MATERIAL_H
#pragma once
