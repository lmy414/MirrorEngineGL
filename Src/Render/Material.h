#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <string>

// 材质类
class Material {
public:
    unsigned int ID;
    std::string Name;
    Shader* shader;

    // 存储材质的纹理变量
    std::unordered_map<std::string, unsigned int> material_variables;

    // 构造函数
    Material(unsigned int id, const std::string& name, Shader* shader);

    // 设置纹理
    virtual void SetTexture(const std::string& variableName, unsigned int textureID);

    // 判断材质是否有效
    bool IsValid() const;

    // 移除材质纹理
    virtual void RemoveTexture(const std::string& variableName);

    // 为材质提供默认纹理
    virtual void SetDefaultTexture();

    // 设置材质的着色器
    void SetShader(Shader* newShader);

    // 获取材质的着色器
    Shader* GetShader() const;

    // 虚拟函数：纹理移除后的处理
    virtual void OnTextureRemoved(const std::string& variableName);

    virtual void SetMaterialUniforms() = 0; // 设置为纯虚函数
};

// SimpleMaterial 类，继承自 Material
class SimpleMaterial : public Material {
public:
    unsigned int diffuseTexture;
    unsigned int normalTexture;
    float shininess;
    float specularStrength;

    // 构造函数
    SimpleMaterial(unsigned int id, const std::string& name, Shader* shaderPtr,
                   unsigned int diffuseTex, unsigned int normalTex,
                   float shininess, float specularStrength);

    // 设置材质的 uniform 参数
    void SetMaterialUniforms() override;

    // 设置材质默认纹理
    void SetDefaultTexture() override;

    // 覆盖父类的 OnTextureRemoved 方法
    void OnTextureRemoved(const std::string& variableName) override;
};

// DefaultMaterial 类，继承自 Material
class DefaultMaterial : public Material {
public:
    glm::vec3 baseColor;

    // 构造函数
    DefaultMaterial(unsigned int id, const std::string& name, Shader* shaderPtr, const glm::vec3& color);

    // 设置材质的 uniform 参数
    void SetMaterialUniforms() override;

    // 设置默认材质颜色
    void SetDefaultTexture() override;

    // 覆盖父类的 OnTextureRemoved 方法
    void OnTextureRemoved(const std::string& variableName) override;
};
