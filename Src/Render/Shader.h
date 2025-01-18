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
    unsigned int ID; // 着色器程序 ID
    
    //存储已经加载的所有着色器
    static std::unordered_map<std::string, std::shared_ptr<Shader>> shaderMap;

    // 构造函数
    Shader(const char* vertexPath, const char* fragmentPath);

    // 刷新功能
    bool Refresh();

    // 激活着色器程序
    void use() const;

    // 设置 Uniform 变量
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;

private:
    std::string vertexPath;    // 顶点着色器路径
    std::string fragmentPath;  // 片段着色器路径

    // 加载并编译着色器
    void loadAndCompile();

    // 路径转换函数
    static std::string convertPath(const char* path);

    // 加载着色器文件
    std::string loadShaderFile(const char* path) const;

    // 编译单个着色器
    void compileShader(const char* code, GLenum type, unsigned int& shaderID) const;

    // 链接着色器程序
    void linkProgram();

    // 检查有效性
    bool isValid() const;
};

#endif // SHADER_H
