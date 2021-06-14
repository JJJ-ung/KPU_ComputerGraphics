#include "stdafx.h"
#include "CScene18.h"
#include "CShaderLoader.h"

CScene18::CScene18()
{
}

CScene18::~CScene18()
{
	Release();
}

HRESULT CScene18::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);


	return NOERROR;
}

GLuint CScene18::Update()
{
	return GLuint();
}

GLvoid CScene18::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, m_eMode);
	glEnable(GL_DEPTH_TEST);

	return GLvoid();
}

GLvoid CScene18::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene18::Input_KeyBoard(unsigned char key, int x, int y)
{

	return GLvoid();
}

GLvoid CScene18::Release()
{
	return GLvoid();
}

CScene18* CScene18::Create()
{
	CScene18* pInstance = new CScene18();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
