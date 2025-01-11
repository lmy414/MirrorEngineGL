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

    static constexpr float cubeVertices[8 * 8] = { // 8 �����㣬ÿ������ 8 ������
        // λ��             // ����          // ��������
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // 0: ���º�
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // 1: ���º�
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // 2: ���Ϻ�
     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // 3: ���Ϻ�
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // 4: ����ǰ
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // 5: ����ǰ
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // 6: ����ǰ
     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f  // 7: ����ǰ
       
    };

    static constexpr unsigned int cubeIndices[36] = { // 36 ������
        // ����
     0, 1, 2, 2, 3, 0,
     // ǰ��
     4, 5, 6, 6, 7, 4,
     // ����
     0, 4, 7, 7, 3, 0,
     // ����
     1, 5, 6, 6, 2, 1,
     // ����
     0, 1, 5, 5, 4, 0,
     // ����
     3, 2, 6, 6, 7, 3
    };
};

#endif // CUBE_H
#pragma once
