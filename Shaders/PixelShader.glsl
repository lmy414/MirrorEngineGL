#version 330 core
out vec4 FragColor;

uniform vec3 triangleColor;

void main() {
    FragColor = vec4(triangleColor * 0.5, 1.0); // 强制使用 triangleColor
}
