#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"

// 材质类型枚举
enum class EMaterialType {
    Default = 0,    // 默认材质
    Simple = 1,     // 简单材质
    PBR = 2,        // 基于物理的材质
    Custom = 3      // 自定义材质
};

// 材质基类
class Material {
public:
    unsigned int ID;                                  // 材质的唯一 ID
    std::string Name;                                 // 材质名称
    Shader* shader;                                   // 绑定的着色器
    std::unordered_map<std::string, unsigned int> material_variables; // 材质的纹理变量

    // 构造函数
    Material(unsigned int id, const std::string& name, Shader* shader);

    // 设置纹理
    virtual void SetTexture(const std::string& variableName, unsigned int textureID);

    // 判断材质是否有效
    bool IsValid() const;

    // 移除材质纹理
    virtual void RemoveTexture(const std::string& variableName);

    // 提供默认纹理或参数
    virtual void SetDefaultTexture();

    // 设置材质的着色器
    void SetShader(Shader* newShader);

    // 获取材质的着色器
    Shader* GetShader() const;

    // 处理纹理被移除的情况
    virtual void OnTextureRemoved(const std::string& variableName);

    // 设置材质的 uniform 参数（纯虚函数，由子类实现）
    virtual void SetMaterialUniforms() = 0;

    // 虚析构函数
    virtual ~Material() = default;
};

// 简单材质类，继承自 Material
class SimpleMaterial : public Material {
public:
    unsigned int diffuseTexture;       // 漫反射纹理
    unsigned int normalTexture;        // 法线纹理
    float shininess;                   // 光泽度
    float specularStrength;            // 镜面强度

    // 构造函数
    SimpleMaterial(unsigned int id, const std::string& name, Shader* shaderPtr,
                   unsigned int diffuseTex, unsigned int normalTex,
                   float shininess, float specularStrength);

    // 设置材质的 uniform 参数
    void SetMaterialUniforms() override;

    // 设置默认纹理
    void SetDefaultTexture() override;

    // 覆盖父类的 OnTextureRemoved 方法
    void OnTextureRemoved(const std::string& variableName) override;
};

// 默认材质类，继承自 Material
class DefaultMaterial : public Material {
public:
    glm::vec3 baseColor;              // 基础颜色

    // 构造函数
    DefaultMaterial(unsigned int id, const std::string& name, Shader* shaderPtr, const glm::vec3& color);

    // 设置材质的 uniform 参数
    void SetMaterialUniforms() override;

    // 设置默认材质颜色
    void SetDefaultTexture() override;

    // 覆盖父类的 OnTextureRemoved 方法
    void OnTextureRemoved(const std::string& variableName) override;
};
