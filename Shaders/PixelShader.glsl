#version 330 core

out vec4 FragColor;  // �������ɫ

in vec3 ourColor;  // �������ɫ
in vec2 TexCoord;  // ������������꣨�������ǲ�ʹ������

uniform vec3 triangleColor;  // ���ڵ�����ɫ�� uniform ����

void main()
{
    // ֱ��ʹ�ô���� triangleColor ������������ɫ
    FragColor = vec4(triangleColor, 1.0f);  // ����������ֱ�������ɫ
}
