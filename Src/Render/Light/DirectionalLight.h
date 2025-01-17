#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <glm/glm.hpp>
#include "../Shader.h"

class DirectionalLight {
public:
    glm::vec3 direction;  // 光照方向
    glm::vec3 color;      // 光源颜色
    float intensity;      // 光照强度

    // 构造函数，初始化光源属性
    DirectionalLight(
        const glm::vec3& direction = glm::vec3(-0.2f, -1.0f, -0.3f),
        const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f),
        float intensity = 1.0f)
        : direction(direction), color(color), intensity(intensity) { }

    // 设置光源的 uniform 参数
    void SetLightUniforms(Shader& shader) {
        shader.setVec3("Direction", direction);
        shader.setVec3("LightColor", color);
        shader.setFloat("Intensity", intensity);
    }

    // 控制光照方向
    void SetDirection(const glm::vec3& newDirection) {
        direction = newDirection;
    }

    // 控制光照颜色
    void SetColor(const glm::vec3& newColor) {
        color = newColor;
    }

    // 控制光照强度
    void SetIntensity(float newIntensity) {
        intensity = newIntensity;
    }

    // 获取光照方向
    glm::vec3 GetDirection() const {
        return direction;
    }

    // 获取光照颜色
    glm::vec3 GetColor() const {
        return color;
    }

    // 获取光照强度
    float GetIntensity() const {
        return intensity;
    }
};

#endif // DIRECTIONAL_LIGHT_H
