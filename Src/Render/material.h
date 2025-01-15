#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Material {
public:
    // ��������
    glm::vec3 diffuse;   // ��������ɫ
    // ���캯������ʼ�����ʲ���
    Material(
        const glm::vec3& diffuse = glm::vec3(0.8f, 0.8f, 0.8f))
        :  diffuse(diffuse) {
    }

    // ���ò��ʵ� uniform ����
    void SetMaterialUniforms(Shader& shader) {
        // ������������ɫ
        shader.setVec3("diffuse", diffuse);
        // ���ø߹ⷴ����ɫ
    }
};

#endif // MATERIAL_H
#pragma once
