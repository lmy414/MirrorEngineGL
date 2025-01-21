// ImGuiControls.h
#ifndef IMGUI_CONTROLS_H
#define IMGUI_CONTROLS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// 用来控制旋转、缩放、平移的结构体
struct TransformControls {
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float scale = 1.0f;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

    void DrawGUI() {
        // 绘制旋转
        ImGui::SliderFloat("Rotation X", &rotationX, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotation Y", &rotationY, 0.0f, 360.0f);

        // 绘制缩放
        ImGui::SliderFloat("Scale", &scale, 0.1f, 3.0f);

        // 绘制位置
        ImGui::DragFloat3("Position", &position[0], 0.1f, -10.0f, 10.0f);
    }

    // 返回模型变换矩阵
    glm::mat4 GetTransformMatrix() {
        glm::mat4 model = glm::mat4(1.0f);

        // 旋转
        model = glm::rotate(model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));

        // 缩放
        model = glm::scale(model, glm::vec3(scale, scale, scale));

        // 平移
        model = glm::translate(model, position);

        return model;
    }
};

#endif // IMGUI_CONTROLS_H
