#version 330 core

layout(location = 0) in vec3 aPos;  // 顶点位置
layout(location = 1) in vec2 aTexCoords;  // 纹理坐标

out vec2 TexCoords;  // 输出纹理坐标

uniform mat4 model;   // 模型矩阵
uniform mat4 view;    // 视图矩阵
uniform mat4 projection;  // 投影矩阵

void main() {
    // 将顶点位置转换到裁剪空间
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // 将纹理坐标传递到片段着色器
    TexCoords = aTexCoords;
}
