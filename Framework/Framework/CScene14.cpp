#include "stdafx.h"
#include "CScene14.h"
#include "CShaderLoader.h"
#include "CShape.h"
#include "CMesh.h"

CScene14::CScene14()
{
}

CScene14::~CScene14()
{
}

HRESULT CScene14::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);

	vector<vec3> vert = { vec3(-1.f, 0.f, 0.f), vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, -1.f, 0.f), vec3(0.f, 0.f, -1.f), vec3(0.f, 0.f, 1.f) };
	vector<vec3> col = { vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f) };
	m_pLine = CShape::Create(vert, col, vert.size(), GL_LINES);
	m_pLine->Rotate(vec3(1.f, 0.f, 0.f), -20.f);
	m_pLine->Rotate(vec3(0.f, 1.f, 0.f), 20.f);

	Create_Mesh(0, PYRAMID);
	Create_Mesh(1, CUBE);

	return NOERROR;
}

GLuint CScene14::Update()
{
	return GLuint();
}

GLvoid CScene14::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_pLine->Render();

	for (int i = 0; i < 2; ++i)
		m_arrMesh[i]->Render();

	return GLvoid();
}

GLvoid CScene14::Input_Mouse(int button, int state, int x, int y)
{
	return GLvoid();
}

GLvoid CScene14::Input_KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'x')
	{
		// 육면체 x축 양
		m_arrMesh[1]->RotateX(1.f);
	}
	else if (key == 'X')
	{
		// 육면체 x축 음
		m_arrMesh[1]->RotateX(-1.f);
	}
	else if (key == 'y')
	{
		// 피라미드 y축 양
		m_arrMesh[0]->RotateY(1.f);
	}
	else if (key == 'Y')
	{
		// 피라미드 y축 음
		m_arrMesh[0]->RotateY(-1.f);
	}
	else if (key == 'b')
	{
		// y축 공전 양
		m_pLine->Rotate(vec3(0.f, 1.f, 0.f), 1.f);
		m_arrMesh[0]->Revolate(vec3(0.f, 1.f, 0.f), 1.f);
		m_arrMesh[1]->Revolate(vec3(0.f, 1.f, 0.f), 1.f);
	}
	else if (key == 'B')
	{
		// y축 공전 음
		m_pLine->Rotate(vec3(0.f, 1.f, 0.f), -1.f);
		m_arrMesh[0]->Revolate(vec3(0.f, 1.f, 0.f), -1.f);
		m_arrMesh[1]->Revolate(vec3(0.f, 1.f, 0.f), -1.f);
	}
	else if (key == 'c' || key == 'C')
	{
		// 다른 도형으로 바꾸기
		Create_Mesh(0, TEAPOT);
		Create_Mesh(1, SPHERE);
	}
	else if (key == 's' || key == 'S')
	{
		// 회전 멈추기
	}

	return GLvoid();
}

GLvoid CScene14::Input_KeyBoardDir(int key, int x, int y)
{
	return GLvoid();
}

GLvoid CScene14::Create_Mesh(int iIndex, TYPE eType)
{
	SafeDelete(m_arrMesh[iIndex]);

	switch (eType)
	{
	case CScene14::CUBE:
		m_arrMesh[iIndex] = CMesh::Create("../Mesh/Cube.obj");
		m_arrMesh[iIndex]->Get_Scale() = vec3(0.025f, 0.025f, 0.025f);
		m_arrMesh[iIndex]->Get_Position() = vec3(-0.5f + iIndex, 0.f, 0.f);
		m_arrMesh[iIndex]->Revolate(vec3(1.f, 0.f, 0.f), -20.f);
		m_arrMesh[iIndex]->Revolate(vec3(0.f, 1.f, 0.f), 20.f);
		break;
	case CScene14::CYLINDER:
		m_arrMesh[iIndex] = CMesh::Create("../Mesh/cylinder.obj");
		m_arrMesh[iIndex]->Get_Scale() = vec3(0.025f, 0.025f, 0.025f);
		m_arrMesh[iIndex]->Get_Position() = vec3(-0.5f + iIndex, 0.f, 0.f);
		m_arrMesh[iIndex]->Revolate(vec3(1.f, 0.f, 0.f), -20.f);
		m_arrMesh[iIndex]->Revolate(vec3(0.f, 1.f, 0.f), 20.f);
		break;
	case CScene14::SPHERE:
		m_arrMesh[iIndex] = CMesh::Create("../Mesh/LowSphere.obj");
		m_arrMesh[iIndex]->Get_Scale() = vec3(0.0125f, 0.0125f, 0.0125f);
		m_arrMesh[iIndex]->Get_Position() = vec3(-0.5f + iIndex, 0.f, 0.f);
		m_arrMesh[iIndex]->Revolate(vec3(1.f, 0.f, 0.f), -20.f);
		m_arrMesh[iIndex]->Revolate(vec3(0.f, 1.f, 0.f), 20.f);
		break;
	case CScene14::PYRAMID:
		m_arrMesh[iIndex] = CMesh::Create("../Mesh/Pyramid.obj");
		m_arrMesh[iIndex]->Get_Scale() = vec3(0.015f, 0.015f, 0.015f);
		m_arrMesh[iIndex]->Get_Position() = vec3(-0.5f + iIndex, 0.f, 0.f);
		m_arrMesh[iIndex]->Revolate(vec3(1.f, 0.f, 0.f), -20.f);
		m_arrMesh[iIndex]->Revolate(vec3(0.f, 1.f, 0.f), 20.f);
		break;
	case CScene14::TEAPOT:
		m_arrMesh[iIndex] = CMesh::Create("../Mesh/Teapot.obj");
		m_arrMesh[iIndex]->Get_Scale() = vec3(0.025f, 0.025f, 0.025f);
		m_arrMesh[iIndex]->Get_Position() = vec3(-0.5f + iIndex, 0.f, 0.f);
		m_arrMesh[iIndex]->Revolate(vec3(1.f, 0.f, 0.f), -20.f);
		m_arrMesh[iIndex]->Revolate(vec3(0.f, 1.f, 0.f), 20.f);
		break;
	default:
		break;
	}

	return GLvoid();
}

GLvoid CScene14::Release()
{
	return GLvoid();
}

CScene14* CScene14::Create()
{
	CScene14* pInstance = new CScene14();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
