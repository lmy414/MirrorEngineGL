#version 330 core

in vec2 TexCoords;           // 从顶点着色器传来的纹理坐标
out vec4 FragColor;          // 最终输出的颜色

uniform sampler2D albedo_map;  // 无光照材质的纹理（基础颜色）

void main() {
    // 直接从纹理中获取颜色，并输出
    FragColor = texture(albedo_map, TexCoords);
}
