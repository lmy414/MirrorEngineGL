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
        projectionMatrix(glm::mat4(1.0f)),
        orthographicMatrix(glm::mat4(1.0f)), // ��ʼ������ͶӰ����
        fov(45.0f), // Ĭ���ӳ���
        nearPlane(1.0f), // Ĭ�Ͻ�ƽ��
        farPlane(10.0f), // Ĭ��Զƽ��
        windowWidth(800), // Ĭ�ϴ��ڿ��
        windowHeight(600), // Ĭ�ϴ��ڸ߶�
        isPerspective(true) // Ĭ��Ϊ͸��ͶӰ
    {
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

    // ����͸��ͶӰ���󣨹̶��ӳ��ǣ�
    void SetFixedPerspectiveProjection(float fov, float nearPlane, float farPlane, float aspectRatio) {
        isPerspective = true; // ���Ϊ͸��ͶӰ
        this->fov = fov;
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
        UpdateProjectionMatrix(fov, aspectRatio, nearPlane, farPlane);
    }

    // ��������ͶӰ����
    void SetOrthographicProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        isPerspective = false; // ���Ϊ����ͶӰ
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
        UpdateOrthographicMatrix(left, right, bottom, top, nearPlane, farPlane);
    }

    // ��ȡ͸��ͶӰ����
    glm::mat4 GetProjectionMatrix() const {
        return projectionMatrix;
    }

    // ��ȡ����ͶӰ����
    glm::mat4 GetOrthographicMatrix() const {
        return orthographicMatrix;
    }

    // ����͸��ͶӰ����
    void UpdateProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
        if (isPerspective) {
            projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
        }
    }

    // ��������ͶӰ����
    void UpdateOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        orthographicMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
    }

    // ���ô��ڴ�С�����ڸ���ͶӰ����
    void SetWindowSize(int width, int height) {
        windowWidth = width;
        windowHeight = height;
        float aspectRatio = (float)width / (float)height;

        // ����͸�ӻ�����ͶӰ����
        if (isPerspective) {
            UpdateProjectionMatrix(fov, aspectRatio, nearPlane, farPlane);
        } else {
            // �������Ǽ�������ͶӰ����ı߽���Ҫ�ṩ
            float left = -aspectRatio * 10.0f;
            float right = aspectRatio * 10.0f;
            float bottom = -10.0f;
            float top = 10.0f;
            UpdateOrthographicMatrix(left, right, bottom, top, nearPlane, farPlane);
        }
    }

private:
    glm::mat4 modelMatrix;      // ģ�;���
    glm::mat4 viewMatrix;       // ��ͼ����
    glm::mat4 projectionMatrix; // ͸��ͶӰ����
    glm::mat4 orthographicMatrix; // ����ͶӰ����

    float fov;                  // �ӳ���
    float nearPlane;            // ��ƽ��
    float farPlane;             // Զƽ��

    int windowWidth;            // ��ǰ���ڿ��
    int windowHeight;           // ��ǰ���ڸ߶�

    bool isPerspective;         // ��ǵ�ǰ�Ƿ�Ϊ͸��ͶӰ
};

#endif // MATRIX_MANAGER_H
