#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ȫ�ֱ�������
extern GLuint framebuffer;
extern GLuint textureID;
extern GLuint renderbuffer;

// ��������
void CreateOpenGLTexture(int width, int height);

#endif // RENDER_H
