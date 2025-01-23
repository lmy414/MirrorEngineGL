#include "Shader.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


std::unordered_map<std::string, std::shared_ptr<Shader>> Shader::shaderMap;

// ���캯��
Shader::Shader(const char* vertexPath, const char* fragmentPath)
    : vertexPath(convertPath(vertexPath)), fragmentPath(convertPath(fragmentPath)) {
    loadAndCompile();
}

// ˢ�¹���
bool Shader::Refresh() {
    std::cout << "Refreshing Shader from: [vert] " << vertexPath
              << " [frag] " << fragmentPath << std::endl;
    loadAndCompile();
    return isValid();
}

// ������ɫ������
void Shader::use() const {
    glUseProgram(ID);
}

// ���� Uniform ����
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
    
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}


// ���ز�������ɫ��
void Shader::loadAndCompile() {
    std::string vertexCode = loadShaderFile(vertexPath.c_str());
    std::string fragmentCode = loadShaderFile(fragmentPath.c_str());

    unsigned int vertex, fragment;
    compileShader(vertexCode.c_str(), GL_VERTEX_SHADER, vertex);
    compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER, fragment);

    // ���������ӳ���
    glDeleteProgram(ID); // ����ɵĳ���
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    linkProgram();

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// ·��ת������
std::string Shader::convertPath(const char* path) {
    std::string result = path;
    std::replace(result.begin(), result.end(), '\\', '/');
    return result;
}

// ������ɫ���ļ�
std::string Shader::loadShaderFile(const char* path) const {
    std::ifstream file;
    std::stringstream stream;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
        stream << file.rdbuf();
        file.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << path << std::endl;
    }
    return stream.str();
}

// ���뵥����ɫ��
void Shader::compileShader(const char* code, GLenum type, unsigned int& shaderID) const {
    shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

// ������ɫ������
void Shader::linkProgram() {
    glLinkProgram(ID);
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

// �����Ч��
bool Shader::isValid() const {
    return glIsProgram(ID);
}
