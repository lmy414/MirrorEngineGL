#ifndef MATRIX_MANAGER_H
#define MATRIX_MANAGER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MatrixManager {
public:
    // ���캯��
    MatrixManager()
        : modelMatrix(glm::mat4(1.0f)),
        viewMatrix(glm::mat4(1.0f)),
        projectionMatrix(glm::mat4(1.0f)) {
    }

    // ����ģ�;���
    void SetModelMatrix(const glm::mat4& matrix) {
        modelMatrix = matrix;
    }

    glm::mat4 GetModelMatrix() const {
        return modelMatrix;
    }

    // ������ͼ����
    void SetViewMatrix(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {
        viewMatrix = glm::lookAt(position, target, up);
    }

    glm::mat4 GetViewMatrix() const {
        return viewMatrix;
    }

    // ����ͶӰ����͸��ͶӰ��
    void SetPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

    // ����ͶӰ��������ͶӰ��
    void SetOrthographicProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
    }

    glm::mat4 GetProjectionMatrix() const {
        return projectionMatrix;
    }

private:
    glm::mat4 modelMatrix;      // ģ�;���
    glm::mat4 viewMatrix;       // ��ͼ����
    glm::mat4 projectionMatrix; // ͶӰ����
};

#endif // MATRIX_MANAGER_H
