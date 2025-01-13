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
        fov(45.0f), // 默认视场角
        nearPlane(0.1f), // 默认近平面
        farPlane(100.0f), // 默认远平面
        windowWidth(800), // 默认窗口宽度
        windowHeight(600) // 默认窗口高度
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
    void SetFixedPerspectiveProjection(float fov, float nearPlane, float farPlane) {
        this->fov = fov;
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
        UpdateProjectionMatrix();
    }

    // 获取投影矩阵
    glm::mat4 GetProjectionMatrix() const {
        return projectionMatrix;
    }

    // 更新投影矩阵，基于当前窗口大小
    void UpdateProjectionMatrix() {
        // 计算当前的宽高比（aspect ratio）
        float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

    // 设置窗口大小（用于更新投影矩阵）
    void SetWindowSize(int width, int height) {
        windowWidth = width;
        windowHeight = height;
        UpdateProjectionMatrix(); // 每次窗口大小变化时，更新投影矩阵
    }

private:
    glm::mat4 modelMatrix;      // 模型矩阵
    glm::mat4 viewMatrix;       // 视图矩阵
    glm::mat4 projectionMatrix; // 投影矩阵

    float fov;                  // 视场角
    float nearPlane;            // 近平面
    float farPlane;             // 远平面

    int windowWidth;            // 当前窗口宽度
    int windowHeight;           // 当前窗口高度
};

#endif // MATRIX_MANAGER_H
