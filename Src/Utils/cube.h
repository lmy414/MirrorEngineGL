#ifndef CUBE_H
#define CUBE_H

#include <vector>

class Cube {
public:
    Cube() {
        vertices.assign(std::begin(cubeVertices), std::end(cubeVertices));
        indices.assign(std::begin(cubeIndices), std::end(cubeIndices));
    }

    const std::vector<float>& GetVertices() const {
        return vertices;
    }

    const std::vector<unsigned int>& GetIndices() const {
        return indices;
    }

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    static constexpr float cubeVertices[8 * 8] = { // 8 个顶点，每个顶点 8 个属性
        // 位置             // 法线          // 纹理坐标
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // 0: 左下后
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // 1: 右下后
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // 2: 右上后
     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // 3: 左上后
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // 4: 左下前
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // 5: 右下前
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // 6: 右上前
     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f  // 7: 左上前
       
    };

    static constexpr unsigned int cubeIndices[36] = { // 36 个索引
        // 后面
     0, 1, 2, 2, 3, 0,
     // 前面
     4, 5, 6, 6, 7, 4,
     // 左面
     0, 4, 7, 7, 3, 0,
     // 右面
     1, 5, 6, 6, 2, 1,
     // 底面
     0, 1, 5, 5, 4, 0,
     // 顶面
     3, 2, 6, 6, 7, 3
    };
};

#endif // CUBE_H
#pragma once
