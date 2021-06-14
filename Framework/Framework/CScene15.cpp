#include "stdafx.h"
#include "CScene15.h"
#include "CMesh.h"
#include "CShaderLoader.h"

CScene15::CScene15()
{
}

CScene15::~CScene15()
{
	Release();
}

HRESULT CScene15::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);

	m_pCamera = CCamera::Create(vec3(0.f, 0.5f, 5.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));

	m_pPlanet[0] = CPlanet15::Create(0.f, 3.f);
	m_pPlanet[1] = CPlanet15::Create(45.f, 5.f);
	m_pPlanet[2] = CPlanet15::Create(-45.f, 10.f);

	m_pMain = CMesh::Create("../Mesh/LowSphere.obj", true, BLUE);
	m_pMain->Get_Scale() = vec3(0.03f, 0.03f, 0.03f);

	return NOERROR;
}

GLuint CScene15::Update()
{
	for(int i = 0; i < 3; ++i)
		m_pPlanet[i]->Update();

	return GLuint();
}

GLvoid CScene15::Render()
{
	glEnable(GL_DEPTH_TEST);

	m_pMain->Render();

	for (int i = 0; i < 3; ++i)
		m_pPlanet[i]->Render();

	m_pCamera->Render();

	return GLvoid();
}

GLvoid CScene15::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene15::Input_KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'm' || key == 'M')
	{
		for (int i = 0; i < 3; ++i)
			m_pPlanet[i]->WireFrame();
	}

	if (key == 'z' || key == 'Z')
		m_pCamera->Move(vec3(0.f, 0.f, -1.f), -0.01f);

	if (key == 'x' || key == 'X')
		m_pCamera->Move(vec3(0.f, 0.f, 1.f), -0.01f);

	if (key == 'w' || key == 'W')
		m_pCamera->Move(vec3(0.f, 1.f, 0.f), 0.01f);

	if (key == 's' || key == 'S')
		m_pCamera->Move(vec3(0.f, -1.f, 0.f), 0.01f);

	if (key == 'a' || key == 'A')
		m_pCamera->Move(vec3(-1.f, 0.f, 0.f), 0.01f);

	if (key == 'd' || key == 'D')
		m_pCamera->Move(vec3(1.f, 0.f, 0.f), 0.01f);

	if (key == 'y')
	{
		for (int i = 0; i < 3; ++i)
			m_pPlanet[i]->Rot(3.f);
	}
	
	if (key == 'Y')
	{
		for (int i = 0; i < 3; ++i)
			m_pPlanet[i]->Rot(-3.f);
	}

	return GLvoid();
}

GLvoid CScene15::Release()
{
	return GLvoid();
}

CScene15* CScene15::Create()
{
	CScene15* pInstance = new CScene15();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
