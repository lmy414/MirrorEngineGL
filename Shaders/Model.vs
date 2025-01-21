#version 330 core

layout(location = 0) in vec3 aPos;      // ����λ��
layout(location = 1) in vec3 aNormal;   // ���㷨��
layout(location = 2) in vec2 aTexCoords; // ��������

out vec2 TexCoords;    // ������������
out vec3 FragPos;      // ����Ƭ��λ��
out vec3 Normal;       // ���ݷ���

uniform mat4 model;    // ģ�;���
uniform mat4 view;     // ��ͼ����
uniform mat4 projection; // ͶӰ����

void main() {
    // ������λ��ת�����ü��ռ�
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // �����������ꡢƬ��λ�úͷ���
    TexCoords = aTexCoords;
    FragPos = vec3(model * vec4(aPos, 1.0));
}
