#version 330 core

out vec4 FragColor;

in vec3 ourColor;  
in vec2 TexCoord; 

uniform vec3 diffuse;  // 漫反射颜色

void main()
{
    FragColor = vec4(diffuse, 1.0f);  // 使用传入的漫反射颜色
}
