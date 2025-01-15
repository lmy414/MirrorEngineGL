#ifndef SHADER_H
#define SHADER_H
#define GLFW_INCLUDE_NONE // ???? GLFW ??????? OpenGL ??????

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID; // ????????? ID

    Shader(const char* vertexPath, const char* fragmentPath); // ??????
    void use(); // ?????????????

    // uniform ???????
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};

#endif
