#version 330 core

layout (location = 0) in vec3 aPos; // ����λ��
void main() {
    gl_Position = vec4(aPos, 1.0); // ������λ��ֱ�Ӵ��ݵ��ü�����
}
