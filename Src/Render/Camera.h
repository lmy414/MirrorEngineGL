#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Tool/MatrixManager.h"  // ���� MatrixManager ���о�����

namespace Core {

    // ������ƶ�����ö��
    enum class CameraMovement {
        FORWARD,  // ��ǰ�ƶ�
        BACKWARD, // ����ƶ�
        LEFT,     // �����ƶ�
        RIGHT,    // �����ƶ�
        UP,       // �����ƶ�
        DOWN      // �����ƶ�
    };

    class Camera {
    public:
        // ���������
        glm::vec3 Position;  // ���λ��
        glm::vec3 Front;     // ����ĳ���
        glm::vec3 Up;        // �����������
        glm::vec3 Right;     // �����������
        glm::vec3 WorldUp;   // ����������������ڼ�������ķ���

        // �����ŷ���ǣ����Ƴ���
        float Yaw;   // ˮƽ��ת�Ƕ�
        float Pitch; // ��ֱ��ת�Ƕ�

        // ����˶�����
        float MovementSpeed;     // �˶��ٶ�
        float MouseSensitivity;  // ���������
        float Zoom;              // ���ż�����Ұ��Χ��

        // ���������������������ͼ����
        MatrixManager matrixManager;

    private:
        bool viewMatrixDirty = true;  // ��ͼ�����Ƿ���Ҫ����

    public:
        // ���캯������ʼ�������Ĭ��ֵ
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
            updateCameraVectors();  // ���������������
        }

        // �������λ�ò������������
        void SetPosition(const glm::vec3& position) {
            Position = position;
            updateCameraVectors();
            viewMatrixDirty = true;  // �����Ҫ������ͼ����
        }

        // ����������򲢸����������
        void SetFront(const glm::vec3& front) {
            Front = front;
            updateCameraVectors();
            viewMatrixDirty = true;  // �����Ҫ������ͼ����
        }

        // ��ȡ��ͼ����ȷ���������µ�
        glm::mat4 GetViewMatrix() {
            updateViewMatrixIfNeeded(); // �����ͼ�����Ƿ���Ҫ����
            return matrixManager.GetViewMatrix();
        }

        // ��������ļ�������
        void ProcessKeyboard(CameraMovement direction, float deltaTime) {
            float velocity = MovementSpeed * deltaTime;  // �����ƶ��ٶ�
            switch (direction) {
            case CameraMovement::FORWARD:
                Position += Front * velocity;  // ��ǰ�ƶ�
                break;
            case CameraMovement::BACKWARD:
                Position -= Front * velocity; // ����ƶ�
                break;
            case CameraMovement::LEFT:
                Position -= Right * velocity; // �����ƶ�
                break;
            case CameraMovement::RIGHT:
                Position += Right * velocity; // �����ƶ�
                break;
            case CameraMovement::UP:
                Position += Up * velocity;    // �����ƶ�
                break;
            case CameraMovement::DOWN:
                Position -= Up * velocity;    // �����ƶ�
                break;
            }
            viewMatrixDirty = true;  // �����Ҫ������ͼ����
        }

        // ����������������
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
            xoffset *= MouseSensitivity;  // ���������ȵ���
            yoffset *= MouseSensitivity;

            Yaw += xoffset;  // ����ˮƽ�Ƕ�
            Pitch += yoffset;  // ���´�ֱ�Ƕ�

            if (constrainPitch) {
                Pitch = glm::clamp(Pitch, -89.0f, 89.0f);  // ���ƴ�ֱ�Ƕȵķ�Χ
            }

            updateCameraVectors();  // ��������ĳ���
            viewMatrixDirty = true;  // �����Ҫ������ͼ����
        }

        // �������������������
        void ProcessMouseScroll(float yoffset) {
            Zoom -= yoffset;  // ���ݹ��ֵ�ֵ������Ұ
            Zoom = glm::clamp(Zoom, 1.0f, 90.0f);  // ������Ұ��Χ
        }

        // ���������Ĭ��λ�úͽǶ�
        void ResetCamera() {
            Position = glm::vec3(0.0f, 0.0f, 3.0f);  // ����Ĭ��λ��
            Front = glm::vec3(0.0f, 0.0f, -1.0f);    // ����Ĭ�ϳ���
            Yaw = -90.0f;                            // ����Ĭ��ˮƽ�Ƕ�
            Pitch = 0.0f;                            // ����Ĭ�ϴ�ֱ�Ƕ�
            updateCameraVectors();  // �����������
            viewMatrixDirty = true;  // �����Ҫ������ͼ����
        }

    private:
        // ��������ĳ�������
        void updateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);  // ��һ����������

            Right = glm::normalize(glm::cross(Front, WorldUp));  // ����������
            Up = glm::normalize(glm::cross(Right, Front));  // ����������
        }

        // �����ͼ������Ҫ���£��������
        void updateViewMatrixIfNeeded() {
            if (viewMatrixDirty) {
                matrixManager.SetViewMatrix(Position, Position + Front, Up);
                viewMatrixDirty = false;  // ������ɣ����ñ��
            }
        }
    };

} // namespace Core

#endif // CAMERA_H
