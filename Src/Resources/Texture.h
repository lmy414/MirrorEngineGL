#pragma once
#include <glad/glad.h>
#include <string>
#include <GLFW/glfw3.h>
#include "stb_image.h"


class Texture {
public:
    // ����2D����
    static unsigned int LoadTexture(const std::string& path, bool flipVertically = true, 
                                    GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT, 
                                    GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);

    // ��������������Դ���������������Դ���������
    static void ClearTextures();
};
