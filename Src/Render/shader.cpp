#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = loadShaderFile(vertexPath);
    std::string fragmentCode = loadShaderFile(fragmentPath);

    unsigned int vertex, fragment;
    compileShader(vertexCode.c_str(), GL_VERTEX_SHADER, vertex);
    compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER, fragment);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    linkProgram();

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::string Shader::loadShaderFile(const char* path) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path);
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    return shaderStream.str();
}

void Shader::compileShader(const char* code, GLenum shaderType, unsigned int& shaderID) {
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") 
                  << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::linkProgram() {
    int success;
    char infoLog[512];

    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        int uniformCount;
        glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &uniformCount);
        char uniformName[256];
        for (int i = 0; i < uniformCount; ++i) {
            GLsizei length;
            glGetActiveUniform(ID, i, sizeof(uniformName), &length, nullptr, nullptr, uniformName);
            std::cout << "Active Uniform: " << uniformName << std::endl;
        }
    }
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}
void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}