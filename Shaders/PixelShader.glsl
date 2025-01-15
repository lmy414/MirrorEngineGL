#version 330 core

out vec4 FragColor;

in vec3 FragPos;  // 片段世界坐标
in vec3 fragNormal;   // 片段法向量
in vec2 TexCoord; // 纹理坐标

// 材质属性
uniform vec3 diffuse;  // 漫反射颜色

// 定向光源属性
uniform vec3 Direction;  // 光源方向
uniform vec3 LightColor;     // 光源颜色
uniform float Intensity; // 光源强度

uniform vec3 viewPos;  // 视点位置（摄像机位置）

void main()
{
    // 计算环境光（ambient）：光源颜色 * 漫反射颜色 * 强度 * 常数系数
    vec3 ambient = LightColor * diffuse * 0.1f * Intensity;

    // 计算漫反射光（diffuse）
    vec3 norm = normalize(fragNormal);  // 归一化法向量
    vec3 lightDir = normalize(-Direction);  // 计算定向光源方向（光线方向是相反的）
    float diff = max(dot(norm, lightDir), 0.0f)*0.5 + 0.5;  // 点乘计算漫反射因子
    vec3 diffuseLighting = LightColor * diffuse * diff * Intensity;

    // 最终光照效果：只计算环境光和漫反射光
    vec3 result = ambient + diffuseLighting;

    // 设置最终片段颜色
    FragColor = vec4(result, 1.0f);
}
