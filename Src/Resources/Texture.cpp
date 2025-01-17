#include "Texture.h"

std::map<std::string, Texture2D*> Texture2D::LoadedTextures;

Texture2D::Texture2D(std::string _path, ETexType type, bool _is_editor) :
    path(_path),
    tex_type(type),
    is_editor(_is_editor)
{
    is_valid = LoadTexture2D(path.c_str(), type);
}

Texture2D::Texture2D(const char* _path, ETexType type, bool _is_editor) :
    path(_path),
    tex_type(type),
    is_editor(_is_editor)
{
    is_valid = LoadTexture2D(path.c_str(), type);
}

Texture2D::~Texture2D()
{
    DeleteTexture2D();
    LoadedTextures.erase(name);
}

void Texture2D::DeleteTexture2D()
{
    std::cout << "Delete Texture: " << path << std::endl;
    for (auto it : textureRefs.references)
    {
        it->OnTextureRemoved(path);
    }

    glDeleteTextures(1, &id);
}

bool Texture2D::LoadTexture2D(const char* texture_path, ETexType type)
{
    int width, height, nrComponents;
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string path_s = texture_path;
    std::replace(path_s.begin(), path_s.end(), '\\', '/');
    unsigned char* data = stbi_load(path_s.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        this->path = path_s;
        this->width = width;
        this->height = height;
        this->nrChannels = nrComponents;

        if (nrChannels == 1)
        {
            tex_type = ETexType::RED;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 3)
        {
            if (type == ETexType::SRGB || type == ETexType::SRGBA)
            {
                tex_type = ETexType::SRGB;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            else
            {
                tex_type = ETexType::RGB;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
        }
        else if (nrChannels == 4)
        {
            if (type == ETexType::SRGB || type == ETexType::SRGBA)
            {
                tex_type = ETexType::SRGBA;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            else
            {
                tex_type = ETexType::RGBA;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
       
        stbi_image_free(data);
        return false;
    }

    stbi_image_free(data);
    name = path_s.substr(path_s.find_last_of('/') + 1, path_s.size());
    LoadedTextures.insert(std::map<std::string, Texture2D*>::value_type(name, this));
    return true;
}

void Texture2D::ResetTextureType(ETexType type)
{
    LoadTexture2D(path.c_str(), type);
}
