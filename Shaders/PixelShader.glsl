#version 330 core

out vec4 FragColor;  // �����ɫ

in vec3 ourColor;  // �������ɫ
in vec2 TexCoord;  // �������������

uniform sampler2D texture1;  // ��һ������
uniform sampler2D texture2;  // �ڶ�������
uniform vec3 triangleColor;  // ���ڵ�����ɫ�� uniform ����

void main()
{
    // ��ȡ�����������ɫֵ
    vec4 tex1Color = texture(texture1, TexCoord);
    vec4 tex2Color = texture(texture2, TexCoord);

    // ��������������ɫ
    vec4 mixedColor = mix(tex1Color, tex2Color, 0.5f);  // 0.5f Ϊ��ϱ���

    // ���� triangleColor ���������յ���ɫ
    mixedColor.rgb *= triangleColor;

    // �����յĻ����ɫ���
    FragColor = mixedColor;
}
