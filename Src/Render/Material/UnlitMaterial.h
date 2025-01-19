#pragma once

#include "Material.h"
#include "../../Resources/Texture.h"

// UnlitMaterial 类，继承自 Material
class UnlitMaterial : public Material {
public:
    Texture2D* albedo_map;  // 用于无光照材质的纹理

    // 构造函数，初始化 albedo_map 贴图
    UnlitMaterial(Texture2D* _albedo_map);

    // 设置材质的 uniform 参数
    void SetMaterialUniforms() override;

    // 使用 DefaultSetup 配置无光照材质的默认设置
    void Setup();
};
