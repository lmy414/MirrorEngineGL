#include "Texture.h"
#include <iostream>

unsigned int Texture::LoadTexture(const std::string& path, bool flipVertically, 
                                        GLenum wrapS, GLenum wrapT, 
                                        GLenum minFilter, GLenum magFilter) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // 纹理参数设置
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // 水平方向重复
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // 垂直方向重复
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // 缩小时使用线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // 放大时使用最近邻过滤


    // 加载图片并生成纹理
    stbi_set_flip_vertically_on_load(flipVertically);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 4) format = GL_RGBA;
        else if (nrChannels == 1) format = GL_RED;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture: " << path << std::endl;
        textureID = 0;  // 如果加载失败，返回 0
    }
    stbi_image_free(data);

    return textureID;
}

void Texture::ClearTextures() {
    // 清理纹理
    // 例如：glDeleteTextures(textureCount, textureArray);
}
