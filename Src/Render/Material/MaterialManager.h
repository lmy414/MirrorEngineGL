#pragma once

#include "Material.h"
#include "ModelMaterial.h"
#include "UnlitMaterial.h"

// 材质管理器类，用于创建不同类型的材质
class MaterialManager {
public:
    // 根据材质类型创建材质
    static Material* CreateMaterialByType(EMaterialType type, Texture2D* albedo = nullptr);
};
