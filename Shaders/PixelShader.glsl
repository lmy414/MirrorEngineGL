#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 triangleColor;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);
    // 使用混合模式将两个纹理的颜色叠加
    FragColor.rgb *= triangleColor;  // 根据颜色调节三角形的颜色
}
