#include "Material.h"
#include <iostream>

// 静态变量初始化
unsigned int Material::cur_id = 0;

// Material 构造函数
Material::Material(Shader* shader)
    : id(cur_id++), shader(shader) {
    std::cout << "Material Created - ID: " << id << std::endl;
}

// 析构函数
Material::~Material() {
    std::cout << "Material Destroyed - ID: " << id << std::endl;
}

// 检查材质是否有效
bool Material::IsValid() const {
    return shader != nullptr;
}

// 设置纹理
void Material::SetTexture(const std::string& variableName, unsigned int textureID) {
    material_variables[variableName] = textureID;
}

// 配置材质的默认设置
void Material::DefaultSetup() {
    // 设置默认的纹理（如果有），并绑定它们
    for (const auto& var : material_variables) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, var.second);
    }
}

// 处理纹理被移除时的逻辑
void Material::OnTextureRemoved(const std::string& variableName) {
    // 替换为默认纹理（可以根据具体需求调整）
    std::cout << "Texture Removed - Variable: " << variableName << std::endl;
    SetTexture(variableName, 0);  // 默认纹理为 0
}
