#include "stdafx.h"
#include "CScene12.h"
#include "CShaderLoader.h"
#include "CShape.h"
#include "CCube.h"
#include "CMesh.h"

CScene12::CScene12()
{
}

CScene12::~CScene12()
{
	Release();
}

HRESULT CScene12::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);

	vector<vec3> vert = { vec3(-1.f, 0.f, 0.f), vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, -1.f, 0.f) };
	vector<vec3> col = { vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f) };
	m_pLine = CShape::Create(vert, col, 4, GL_LINES);

	m_pCube = CMesh::Create("../Mesh/Cube.obj");
	m_pCube->Scale(vec3(0.05f, 0.05f, 0.05f));
	m_pCube->RotateX(-30.f);
	m_pCube->RotateY(45.f);

	m_pPyramid = CMesh::Create("../Mesh/Pyramid.obj");
	m_pPyramid->Scale(vec3(0.025f, 0.025f, 0.025f));
	m_pCube->RotateX(-30.f);
	m_pCube->RotateY(45.f);

	glDisable(GL_CULL_FACE);

	return NOERROR;
}

GLuint CScene12::Update()
{
	if (m_iRot == 1)
	{
		// X양
		if (m_bCube)
			m_pCube->RotateX(1.f);
		else
			m_pPyramid->RotateX(1.f);
	}
	if (m_iRot == 2)
	{
		// X음
		if (m_bCube)
			m_pCube->RotateX(-1.f);
		else
			m_pPyramid->RotateX(-1.f);
	}
	if (m_iRot == 3)
	{
		// Y양
		if (m_bCube)
			m_pCube->RotateY(1.f);
		else
			m_pPyramid->RotateY(1.f);
	}
	if (m_iRot == 4)
	{
		// Y음
		if (m_bCube)
			m_pCube->RotateY(-1.f);
		else
			m_pPyramid->RotateY(-1.f);
	}

	return GLuint();
}

GLvoid CScene12::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, m_eMode);

	if (m_bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	m_pLine->Render();
	if(m_bCube)
		m_pCube->Render();
	else
		m_pPyramid->Render();

	return GLvoid();
}

GLvoid CScene12::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene12::Input_KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'c' || key == 'C')
		m_bCube = true;
	if (key == 'p' || key == 'P')
		m_bCube = false;
	if (key == 'h' || key == 'H')
		m_bDepth = !m_bDepth;
	if (key == 'x')
		m_iRot = 1;
	if (key == 'X')
		m_iRot = 2;
	if (key == 'y')
		m_iRot = 3;
	if (key == 'Y')
		m_iRot = 4;
	if (key == 'w' || key == 'W')
	{
		if (m_eMode == GL_FILL)
			m_eMode = GL_LINE;
		else if (m_eMode == GL_LINE)
			m_eMode = GL_FILL;
	}
	if (key == 's' || key == 'S')
	{
		m_iRot = -1;
		m_pCube->Get_Position() = vec3(0.f);
		m_pPyramid->Get_Position() = vec3(0.f);
	}

	return GLvoid();
}

GLvoid CScene12::Input_KeyBoardDir(int key, int x, int y)
{
	if (key == 100) 
	{//left direction key
		if (m_bCube)
			m_pCube->Move(vec3(-0.01f, 0.f, 0.f));
		else
			m_pPyramid->Move(vec3(-0.01f, 0.f, 0.f));
	}

	if (key == 102)
	{
		if (m_bCube)
			m_pCube->Move(vec3(0.01f, 0.f, 0.f));
		else
			m_pPyramid->Move(vec3(0.01f, 0.f, 0.f));
	}

	if (key == 101)
	{//forward
		if (m_bCube)
			m_pCube->Move(vec3(0.f, 0.01f, 0.f));
		else
			m_pPyramid->Move(vec3(0.f, 0.01f, 0.f));
	}

	if (key == 103)
	{//backward
		if (m_bCube)
			m_pCube->Move(vec3(0.f, -0.01f, 0.f));
		else
			m_pPyramid->Move(vec3(0.f, -0.01f, 0.f));
	}

	return GLvoid();
}

GLvoid CScene12::Release()
{
	SafeDelete(m_pLine);
	SafeDelete(m_pCube);

	return GLvoid();
}

CScene12* CScene12::Create()
{
	CScene12* pInstance = new CScene12();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
