#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <memory> 
#include <GLFW/glfw3.h>

class Shader {
public:
    unsigned int ID; // ��ɫ������ ID
    
    //�洢�Ѿ����ص�������ɫ��
    static std::unordered_map<std::string, std::shared_ptr<Shader>> shaderMap;

    // ���캯��
    Shader(const char* vertexPath, const char* fragmentPath);

    // ˢ�¹���
    bool Refresh();

    // ������ɫ������
    void use() const;

    // ���� Uniform ����
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;

private:
    std::string vertexPath;    // ������ɫ��·��
    std::string fragmentPath;  // Ƭ����ɫ��·��

    // ���ز�������ɫ��
    void loadAndCompile();

    // ·��ת������
    static std::string convertPath(const char* path);

    // ������ɫ���ļ�
    std::string loadShaderFile(const char* path) const;

    // ���뵥����ɫ��
    void compileShader(const char* code, GLenum type, unsigned int& shaderID) const;

    // ������ɫ������
    void linkProgram();

    // �����Ч��
    bool isValid() const;
};

#endif // SHADER_H
