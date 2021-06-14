#include "stdafx.h"
#include "CScene23.h"
#include "CShaderLoader.h"

CScene23::CScene23()
{
}

CScene23::~CScene23()
{
	Release();
}

HRESULT CScene23::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);


	return NOERROR;
}

GLuint CScene23::Update()
{
	return GLuint();
}

GLvoid CScene23::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, m_eMode);
	glEnable(GL_DEPTH_TEST);

	return GLvoid();
}

GLvoid CScene23::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene23::Input_KeyBoard(unsigned char key, int x, int y)
{

	return GLvoid();
}

GLvoid CScene23::Release()
{
	return GLvoid();
}

CScene23* CScene23::Create()
{
	CScene23* pInstance = new CScene23();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
