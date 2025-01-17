#include "Material.h"
#include <string>
#include <sstream>
#include <iostream>
#include "../Tool/ToString.h"
// Material 构造函数
Material::Material(unsigned int id, const std::string& name, Shader* shader)
    : ID(id), Name(name), shader(shader) {
    std::cout << "Material Created - ID: " << ID << ", Name: " << Name << std::endl;  // 输出材质创建信息
}

// 设置材质纹理
void Material::SetTexture(const std::string& variableName, unsigned int textureID) {
    std::cout << "Setting texture - Variable: " << variableName << ", TextureID: " << textureID << std::endl;
    material_variables[variableName] = textureID;  // 直接存储纹理 ID
}

// 判断材质是否有效
bool Material::IsValid() const {
    bool valid = (ID != 0 && shader != nullptr);  // 材质ID和着色器都不为空
    std::cout << "Material Validity - ID: " << ID << ", Valid: " << (valid ? "True" : "False") << std::endl;
    return valid;
}

// 移除材质纹理
void Material::RemoveTexture(const std::string& variableName) {
    std::cout << "Removing texture - Variable: " << variableName << std::endl;
    material_variables.erase(variableName);
}

// 为材质提供默认纹理
void Material::SetDefaultTexture() {
    std::cout << "Setting default texture (diffuseTexture = 0)" << std::endl;
    SetTexture("diffuseTexture", 0);  // 使用0作为默认纹理 ID
}

// 设置材质的着色器
void Material::SetShader(Shader* newShader) {
    std::cout << "Setting shader - New Shader: " << newShader << std::endl;
    shader = newShader;
}

// 获取材质的着色器
Shader* Material::GetShader() const {
    std::cout << "Getting shader - Shader: " << shader << std::endl;
    return shader;
}

// 这是一个虚函数，在派生类中可以重写
void Material::OnTextureRemoved(const std::string& variableName) {
    std::cout << "Texture Removed - Variable: " << variableName << std::endl;
    // 父类可以在这里做一些通用的处理，子类重写时可以增加自定义处理
}

// SimpleMaterial 构造函数
SimpleMaterial::SimpleMaterial(unsigned int id, const std::string& name, Shader* shaderPtr,
                               unsigned int diffuseTex, unsigned int normalTex, 
                               float shininess, float specularStrength)
    : Material(id, name, shaderPtr), diffuseTexture(diffuseTex), normalTexture(normalTex),
      shininess(shininess), specularStrength(specularStrength) {
    std::cout << "SimpleMaterial Created - ID: " << id << ", Name: " << name << std::endl;
}

// 设置材质的 uniform 参数
void SimpleMaterial::SetMaterialUniforms() {
    std::cout << "Setting SimpleMaterial uniforms" << std::endl;
    shader->setInt("diffuseTexture", 0);
    shader->setInt("normalTexture", 1);
    shader->setFloat("shininess", shininess);
    shader->setFloat("specularStrength", specularStrength);

    if (diffuseTexture != 0) {
        std::cout << "Binding diffuse texture ID: " << diffuseTexture << std::endl;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture);
    }

    if (normalTexture != 0) {
        std::cout << "Binding normal texture ID: " << normalTexture << std::endl;
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalTexture);
    }
}

// 设置材质默认纹理
void SimpleMaterial::SetDefaultTexture() {
    std::cout << "Setting SimpleMaterial default textures (diffuse = 0, normal = 0)" << std::endl;
    diffuseTexture = 0;  // 使用默认纹理（这里为0）
    normalTexture = 0;
}

// 覆盖父类的 OnTextureRemoved 方法
void SimpleMaterial::OnTextureRemoved(const std::string& variableName) {
    std::cout << "SimpleMaterial - Texture Removed: " << variableName << std::endl;
    if (variableName == "diffuseTexture") {
        diffuseTexture = 0;  // 设置 diffuseTexture 为无效纹理 ID
    } else if (variableName == "normalTexture") {
        normalTexture = 0;  // 设置 normalTexture 为无效纹理 ID
    }
}

// DefaultMaterial 构造函数
DefaultMaterial::DefaultMaterial(unsigned int id, const std::string& name, Shader* shaderPtr, const glm::vec3& color)
    : Material(id, name, shaderPtr), baseColor(color) {
    std::cout << "DefaultMaterial Created - ID: " << id << ", Name: " << name << ", BaseColor: " << ToString::toString(color) << std::endl;
}

// 设置材质的 uniform 参数
void DefaultMaterial::SetMaterialUniforms() {
    std::cout << "Setting DefaultMaterial uniform - BaseColor: " << ToString::toString(baseColor) << std::endl;
    shader->setVec3("baseColor", baseColor);
}

// 设置默认材质颜色
void DefaultMaterial::SetDefaultTexture() {
    std::cout << "Setting DefaultMaterial default color (white)" << std::endl;
    baseColor = glm::vec3(1.0f, 1.0f, 1.0f);  // 设置为白色作为默认颜色
}

// 覆盖父类的 OnTextureRemoved 方法
void DefaultMaterial::OnTextureRemoved(const std::string& variableName) {
    std::cout << "DefaultMaterial - Texture Removed: " << variableName << std::endl;
    if (variableName == "baseColor") {
        baseColor = glm::vec3(1.0f, 1.0f, 1.0f);  // 还原为默认的白色
    }
}
