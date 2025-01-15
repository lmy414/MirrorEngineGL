#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Tool/MatrixManager.h"  // ???? MatrixManager

namespace Core {

    // ???????????????????
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,    // ????
        DOWN   // ????
    };

    class Camera {
    public:
        // ?????????
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        // ?????
        float Yaw;
        float Pitch;

        // ???????
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        // ?????????
        MatrixManager matrixManager;

    private:
        bool viewMatrixDirty = true;  // ???????????????????????

    public:
        // ???????????????????
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

        // ???????¦Ë??
        void SetPosition(const glm::vec3& position) {
            Position = position;
            updateCameraVectors();
            viewMatrixDirty = true;  // ?????????????????
        }

        // ????????????????
        void SetFront(const glm::vec3& front) {
            Front = front;
            updateCameraVectors();
            viewMatrixDirty = true;  // ?????????????????
        }

        // ?????????????????????????
        glm::mat4 GetViewMatrix() {
            updateViewMatrixIfNeeded(); // ??????????????
            return matrixManager.GetViewMatrix();
        }

        // ??????????
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
                Position += Up * velocity;   // ???????
                break;
            case CameraMovement::DOWN:
                Position -= Up * velocity;   // ???????
                break;
            }
            viewMatrixDirty = true;  // ?????????????????
        }

        // ?????????
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;

            Yaw += xoffset;
            Pitch += yoffset;

            if (constrainPitch) {
                Pitch = glm::clamp(Pitch, -89.0f, 89.0f);
            }

            updateCameraVectors();
            viewMatrixDirty = true;  // ?????????????????
        }

        // ??????????
        void ProcessMouseScroll(float yoffset) {
            Zoom -= yoffset;
            Zoom = glm::clamp(Zoom, 1.0f, 90.0f);
        }

        // ????????????¦Ë?¨²????
        void ResetCamera() {
            Position = glm::vec3(0.0f, 0.0f, 3.0f);  // ???¦Ë??
            Front = glm::vec3(0.0f, 0.0f, -1.0f);    // ??????
            Yaw = -90.0f;                            // ????????
            Pitch = 0.0f;                            // ?????????
            updateCameraVectors();
            viewMatrixDirty = true;  // ?????????????????
        }

    private:
        // ?????????????????
        void updateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);

            Right = glm::normalize(glm::cross(Front, WorldUp));
            Up = glm::normalize(glm::cross(Right, Front));
        }

        // ???????????????????§Ò?
        void updateViewMatrixIfNeeded() {
            if (viewMatrixDirty) {
                matrixManager.SetViewMatrix(Position, Position + Front, Up);
                viewMatrixDirty = false;
            }
        }
    };

} // namespace Core

#endif // CAMERA_H
