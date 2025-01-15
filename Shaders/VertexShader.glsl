#version 330 core
layout(location = 0) in vec3 aPosition;   // 顶点位置
layout(location = 1) in vec3 aNormal;     // 顶点法线
layout(location = 2) in vec2 aTexCoords;  // 纹理坐标

out vec3 fragNormal;  // 将法线传递给片段着色器

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    fragNormal = aNormal;  // 将法线传递给片段着色器
}
