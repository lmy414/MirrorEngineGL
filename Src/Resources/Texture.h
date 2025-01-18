#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Render/Material.h"
#include "stb_image.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "../Core/EditorResource.h"
#include <map>


class Texture2D {
public:
    enum class ETexType {
        RGB,
        RGBA,
        SRGB,
        SRGBA,
        RED
    };

    // 加载2D纹理
    Texture2D(std::string _path, ETexType type = ETexType::SRGB, bool _is_editor = false);
    Texture2D(const char* _path, ETexType type = ETexType::SRGB, bool _is_editor = false);
    ~Texture2D();

    bool LoadTexture2D(const char* path, ETexType type);
    void ResetTextureType(ETexType type);
    void DeleteTexture2D();
    // 添加一个用于获取路径的 getter 方法
    const std::string& getPath() const {return path;}//返回路径
    // 获取纹理 ID
    unsigned int GetID() const { return id; }

private:
    unsigned int id;
    std::string path;
    std::string name;
    int width, height, nrChannels;
    ETexType tex_type;
    bool is_editor;
    bool is_valid;

    static std::map<std::string, Texture2D*> LoadedTextures;
    EditorResource<Material*>       textureRefs;
};

