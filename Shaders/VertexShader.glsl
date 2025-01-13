#version 330 core

// ���붥�����ԣ�λ�ú���������
layout (location = 0) in vec3 aPos;       // λ��
layout (location = 2) in vec2 aTexCoord;  // ��������

// ������������ڴ��ݵ�Ƭ����ɫ��
out vec2 TexCoord;  // ��������

// �任����
uniform mat4 model;       // ģ�;���
uniform mat4 view;        // ��ͼ����
uniform mat4 projection;  // ͶӰ����

void main()
{
    // �������յĶ���λ�ã�ģ�ͱ任 -> ��ͼ�任 -> ͶӰ�任��
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    
    // ���������괫�ݸ�Ƭ����ɫ��
    TexCoord = aTexCoord;
}
