#include "stdafx.h"
#include "CScene19.h"
#include "CShaderLoader.h"

CScene19::CScene19()
{
}

CScene19::~CScene19()
{
	Release();
}

HRESULT CScene19::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);


	return NOERROR;
}

GLuint CScene19::Update()
{
	return GLuint();
}

GLvoid CScene19::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, m_eMode);
	glEnable(GL_DEPTH_TEST);

	return GLvoid();
}

GLvoid CScene19::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene19::Input_KeyBoard(unsigned char key, int x, int y)
{

	return GLvoid();
}

GLvoid CScene19::Release()
{
	return GLvoid();
}

CScene19* CScene19::Create()
{
	CScene19* pInstance = new CScene19();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
