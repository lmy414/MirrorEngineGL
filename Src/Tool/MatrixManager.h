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
        fov(45.0f), // Ĭ���ӳ���
        nearPlane(0.1f), // Ĭ�Ͻ�ƽ��
        farPlane(100.0f), // Ĭ��Զƽ��
        windowWidth(800), // Ĭ�ϴ��ڿ��
        windowHeight(600) // Ĭ�ϴ��ڸ߶�
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
    void SetFixedPerspectiveProjection(float fov, float nearPlane, float farPlane) {
        this->fov = fov;
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
        UpdateProjectionMatrix();
    }

    // ��ȡͶӰ����
    glm::mat4 GetProjectionMatrix() const {
        return projectionMatrix;
    }

    // ����ͶӰ���󣬻��ڵ�ǰ���ڴ�С
    void UpdateProjectionMatrix() {
        // ���㵱ǰ�Ŀ�߱ȣ�aspect ratio��
        float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

    // ���ô��ڴ�С�����ڸ���ͶӰ����
    void SetWindowSize(int width, int height) {
        windowWidth = width;
        windowHeight = height;
        UpdateProjectionMatrix(); // ÿ�δ��ڴ�С�仯ʱ������ͶӰ����
    }

private:
    glm::mat4 modelMatrix;      // ģ�;���
    glm::mat4 viewMatrix;       // ��ͼ����
    glm::mat4 projectionMatrix; // ͶӰ����

    float fov;                  // �ӳ���
    float nearPlane;            // ��ƽ��
    float farPlane;             // Զƽ��

    int windowWidth;            // ��ǰ���ڿ��
    int windowHeight;           // ��ǰ���ڸ߶�
};

#endif // MATRIX_MANAGER_H
