#version 330 core

layout(location = 0) in vec3 aPos;      // 顶点位置
layout(location = 1) in vec3 aNormal;   // 顶点法线
layout(location = 2) in vec2 aTexCoords; // 纹理坐标

out vec2 TexCoords;    // 传递纹理坐标
out vec3 FragPos;      // 传递片段位置
out vec3 Normal;       // 传递法线

uniform mat4 model;    // 模型矩阵
uniform mat4 view;     // 视图矩阵
uniform mat4 projection; // 投影矩阵

void main() {
    // 将顶点位置转换到裁剪空间
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // 传递纹理坐标、片段位置和法线
    TexCoords = aTexCoords;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
}
