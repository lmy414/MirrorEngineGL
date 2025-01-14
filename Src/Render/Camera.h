#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Tool/MatrixManager.h"  // 引入 MatrixManager

namespace Core {

    // 定义摄像机移动方向枚举
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,    // 向上
        DOWN   // 向下
    };

    class Camera {
    public:
        // 摄像机属性
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        // 欧拉角
        float Yaw;
        float Pitch;

        // 设置选项
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        // 矩阵管理器
        MatrixManager matrixManager;

    private:
        bool viewMatrixDirty = true;  // 用于标记视图矩阵是否需要更新

    public:
        // 构造函数：用向量初始化
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = -90.0f, float pitch = 0.0f)
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
            MovementSpeed(2.5f),
            MouseSensitivity(0.1f),
            Zoom(45.0f)
        {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        // 设置相机位置
        void SetPosition(const glm::vec3& position) {
            Position = position;
            updateCameraVectors();
            viewMatrixDirty = true;  // 标记视图矩阵需要更新
        }

        // 设置相机的前向向量
        void SetFront(const glm::vec3& front) {
            Front = front;
            updateCameraVectors();
            viewMatrixDirty = true;  // 标记视图矩阵需要更新
        }

        // 获取视图矩阵（只有在需要时才更新）
        glm::mat4 GetViewMatrix() {
            updateViewMatrixIfNeeded(); // 只有在需要时才更新
            return matrixManager.GetViewMatrix();
        }

        // 键盘输入处理
        void ProcessKeyboard(CameraMovement direction, float deltaTime) {
            float velocity = MovementSpeed * deltaTime;
            switch (direction) {
            case CameraMovement::FORWARD:
                Position += Front * velocity;
                break;
            case CameraMovement::BACKWARD:
                Position -= Front * velocity;
                break;
            case CameraMovement::LEFT:
                Position -= Right * velocity;
                break;
            case CameraMovement::RIGHT:
                Position += Right * velocity;
                break;
            case CameraMovement::UP:
                Position += Up * velocity;   // 向上移动
                break;
            case CameraMovement::DOWN:
                Position -= Up * velocity;   // 向下移动
                break;
            }
            viewMatrixDirty = true;  // 标记视图矩阵需要更新
        }

        // 鼠标输入处理
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;

            Yaw += xoffset;
            Pitch += yoffset;

            if (constrainPitch) {
                Pitch = glm::clamp(Pitch, -89.0f, 89.0f);
            }

            updateCameraVectors();
            viewMatrixDirty = true;  // 标记视图矩阵需要更新
        }

        // 鼠标滚轮缩放
        void ProcessMouseScroll(float yoffset) {
            Zoom -= yoffset;
            Zoom = glm::clamp(Zoom, 1.0f, 90.0f);
        }

        // 重置相机到初始位置和朝向
        void ResetCamera() {
            Position = glm::vec3(0.0f, 0.0f, 3.0f);  // 初始位置
            Front = glm::vec3(0.0f, 0.0f, -1.0f);    // 初始前向
            Yaw = -90.0f;                            // 初始偏航角
            Pitch = 0.0f;                            // 初始俯仰角
            updateCameraVectors();
            viewMatrixDirty = true;  // 标记视图矩阵需要更新
        }

    private:
        // 更新摄像机方向向量
        void updateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);

            Right = glm::normalize(glm::cross(Front, WorldUp));
            Up = glm::normalize(glm::cross(Right, Front));
        }

        // 更新视图矩阵时检查是否有变化
        void updateViewMatrixIfNeeded() {
            if (viewMatrixDirty) {
                matrixManager.SetViewMatrix(Position, Position + Front, Up);
                viewMatrixDirty = false;
            }
        }
    };

} // namespace Core

#endif // CAMERA_H
