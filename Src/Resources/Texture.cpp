#include "Texture.h"
#include <iostream>

unsigned int Texture::LoadTexture(const std::string& path, bool flipVertically, 
                                        GLenum wrapS, GLenum wrapT, 
                                        GLenum minFilter, GLenum magFilter) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // �����������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // ˮƽ�����ظ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // ��ֱ�����ظ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // ��Сʱʹ�����Թ���
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // �Ŵ�ʱʹ������ڹ���


    // ����ͼƬ����������
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
        textureID = 0;  // �������ʧ�ܣ����� 0
    }
    stbi_image_free(data);

    return textureID;
}

void Texture::ClearTextures() {
    // ��������
    // ���磺glDeleteTextures(textureCount, textureArray);
}
