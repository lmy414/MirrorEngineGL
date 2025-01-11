#version 330 core

out vec4 FragColor;  // 输出颜色

in vec3 ourColor;  // 输入的颜色
in vec2 TexCoord;  // 输入的纹理坐标

uniform sampler2D texture1;  // 第一个纹理
uniform sampler2D texture2;  // 第二个纹理
uniform vec3 triangleColor;  // 用于调节颜色的 uniform 变量

void main()
{
    // 获取两个纹理的颜色值
    vec4 tex1Color = texture(texture1, TexCoord);
    vec4 tex2Color = texture(texture2, TexCoord);

    // 混合两个纹理的颜色
    vec4 mixedColor = mix(tex1Color, tex2Color, 0.5f);  // 0.5f 为混合比例

    // 根据 triangleColor 来调整最终的颜色
    mixedColor.rgb *= triangleColor;

    // 将最终的混合颜色输出
    FragColor = mixedColor;
}
