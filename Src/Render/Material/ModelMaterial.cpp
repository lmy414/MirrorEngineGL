#include "ModelMaterial.h"
#include <iostream>


// ModelMaterial 构造函数
ModelMaterial::ModelMaterial(Texture2D* _albedo)
    : Material(new Shader("E:/MirrorEngine/MirrorEngine2/Shaders/Model.vs","E:/MirrorEngine/MirrorEngine2/Shaders/Model.fs")), albedo(_albedo) {
    std::cout << "ModelMaterial Created" << std::endl;
}

// 设置 ModelMaterial 的 uniform 参数
void ModelMaterial::SetMaterialUniforms() {
    shader->setInt("albedo", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedo->GetID());
}

// 使用 DefaultSetup 配置材质的默认设置
void ModelMaterial::Setup() {
    DefaultSetup();
}
