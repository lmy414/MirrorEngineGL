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
    // 纹理通道类型
    enum class TextureChannelType {
        RGB,        // RGB
        RGBA,       // RGBA
    };

    // 纹理类型
    enum class TextureType {
        DIFFUSE,    // 漫反射纹理
        SPECULAR,   // 高光纹理
        NORMAL,     // 法线纹理
        EMISSIVE,   // 自发光纹理
        AMBIENT_OCCLUSION, // 环境光遮蔽纹理
        ROUGHNESS,  // 粗糙度纹理
        METALLIC    // 金属度纹理
    };

    // 构造函数
    Texture(const std::string& name, const std::string& path, TextureType type, TextureChannelType channelType)
        : m_name(name), m_path(path), m_type(type), m_channelType(channelType), m_id(0) {
        LoadTexture();
    }

    // 加载纹理
    void LoadTexture() {
        int width, height, channels;
        unsigned char* data = stbi_load(m_path.c_str(), &width, &height, &channels, 0);
        if (data) {
            glGenTextures(1, &m_id);
            glBindTexture(GL_TEXTURE_2D, m_id);

            // 设置纹理的重复方式和过滤方式
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // 根据通道类型来设置纹理格式
            GLenum format = (m_channelType == TextureChannelType::RGBA) ? GL_RGBA : 
                            (m_channelType == TextureChannelType::RGB) ? GL_RGB : GL_RED;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load texture: " << m_path << std::endl;
        }
    }

    // 获取纹理ID
    GLuint GetID() const { return m_id; }

    // 获取纹理名称
    const std::string& GetName() const { return m_name; }

    // 获取纹理类型
    TextureType GetType() const { return m_type; }

    // 获取纹理通道类型
    TextureChannelType GetChannelType() const { return m_channelType; }

private:
    std::string m_name;                 // 纹理名称
    std::string m_path;                 // 纹理路径
    GLuint m_id;                        // 纹理ID (OpenGL纹理ID)
    TextureType m_type;                 // 纹理类型
    TextureChannelType m_channelType;   // 纹理通道类型
};

#endif // TEXTURE_H

