#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Render/Material/Material.h"
#include "stb_image.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "../Core/EditorResource.h"
#include <map>


class Texture {
public:
    // ����ͨ������
    enum class TextureChannelType {
        RGB,        // RGB
        RGBA,       // RGBA
    };

    // ��������
    enum class TextureType {
        DIFFUSE,    // ����������
        SPECULAR,   // �߹�����
        NORMAL,     // ��������
        EMISSIVE,   // �Է�������
        AMBIENT_OCCLUSION, // �������ڱ�����
        ROUGHNESS,  // �ֲڶ�����
        METALLIC    // ����������
    };

    // ���캯��
    Texture(const std::string& name, const std::string& path, TextureType type, TextureChannelType channelType)
        : m_name(name), m_path(path), m_type(type), m_channelType(channelType), m_id(0) {
        LoadTexture();
    }

    // ��������
    void LoadTexture() {
        int width, height, channels;
        unsigned char* data = stbi_load(m_path.c_str(), &width, &height, &channels, 0);
        if (data) {
            glGenTextures(1, &m_id);
            glBindTexture(GL_TEXTURE_2D, m_id);

            // ����������ظ���ʽ�͹��˷�ʽ
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // ����ͨ�����������������ʽ
            GLenum format = (m_channelType == TextureChannelType::RGBA) ? GL_RGBA : 
                            (m_channelType == TextureChannelType::RGB) ? GL_RGB : GL_RED;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load texture: " << m_path << std::endl;
        }
    }

    // ��ȡ����ID
    GLuint GetID() const { return m_id; }

    // ��ȡ��������
    const std::string& GetName() const { return m_name; }

    // ��ȡ��������
    TextureType GetType() const { return m_type; }

    // ��ȡ����ͨ������
    TextureChannelType GetChannelType() const { return m_channelType; }

private:
    std::string m_name;                 // ��������
    std::string m_path;                 // ����·��
    GLuint m_id;                        // ����ID (OpenGL����ID)
    TextureType m_type;                 // ��������
    TextureChannelType m_channelType;   // ����ͨ������
};

#endif // TEXTURE_H

