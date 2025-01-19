#include "MaterialManager.h"
#include <iostream>

// MaterialManager 的 CreateMaterialByType 实现
Material* MaterialManager::CreateMaterialByType(EMaterialType type, Texture2D* albedo) {
    switch (type) {
    case EMaterialType::Model:
        return new ModelMaterial(albedo);
    case EMaterialType::Unlit:
        return new UnlitMaterial(albedo);
    default:
        std::cerr << "Unknown Material Type!" << std::endl;
        return nullptr;
    }
}
#include "MaterialManager.h"
