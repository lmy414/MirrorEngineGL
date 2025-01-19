#version 330 core

in vec2 TexCoords;           // �Ӷ�����ɫ����������������
in vec3 FragPos;             // �Ӷ�����ɫ��������Ƭ��λ��
in vec3 Normal;              // �Ӷ�����ɫ�������ķ���

out vec4 FragColor;          // �����������ɫ

uniform sampler2D albedo;    // ����������
uniform vec3 viewPos;        // �ӵ�λ��
uniform vec3 lightPos;       // ��Դλ��
uniform vec3 lightColor;     // ��Դ��ɫ

void main() {
    // ������
    vec3 ambient = 0.1 * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // ��������ɫ����ս��
    vec4 textureColor = texture(albedo, TexCoords);
    vec3 result = (ambient + diffuse) * textureColor.rgb;

    FragColor = vec4(result, 1.0);
}
