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
#include <glm/gtc/type_ptr.hpp>  // 添加这个头文件
class Shader {
    
public:
    // 构造函数：加载并编译着色器
    Shader(const char* vertexPath, const char* fragmentPath);

    // 使用当前着色器程序
    void use();

    // 设置 uniform 类型的变量
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;

private:
    // 着色器程序 ID
    unsigned int ID;

    // 加载着色器代码文件
    std::string loadShaderFile(const char* path);

    // 编译着色器
    void compileShader(const char* code, GLenum shaderType, unsigned int& shaderID);

    // 链接着色器程序
    void linkProgram();
};

#endif // SHADER_H
