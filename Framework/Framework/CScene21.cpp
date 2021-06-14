#include "stdafx.h"
#include "CScene21.h"
#include "CShaderLoader.h"

CScene21::CScene21()
{
}

CScene21::~CScene21()
{
	Release();
}

HRESULT CScene21::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);


	return NOERROR;
}

GLuint CScene21::Update()
{
	return GLuint();
}

GLvoid CScene21::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, m_eMode);
	glEnable(GL_DEPTH_TEST);

	return GLvoid();
}

GLvoid CScene21::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene21::Input_KeyBoard(unsigned char key, int x, int y)
{

	return GLvoid();
}

GLvoid CScene21::Release()
{
	return GLvoid();
}

CScene21* CScene21::Create()
{
	CScene21* pInstance = new CScene21();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
