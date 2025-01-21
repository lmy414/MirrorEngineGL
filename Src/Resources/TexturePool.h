#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H

#include <unordered_map>
#include <memory>
#include "Texture.h"

class TexturePool {
public:
    // 添加纹理到纹理池
    void AddTexture(const std::shared_ptr<Texture>& texture) {
        m_textures[texture->GetID()] = texture;
        m_textureNames[texture->GetName()] = texture;
    }

    // 通过纹理ID查找纹理
    std::shared_ptr<Texture> GetTextureByID(GLuint id) {
        if (m_textures.find(id) != m_textures.end()) {
            return m_textures[id];
        }
        return nullptr;
    }

    // 通过纹理名称查找纹理
    std::shared_ptr<Texture> GetTextureByName(const std::string& name) {
        if (m_textureNames.find(name) != m_textureNames.end()) {
            return m_textureNames[name];
        }
        return nullptr;
    }

    // 检查纹理是否已经存在，避免重复加载
    bool TextureExists(const std::string& name) {
        return m_textureNames.find(name) != m_textureNames.end();
    }

    // 通过路径获取纹理，如果纹理已经存在，则返回已加载的纹理
    std::shared_ptr<Texture> LoadTexture(const std::string& name, const std::string& path,
                                         Texture::TextureType type, Texture::TextureChannelType channelType) {
        if (TextureExists(name)) {
            std::cout << "Texture already loaded: " << name << std::endl;
            return GetTextureByName(name); // 如果纹理已加载，直接返回
        }

        // 如果纹理未加载，创建新的纹理并加载
        std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(name, path, type, channelType);
        AddTexture(newTexture);  // 添加到纹理池中
        return newTexture;
    }

private:
    std::unordered_map<GLuint, std::shared_ptr<Texture>> m_textures;         // 通过纹理ID查找纹理
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_textureNames; // 通过纹理名称查找纹理
};

#endif // TEXTUREPOOL_H
