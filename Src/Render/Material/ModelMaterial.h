#pragma once

#include "Material.h"
#include "../../Resources/Texture.h"

// ModelMaterial 类，继承自 Material
class ModelMaterial : public Material {
public:
    Texture* albedo;  // 漫反射贴图

    // 构造函数，使用默认的 model.fs 着色器和初始化 albedo 贴图
    ModelMaterial(Texture* _albedo);

    // 设置材质的 uniform 参数
    void SetMaterialUniforms() override;

    // 使用 DefaultSetup 配置材质的默认设置
    void Setup();
};
