#ifndef COMMON_H
#define COMMON_H

// GUI ģ��
// ����ͼ���û��������ز���
#include "../Src/gui/gui.h"
#include "../imgui/ImGuiFileDialog.h"

// ��Ⱦģ��
// ��װ�� OpenGL ���ù��ߺ���
#include "../Src/Render/opengl_utils.h"
// ��װ��ɫ���࣬���� OpenGL ��ɫ���ļ��ء�������ʹ��
#include "../Src/Render/shader.h"
// ��װ������Ⱦ����Ⱦһ���������
#include "../Src/Render/mesh_render.h"
//��װ��������������λ�ã������ӽǵ�
#include"../Src/Render/Camera.h"
//��װ��Ⱦ������
//#include"../Src/Render/Render.h"
//��װ��ɫ����
#include"../Src/Render/material.h"
//��װ��Դ��
#include"../Src/Render/directionalLight.h"


// ����ģ��
// ��װ��MVP����
#include"../Src/Tool/MatrixManager.h"


//��Դģ��
// �������������������������ݲ��󶨵� OpenGL ���������
#include "../Src/Resources/textureLoader.h"
//�������࣬������һ��������Ķ������ݺ���������
#include "../Src/Resources/modelLoader.h.h"

//����ģ��
//�����������������̺��������
#include"../Src/Core/InputManager.h"

// GLM ��ѧ��
// ����ʸ�������������Լ��任����
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ��׼��
// ���������������ͷ�ļ��������ڵ��Ժ���־��ӡ
#include <iostream>

#endif // COMMON_H




















