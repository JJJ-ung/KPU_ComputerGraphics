#include "stdafx.h"
#include "CScene25.h"
#include "CShaderLoader.h"

CScene25::CScene25()
{
}

CScene25::~CScene25()
{
	Release();
}

HRESULT CScene25::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);


	return NOERROR;
}

GLuint CScene25::Update()
{
	return GLuint();
}

GLvoid CScene25::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, m_eMode);
	glEnable(GL_DEPTH_TEST);

	return GLvoid();
}

GLvoid CScene25::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene25::Input_KeyBoard(unsigned char key, int x, int y)
{

	return GLvoid();
}

GLvoid CScene25::Release()
{
	return GLvoid();
}

CScene25* CScene25::Create()
{
	CScene25* pInstance = new CScene25();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
