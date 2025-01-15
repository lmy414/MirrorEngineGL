#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Material {
public:
    glm::vec3 diffuse;  // ��������ɫ
    unsigned int diffuseTexture;  // ����������

    // ���캯������ʼ�����ʲ���
    Material(const glm::vec3& diffuse = glm::vec3(0.8f, 0.8f, 0.8f), unsigned int diffuseTexture = 0)
        : diffuse(diffuse), diffuseTexture(diffuseTexture) {}

    // ���ò��ʵ� uniform ����
    void SetMaterialUniforms(Shader& shader) {
        // ������������ɫ
        shader.setVec3("diffuse", diffuse);

        // ������������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture);
        shader.setInt("diffuseTexture", 0);
    }
};

#endif // MATERIAL_H
