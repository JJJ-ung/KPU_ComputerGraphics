#include "stdafx.h"
#include "CScene20.h"
#include "CShaderLoader.h"

CScene20::CScene20()
{
}

CScene20::~CScene20()
{
	Release();
}

HRESULT CScene20::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);


	return NOERROR;
}

GLuint CScene20::Update()
{
	return GLuint();
}

GLvoid CScene20::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, m_eMode);
	glEnable(GL_DEPTH_TEST);

	return GLvoid();
}

GLvoid CScene20::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene20::Input_KeyBoard(unsigned char key, int x, int y)
{

	return GLvoid();
}

GLvoid CScene20::Release()
{
	return GLvoid();
}

CScene20* CScene20::Create()
{
	CScene20* pInstance = new CScene20();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
