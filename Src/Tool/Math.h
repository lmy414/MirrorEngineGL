#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Math
{
public:
    // 手动实现 clamp 函数
    template <typename T>
    static T clamp(T value, T minVal, T maxVal) {
        if (value < minVal) return minVal;   // 如果 value 小于 minVal，返回 minVal
        if (value > maxVal) return maxVal;   // 如果 value 大于 maxVal，返回 maxVal
        return value;                        // 否则返回原值
    }
};
