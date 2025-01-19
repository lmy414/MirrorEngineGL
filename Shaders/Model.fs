#version 330 core

in vec2 TexCoords;           // 从顶点着色器传来的纹理坐标
in vec3 FragPos;             // 从顶点着色器传来的片段位置
in vec3 Normal;              // 从顶点着色器传来的法线

out vec4 FragColor;          // 最终输出的颜色

uniform sampler2D albedo;    // 漫反射纹理
uniform vec3 viewPos;        // 视点位置
uniform vec3 lightPos;       // 光源位置
uniform vec3 lightColor;     // 光源颜色

void main() {
    // 漫反射
    vec3 ambient = 0.1 * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 将纹理颜色与光照结合
    vec4 textureColor = texture(albedo, TexCoords);
    vec3 result = (ambient + diffuse) * textureColor.rgb;

    FragColor = vec4(result, 1.0);
}
