#version 330 core

out vec4 FragColor;  // 输出的颜色

in vec3 ourColor;  // 输入的颜色
in vec2 TexCoord;  // 输入的纹理坐标（尽管我们不使用它）

uniform vec3 triangleColor;  // 用于调节颜色的 uniform 变量

void main()
{
    // 直接使用传入的 triangleColor 来设置最终颜色
    FragColor = vec4(triangleColor, 1.0f);  // 不考虑纹理，直接输出颜色
}
