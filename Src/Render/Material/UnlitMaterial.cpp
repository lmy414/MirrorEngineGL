#include "UnlitMaterial.h"
#include <iostream>

// UnlitMaterial 构造函数
UnlitMaterial::UnlitMaterial(Texture2D* _albedo_map)
    : Material(new Shader("E:/MirrorEngine/MirrorEngine2/Shaders/unlit.vs","E:/MirrorEngine/MirrorEngine2/Shaders/unlit.fs")), albedo_map(_albedo_map) {
    std::cout << "UnlitMaterial Created" << std::endl;
}

// 设置 UnlitMaterial 的 uniform 参数
void UnlitMaterial::SetMaterialUniforms() {
    shader->setInt("albedo_map", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedo_map->GetID());
}

// 使用 DefaultSetup 配置无光照材质的默认设置
void UnlitMaterial::Setup() {
    DefaultSetup();
}
