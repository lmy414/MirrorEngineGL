#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// 全局变量声明
extern GLuint framebuffer;
extern GLuint textureID;
extern GLuint renderbuffer;

// 函数声明
void CreateOpenGLTexture(int width, int height);

#endif // RENDER_H
