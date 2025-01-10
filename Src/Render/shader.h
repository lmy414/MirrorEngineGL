#ifndef SHADER_H
#define SHADER_H
#define GLFW_INCLUDE_NONE // 避免 GLFW 自动包含 OpenGL 的头文件

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID; // 着色器程序 ID

    Shader(const char* vertexPath, const char* fragmentPath); // 构造函数
    void use(); // 激活着色器程序

    // uniform 工具函数
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};

#endif
