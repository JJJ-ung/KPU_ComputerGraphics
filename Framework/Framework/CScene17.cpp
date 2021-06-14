#include "stdafx.h"
#include "CScene17.h"
#include "CShaderLoader.h"
#include "CShape.h"
#include "CObject17.h"

CScene17::CScene17()
{
}

CScene17::~CScene17()
{
	Release();
}

HRESULT CScene17::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);

	m_pCamera = CCamera::Create(vec3(0.f, 3.f, 3.f), vec3(0.f, 0.5f, 0.f), vec3(0.f, 1.f, 0.f));

	vector<vec3> vert = { vec3(-1.f, 0.f, 1.f), vec3(1.f, 0.f, -1.f), vec3(-1.f, 0.f, -1.f),
											 vec3(-1.f, 0.f, 1.f), vec3(1.f, 0.f, 1.f), vec3(1.f, 0.f, -1.f) };
	vector<vec3> col = { vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f) };
	m_pTerrain = CShape::Create(vert, col, vert.size(), GL_TRIANGLES);

	m_pObject = CObject17::Create();

	return NOERROR;
}

GLuint CScene17::Update()
{
	if (m_bRot)
		m_pObject->Arm();

	return GLuint();
}

GLvoid CScene17::Render()
{
	glEnable(GL_DEPTH_TEST);

	m_pTerrain->Render();
	m_pObject->Render();

	//m_pCamera->Follow(m_pObject->Get_Position());
	//m_pCamera->Get_At() = m_pObject->Get_Position();
	m_pCamera->Render();

	return GLvoid();
}

GLvoid CScene17::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene17::Input_KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'b')
	{
		m_pObject->Move(vec3(-1.f, 0.f, 0.f), 0.01f);
		m_pCamera->Get_Eye() += vec3(-1.f, 0.f, 0.f) * 0.01f;
		m_pCamera->Get_At() += vec3(-1.f, 0.f, 0.f) * 0.01f;
	}
	if (key == 'B')
	{
		m_pObject->Move(vec3(1.f, 0.f, 0.f), 0.01f);
		m_pCamera->Get_Eye() += vec3(1.f, 0.f, 0.f) * 0.01f;
		m_pCamera->Get_At() += vec3(1.f, 0.f, 0.f) * 0.01f;
	}

	if (key == 'm')
		m_pObject->Rotate(0.3f);
	if (key == 'M')
		m_pObject->Rotate(-0.3f);

	if (key == 't' || key == 'T')
		m_bRot = true;
	if (key == 's' || key == 'S')
		m_bRot = false;

	if (key == 'z')
		m_pCamera->Move(vec3(0.f, 0.f, 1.f), 0.01f);
	if (key == 'Z')
		m_pCamera->Move(vec3(0.f, 0.f, -1.f), 0.01f);
	if (key == 'x')
		m_pCamera->Move(vec3(1.f, 0.f, 0.f), 0.01f);
	if (key == 'X')
		m_pCamera->Move(vec3(-1.f, 0.f, 0.f), 0.01f);
	if (key == 'r')
	{
		m_pCamera->Rotate(vec3(0.f, 1.f, 0.f), 5.f);
	}
	if (key == 'R')
		m_pCamera->Rotate(vec3(0.f, 1.f, 0.f), -5.f);

	if (key == 'c' || key == 'C')
	{
		SafeDelete(m_pObject);
		m_pObject = CObject17::Create();
	}

	if (key == 'q' || key == 'Q')
		exit(0);

	return GLvoid();
}

GLvoid CScene17::Release()
{
	return GLvoid();
}

CScene17* CScene17::Create()
{
	CScene17* pInstance = new CScene17();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
