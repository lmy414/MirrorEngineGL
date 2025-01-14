#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <glad/glad.h>
#include "stb_image.h"
#include <string>

class TextureLoader {
public:
    // ��̬������������
    static unsigned int LoadTexture(const std::string& path, bool flipVertically = true, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);

private:
    // ��ֹ���� TextureLoader ʵ��
    TextureLoader() = delete;
};

#endif // TEXTURE_LOADER_H
#pragma once
