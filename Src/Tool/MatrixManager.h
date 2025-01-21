#ifndef MATRIX_MANAGER_H
#define MATRIX_MANAGER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MatrixManager {
public:
    // 构造函数
    MatrixManager()
        : modelMatrix(glm::mat4(1.0f)),
        viewMatrix(glm::mat4(1.0f)),
        projectionMatrix(glm::mat4(1.0f)),
        orthographicMatrix(glm::mat4(1.0f)), // 初始化正交投影矩阵
        fov(45.0f), // 默认视场角
        nearPlane(1.0f), // 默认近平面
        farPlane(10.0f), // 默认远平面
        windowWidth(800), // 默认窗口宽度
        windowHeight(600), // 默认窗口高度
        isPerspective(true) // 默认为透视投影
    {
    }

    // 设置模型矩阵
    void SetModelMatrix(const glm::mat4& matrix) {
        modelMatrix = matrix;
    }

    glm::mat4 GetModelMatrix() const {
        return modelMatrix;
    }

    // 设置视图矩阵
    void SetViewMatrix(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {
        viewMatrix = glm::lookAt(position, target, up);
    }

    glm::mat4 GetViewMatrix() const {
        return viewMatrix;
    }

    // 设置透视投影矩阵（固定视场角）
    void SetFixedPerspectiveProjection(float fov, float nearPlane, float farPlane, float aspectRatio) {
        isPerspective = true; // 标记为透视投影
        this->fov = fov;
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
        UpdateProjectionMatrix(fov, aspectRatio, nearPlane, farPlane);
    }

    // 设置正交投影矩阵
    void SetOrthographicProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        isPerspective = false; // 标记为正交投影
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
        UpdateOrthographicMatrix(left, right, bottom, top, nearPlane, farPlane);
    }

    // 获取透视投影矩阵
    glm::mat4 GetProjectionMatrix() const {
        return projectionMatrix;
    }

    // 获取正交投影矩阵
    glm::mat4 GetOrthographicMatrix() const {
        return orthographicMatrix;
    }

    // 更新透视投影矩阵
    void UpdateProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
        if (isPerspective) {
            projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
        }
    }

    // 更新正交投影矩阵
    void UpdateOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        orthographicMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
    }

    // 设置窗口大小（用于更新投影矩阵）
    void SetWindowSize(int width, int height) {
        windowWidth = width;
        windowHeight = height;
        float aspectRatio = (float)width / (float)height;

        // 更新透视或正交投影矩阵
        if (isPerspective) {
            UpdateProjectionMatrix(fov, aspectRatio, nearPlane, farPlane);
        } else {
            // 这里我们假设正交投影矩阵的边界需要提供
            float left = -aspectRatio * 10.0f;
            float right = aspectRatio * 10.0f;
            float bottom = -10.0f;
            float top = 10.0f;
            UpdateOrthographicMatrix(left, right, bottom, top, nearPlane, farPlane);
        }
    }

private:
    glm::mat4 modelMatrix;      // 模型矩阵
    glm::mat4 viewMatrix;       // 视图矩阵
    glm::mat4 projectionMatrix; // 透视投影矩阵
    glm::mat4 orthographicMatrix; // 正交投影矩阵

    float fov;                  // 视场角
    float nearPlane;            // 近平面
    float farPlane;             // 远平面

    int windowWidth;            // 当前窗口宽度
    int windowHeight;           // 当前窗口高度

    bool isPerspective;         // 标记当前是否为透视投影
};

#endif // MATRIX_MANAGER_H
