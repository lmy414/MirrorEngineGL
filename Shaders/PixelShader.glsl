#version 330 core

out vec4 FragColor;

in vec3 ourColor;  
in vec2 TexCoord; 

uniform vec3 diffuse;  // ��������ɫ

void main()
{
    FragColor = vec4(diffuse, 1.0f);  // ʹ�ô������������ɫ
}
