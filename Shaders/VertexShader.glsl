#version 330 core

// 输入顶点属性：位置和纹理坐标
layout (location = 0) in vec3 aPos;       // 位置
layout (location = 2) in vec2 aTexCoord;  // 纹理坐标

// 输出变量，用于传递到片段着色器
out vec2 TexCoord;  // 纹理坐标

// 变换矩阵
uniform mat4 model;       // 模型矩阵
uniform mat4 view;        // 视图矩阵
uniform mat4 projection;  // 投影矩阵

void main()
{
    // 计算最终的顶点位置（模型变换 -> 视图变换 -> 投影变换）
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    
    // 将纹理坐标传递给片段着色器
    TexCoord = aTexCoord;
}
