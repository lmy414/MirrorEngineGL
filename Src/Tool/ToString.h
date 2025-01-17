#pragma once
#include <string>
#include <sstream>
#include <glm/glm.hpp>  // 引入 glm::vec3 和 glm::mat4

class ToString
{
public:
    // 定义模板函数 toString，用于类型转换
    template <typename T>
    static std::string toString(const T& value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    // 为 glm::vec3 类型特化 toString
    static std::string toString(const glm::vec3& value) {
        std::stringstream ss;
        ss << "(" << value.x << ", " << value.y << ", " << value.z << ")";
        return ss.str();
    }

    // 为 glm::mat4 类型特化 toString
    static std::string toString(const glm::mat4& value) {
        std::stringstream ss;
        for (int i = 0; i < 4; ++i) {
            ss << "(";
            for (int j = 0; j < 4; ++j) {
                ss << value[i][j];
                if (j < 3) ss << ", ";
            }
            ss << ")";
            if (i < 3) ss << ", ";
        }
        return ss.str();
    }
};
