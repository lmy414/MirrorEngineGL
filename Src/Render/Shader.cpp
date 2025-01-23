#include "Shader.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


std::unordered_map<std::string, std::shared_ptr<Shader>> Shader::shaderMap;

// 构造函数
Shader::Shader(const char* vertexPath, const char* fragmentPath)
    : vertexPath(convertPath(vertexPath)), fragmentPath(convertPath(fragmentPath)) {
    loadAndCompile();
}

// 刷新功能
bool Shader::Refresh() {
    std::cout << "Refreshing Shader from: [vert] " << vertexPath
              << " [frag] " << fragmentPath << std::endl;
    loadAndCompile();
    return isValid();
}

// 激活着色器程序
void Shader::use() const {
    glUseProgram(ID);
}

// 设置 Uniform 变量
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


// 加载并编译着色器
void Shader::loadAndCompile() {
    std::string vertexCode = loadShaderFile(vertexPath.c_str());
    std::string fragmentCode = loadShaderFile(fragmentPath.c_str());

    unsigned int vertex, fragment;
    compileShader(vertexCode.c_str(), GL_VERTEX_SHADER, vertex);
    compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER, fragment);

    // 创建和链接程序
    glDeleteProgram(ID); // 清理旧的程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    linkProgram();

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// 路径转换函数
std::string Shader::convertPath(const char* path) {
    std::string result = path;
    std::replace(result.begin(), result.end(), '\\', '/');
    return result;
}

// 加载着色器文件
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

// 编译单个着色器
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

// 链接着色器程序
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

// 检查有效性
bool Shader::isValid() const {
    return glIsProgram(ID);
}
