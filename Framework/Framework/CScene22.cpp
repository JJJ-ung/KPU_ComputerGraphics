#include "stdafx.h"
#include "CScene22.h"
#include "CShaderLoader.h"

CScene22::CScene22()
{
}

CScene22::~CScene22()
{
	Release();
}

HRESULT CScene22::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);


	return NOERROR;
}

GLuint CScene22::Update()
{
	return GLuint();
}

GLvoid CScene22::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, m_eMode);
	glEnable(GL_DEPTH_TEST);

	return GLvoid();
}

GLvoid CScene22::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene22::Input_KeyBoard(unsigned char key, int x, int y)
{

	return GLvoid();
}

GLvoid CScene22::Release()
{
	return GLvoid();
}

CScene22* CScene22::Create()
{
	CScene22* pInstance = new CScene22();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
