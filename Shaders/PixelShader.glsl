#version 330 core

out vec4 FragColor;

in vec3 FragPos;  // Ƭ����������
in vec3 fragNormal;   // Ƭ�η�����
in vec2 TexCoord; // ��������

// ��������
uniform vec3 diffuse;  // ��������ɫ

// �����Դ����
uniform vec3 Direction;  // ��Դ����
uniform vec3 LightColor;     // ��Դ��ɫ
uniform float Intensity; // ��Դǿ��

uniform vec3 viewPos;  // �ӵ�λ�ã������λ�ã�

void main()
{
    // ���㻷���⣨ambient������Դ��ɫ * ��������ɫ * ǿ�� * ����ϵ��
    vec3 ambient = LightColor * diffuse * 0.1f * Intensity;

    // ����������⣨diffuse��
    vec3 norm = normalize(fragNormal);  // ��һ��������
    vec3 lightDir = normalize(-Direction);  // ���㶨���Դ���򣨹��߷������෴�ģ�
    float diff = max(dot(norm, lightDir), 0.0f)*0.5 + 0.5;  // ��˼�������������
    vec3 diffuseLighting = LightColor * diffuse * diff * Intensity;

    // ���չ���Ч����ֻ���㻷������������
    vec3 result = ambient + diffuseLighting;

    // ��������Ƭ����ɫ
    FragColor = vec4(result, 1.0f);
}
