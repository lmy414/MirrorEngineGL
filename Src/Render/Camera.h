#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Tool/MatrixManager.h"  // 引入 MatrixManager 进行矩阵处理

namespace Core {

    // 相机的移动方向枚举
    enum class CameraMovement {
        FORWARD,  // 向前移动
        BACKWARD, // 向后移动
        LEFT,     // 向左移动
        RIGHT,    // 向右移动
        UP,       // 向上移动
        DOWN      // 向下移动
    };

    class Camera {
    public:
        // 相机的属性
        glm::vec3 Position;  // 相机位置
        glm::vec3 Front;     // 相机的朝向
        glm::vec3 Up;        // 相机的上向量
        glm::vec3 Right;     // 相机的右向量
        glm::vec3 WorldUp;   // 世界的上向量，用于计算相机的方向

        // 相机的欧拉角（控制朝向）
        float Yaw;   // 水平旋转角度
        float Pitch; // 垂直旋转角度

        // 相机运动参数
        float MovementSpeed;     // 运动速度
        float MouseSensitivity;  // 鼠标灵敏度
        float Zoom;              // 缩放级别（视野范围）

        // 矩阵管理器，负责设置视图矩阵
        MatrixManager matrixManager;

    private:
        bool viewMatrixDirty = true;  // 视图矩阵是否需要更新

    public:
        // 构造函数，初始化相机的默认值
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = -90.0f, float pitch = 0.0f)
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
              MovementSpeed(2.5f), MouseSensitivity(0.1f), Zoom(45.0f)
        {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();  // 更新相机朝向向量
        }

        // 设置相机位置并更新相机向量
        void SetPosition(const glm::vec3& position) {
            Position = position;
            updateCameraVectors();
            viewMatrixDirty = true;  // 标记需要更新视图矩阵
        }

        // 设置相机朝向并更新相机向量
        void SetFront(const glm::vec3& front) {
            Front = front;
            updateCameraVectors();
            viewMatrixDirty = true;  // 标记需要更新视图矩阵
        }

        // 获取视图矩阵，确保它是最新的
        glm::mat4 GetViewMatrix() {
            updateViewMatrixIfNeeded(); // 检查视图矩阵是否需要更新
            return matrixManager.GetViewMatrix();
        }

        // 处理相机的键盘输入
        void ProcessKeyboard(CameraMovement direction, float deltaTime) {
            float velocity = MovementSpeed * deltaTime;  // 计算移动速度
            switch (direction) {
            case CameraMovement::FORWARD:
                Position += Front * velocity;  // 向前移动
                break;
            case CameraMovement::BACKWARD:
                Position -= Front * velocity; // 向后移动
                break;
            case CameraMovement::LEFT:
                Position -= Right * velocity; // 向左移动
                break;
            case CameraMovement::RIGHT:
                Position += Right * velocity; // 向右移动
                break;
            case CameraMovement::UP:
                Position += Up * velocity;    // 向上移动
                break;
            case CameraMovement::DOWN:
                Position -= Up * velocity;    // 向下移动
                break;
            }
            viewMatrixDirty = true;  // 标记需要更新视图矩阵
        }

        // 处理相机的鼠标输入
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
            xoffset *= MouseSensitivity;  // 根据灵敏度调整
            yoffset *= MouseSensitivity;

            Yaw += xoffset;  // 更新水平角度
            Pitch += yoffset;  // 更新垂直角度

            if (constrainPitch) {
                Pitch = glm::clamp(Pitch, -89.0f, 89.0f);  // 限制垂直角度的范围
            }

            updateCameraVectors();  // 更新相机的朝向
            viewMatrixDirty = true;  // 标记需要更新视图矩阵
        }

        // 处理相机的鼠标滚轮输入
        void ProcessMouseScroll(float yoffset) {
            Zoom -= yoffset;  // 根据滚轮的值调整视野
            Zoom = glm::clamp(Zoom, 1.0f, 90.0f);  // 限制视野范围
        }

        // 重置相机到默认位置和角度
        void ResetCamera() {
            Position = glm::vec3(0.0f, 0.0f, 3.0f);  // 设置默认位置
            Front = glm::vec3(0.0f, 0.0f, -1.0f);    // 设置默认朝向
            Yaw = -90.0f;                            // 设置默认水平角度
            Pitch = 0.0f;                            // 设置默认垂直角度
            updateCameraVectors();  // 更新相机朝向
            viewMatrixDirty = true;  // 标记需要更新视图矩阵
        }

    private:
        // 更新相机的朝向向量
        void updateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);  // 归一化朝向向量

            Right = glm::normalize(glm::cross(Front, WorldUp));  // 计算右向量
            Up = glm::normalize(glm::cross(Right, Front));  // 计算上向量
        }

        // 如果视图矩阵需要更新，则更新它
        void updateViewMatrixIfNeeded() {
            if (viewMatrixDirty) {
                matrixManager.SetViewMatrix(Position, Position + Front, Up);
                viewMatrixDirty = false;  // 更新完成，重置标记
            }
        }
    };

} // namespace Core

#endif // CAMERA_H
