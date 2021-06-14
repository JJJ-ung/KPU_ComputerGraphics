#include "stdafx.h"
#include "CScene24.h"
#include "CShaderLoader.h"

CScene24::CScene24()
{
}

CScene24::~CScene24()
{
	Release();
}

HRESULT CScene24::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);


	return NOERROR;
}

GLuint CScene24::Update()
{
	return GLuint();
}

GLvoid CScene24::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, m_eMode);
	glEnable(GL_DEPTH_TEST);

	return GLvoid();
}

GLvoid CScene24::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene24::Input_KeyBoard(unsigned char key, int x, int y)
{

	return GLvoid();
}

GLvoid CScene24::Release()
{
	return GLvoid();
}

CScene24* CScene24::Create()
{
	CScene24* pInstance = new CScene24();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
