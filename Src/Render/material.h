#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Material {
public:
    // ��������
    glm::vec3 ambient;   // ��������ɫ
    glm::vec3 diffuse;   // ��������ɫ
    glm::vec3 specular;  // �߹ⷴ����ɫ
    float shininess;     // �����

    // ���캯������ʼ�����ʲ���
    Material(const glm::vec3& ambient = glm::vec3(0.2f, 0.2f, 0.2f),
        const glm::vec3& diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
        const glm::vec3& specular = glm::vec3(1.0f, 1.0f, 1.0f),
        float shininess = 32.0f)
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {
    }

    // ���ò��ʵ� uniform ����
    void SetMaterialUniforms(Shader& shader) {
        // ���û�������ɫ
        shader.setUniform("material.ambient", ambient);
        // ������������ɫ
        shader.setUniform("material.diffuse", diffuse);
        // ���ø߹ⷴ����ɫ
        shader.setUniform("material.specular", specular);
        // ���ù����
        shader.setUniform("material.shininess", shininess);
    }
};

#endif // MATERIAL_H
#pragma once
