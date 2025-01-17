#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <glm/gtc/type_ptr.hpp>  // ������ͷ�ļ�
class Shader {
    
public:
    // ���캯�������ز�������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath);

    // ʹ�õ�ǰ��ɫ������
    void use();

    // ���� uniform ���͵ı���
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;

private:
    // ��ɫ������ ID
    unsigned int ID;

    // ������ɫ�������ļ�
    std::string loadShaderFile(const char* path);

    // ������ɫ��
    void compileShader(const char* code, GLenum shaderType, unsigned int& shaderID);

    // ������ɫ������
    void linkProgram();
};

#endif // SHADER_H
