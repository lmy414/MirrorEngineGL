#pragma once
#include <glad/glad.h>
#include <string>
#include <GLFW/glfw3.h>
#include "stb_image.h"


class Texture {
public:
    // 加载2D纹理
    static unsigned int LoadTexture(const std::string& path, bool flipVertically = true, 
                                    GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT, 
                                    GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);

    // 清理所有纹理资源（如果你有纹理资源管理的需求）
    static void ClearTextures();
};
