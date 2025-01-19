#version 330 core

layout(location = 0) in vec3 aPos;  // ����λ��
layout(location = 1) in vec2 aTexCoords;  // ��������

out vec2 TexCoords;  // �����������

uniform mat4 model;   // ģ�;���
uniform mat4 view;    // ��ͼ����
uniform mat4 projection;  // ͶӰ����

void main() {
    // ������λ��ת�����ü��ռ�
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // ���������괫�ݵ�Ƭ����ɫ��
    TexCoords = aTexCoords;
}
