#ifndef COMMON_H
#define COMMON_H

// GUI ģ��
// ����ͼ���û��������ز���
#include "../Src/gui/Gui.h"
#include "../imgui/ImGuiFileDialog.h"

// ��Ⱦģ��
// ��װ�� OpenGL ���ù��ߺ���
#include "../Src/Render/Opengl_Utils.h"
// ��װ��ɫ���࣬���� OpenGL ��ɫ���ļ��ء�������ʹ��
#include "../Src/Render/Shader.h"
// ��װ������Ⱦ����Ⱦһ���������
#include "../Src/Render/Mesh.h"
//��װ��������������λ�ã������ӽǵ�
#include"../Src/Render/Camera.h"
//��װ��Ⱦ������
//#include"../Src/Render/Render.h"
//��װ��ɫ����
//#include"../Src/Render/Material.h"
//��װ��Դ��
#include"../Src/Render/Light//DirectionalLight.h"


// ����ģ��
// ��װ��MVP����
#include"../Src/Tool/MatrixManager.h"


//��Դģ��
// �������������������������ݲ��󶨵� OpenGL ���������
#include "../Src/Resources/Texture.h"
//�������࣬������һ��������Ķ������ݺ���������
#include "../Src/Resources/Model.h"

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




















