#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../Shader.h"
#include "../../Resources/Texture.h"

// 材质类型枚举
enum class EMaterialType {
    Default = 0,    // 默认材质
    Model = 1,      // 模型材质
    Unlit = 2,      // 无光照材质
    Custom = 3      // 自定义材质
};

// 材质的参数集合，用于保存材质的所有变量
using MaterialVariables = std::unordered_map<std::string, unsigned int>;

// 材质基类
class Material {
public:
    static unsigned int cur_id;               // 静态变量，用于生成唯一 ID
    unsigned int id;                           // 每个实例的唯一标识符
    Shader* shader;                            // 用于渲染该材质的着色器
    MaterialVariables material_variables;      // 材质的变量集合

    // 构造函数
    Material(Shader* shader);

    // 析构函数
    virtual ~Material();

    // 检查材质是否有效
    bool IsValid() const;

    // 设置纹理
    virtual void SetTexture(const std::string& variableName, unsigned int textureID);

    // 配置材质的默认设置
    virtual void DefaultSetup();

    // 处理纹理被移除时的逻辑
    virtual void OnTextureRemoved(const std::string& variableName);

    // 设置材质的 uniform 参数（纯虚函数，由子类实现）
    virtual void SetMaterialUniforms() = 0;
};
