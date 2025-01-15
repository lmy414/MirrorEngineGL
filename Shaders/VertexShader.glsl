#version 330 core
layout(location = 0) in vec3 aPosition;   // ����λ��
layout(location = 1) in vec3 aNormal;     // ���㷨��
layout(location = 2) in vec2 aTexCoords;  // ��������

out vec3 fragNormal;  // �����ߴ��ݸ�Ƭ����ɫ��

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    fragNormal = aNormal;  // �����ߴ��ݸ�Ƭ����ɫ��
}
