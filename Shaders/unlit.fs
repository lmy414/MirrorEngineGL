#version 330 core

in vec2 TexCoords;           // �Ӷ�����ɫ����������������
out vec4 FragColor;          // �����������ɫ

uniform sampler2D albedo_map;  // �޹��ղ��ʵ�����������ɫ��

void main() {
    // ֱ�Ӵ������л�ȡ��ɫ�������
    FragColor = texture(albedo_map, TexCoords);
}
