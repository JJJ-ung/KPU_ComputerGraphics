#include "stdafx.h"
#include "CScene13.h"
#include "CShaderLoader.h"
#include "CShape.h"
#include "CMesh.h"

CScene13::CScene13()
{
}

CScene13::~CScene13()
{
	Release();
}

HRESULT CScene13::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);

	vector<vec3> vert = { vec3(-1.f, 0.f, 0.f), vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, -1.f, 0.f) };
	vector<vec3> col = { vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f) };
	m_pLine = CShape::Create(vert, col, 4, GL_LINES);

	if (FAILED(Create_SinSpline()))
		return E_FAIL;

	if (FAILED(Create_SpringSpline()))
		return E_FAIL;

	if (FAILED(Create_ZigZagSpline()))
		return E_FAIL;

	vector<vec3> vert2 = { vec3(-0.1f, -0.1f, 0.1f), vec3(0.f, 0.1f, 0.1f), vec3(0.1f, -0.1f, 0.1f) };
	vector<vec3> col2 = { vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f) };
	m_pShape = CShape::Create(vert2, col2, vert2.size());
	m_pShape->Get_Position() = vec3(-1.f, 0.f, 0.f);

	m_pMesh = CMesh::Create("../Mesh/Cube.obj");
	m_pMesh->Scale(vec3(0.015f, 0.015f, 0.015f));
	m_pMesh->RotateX(-30.f);
	m_pMesh->RotateY(45.f);
	m_pMesh->Get_Position() = vec3(-1.f, 0.f, 0.f);

	glEnable(GL_DEPTH_TEST);

	return NOERROR;
}

GLuint CScene13::Update()
{
	if (m_iAct == 1)
	{
		vec3 meshpos = vec3(0.f), tripos = vec3(0.f);
		if (m_iCurr == 1)
		{
			// 사인
			m_fMeshAngle += 0.4f;
			m_fShapeAngle += 0.7f;
			meshpos = vec3((m_fMeshAngle - 360.f) / 360.f, sinf(ToRadian(m_fMeshAngle)), 0.f);
			tripos = vec3((m_fShapeAngle - 360.f) / 360.f, sinf(ToRadian(m_fShapeAngle)), 0.f);
			m_pShape->Move_Position(tripos);
			m_pMesh->Move_Position(meshpos);
		}
		else if (m_iCurr == 2)
		{
			// 스프링
			m_fMeshAngle += 0.4f;
			m_fShapeAngle += 0.7f;
			m_pMesh->Get_Position() = SpringSpline(m_fMeshAngle, m_fMeshAdd);
			m_pShape->Get_Position() = SpringSpline(m_fShapeAngle, m_fShapeAdd);
			m_fMeshAdd += 0.005f * 0.4f;
			m_fShapeAdd += 0.005f * 0.7f;
		}
		else if (m_iCurr == 3)
		{
			// 지그재그
			if (m_pShape->Get_Position().x < -0.75f && m_pShape->Get_Position().x >= -1.f)
				m_pShape->Move(vec3(0.003f, 0.003f * 4, 0.f));
			else if (m_pShape->Get_Position().x < -0.25f && m_pShape->Get_Position().x >= -0.75f)
				m_pShape->Move(vec3(0.003f, -0.003f * 4, 0.f));
			else if (m_pShape->Get_Position().x < 0.25f && m_pShape->Get_Position().x >= -0.25f)
				m_pShape->Move(vec3(0.003f, 0.003f * 4, 0.f));
			else if (m_pShape->Get_Position().x < 0.75f && m_pShape->Get_Position().x >= 0.25f)
				m_pShape->Move(vec3(0.003f, -0.003f * 4, 0.f));
			else
				m_pShape->Move(vec3(0.003f, 0.003f * 4, 0.f));

			if (m_pMesh->Get_Position().x < -0.75f && m_pMesh->Get_Position().x >= -1.f)
				m_pMesh->Move(vec3(0.0015f, 0.0015f * 4, 0.f));
			else if (m_pMesh->Get_Position().x < -0.25f && m_pMesh->Get_Position().x >= -0.75f)
				m_pMesh->Move(vec3(0.0015f, -0.0015f * 4, 0.f));
			else if (m_pMesh->Get_Position().x < 0.25f && m_pMesh->Get_Position().x >= -0.25f)
				m_pMesh->Move(vec3(0.0015f, 0.0015f * 4, 0.f));
			else if (m_pMesh->Get_Position().x < 0.75f && m_pMesh->Get_Position().x >= 0.25f)
				m_pMesh->Move(vec3(0.0015f, -0.0015f * 4, 0.f));
			else
				m_pMesh->Move(vec3(0.0015f, 0.0015f * 4, 0.f));
		}
	}
	if (m_iAct == 2)
	{
		vec3 meshpos = vec3(0.f), tripos = vec3(0.f);
		if (m_iCurr == 1)
		{
			// 사인
			m_fMeshAngle += 0.4f;
			m_fShapeAngle += 0.7f;
			meshpos = vec3((m_fMeshAngle - 360.f) / 360.f, sinf(ToRadian(m_fMeshAngle)), 0.f);
			tripos = vec3((m_fShapeAngle - 360.f) / 360.f, sinf(ToRadian(m_fShapeAngle)), 0.f);
			m_pShape->Move_Position(tripos);
			m_pMesh->Move_Position(meshpos);
		}
		else if (m_iCurr == 2)
		{
			// 스프링
			m_fMeshAngle += 0.4f;
			m_fShapeAngle += 0.7f;
			m_pMesh->Get_Position() = SpringSpline(m_fMeshAngle, m_fMeshAdd);
			m_pShape->Get_Position() = SpringSpline(m_fShapeAngle, m_fShapeAdd);
			m_fMeshAdd += 0.005f * 0.4f;
			m_fShapeAdd += 0.005f * 0.7f;
		}
		else if (m_iCurr == 3)
		{
			// 지그재그
			if (m_pShape->Get_Position().x < -0.75f && m_pShape->Get_Position().x >= -1.f)
				m_pShape->Move(vec3(0.003f, 0.003f * 4, 0.f));
			else if (m_pShape->Get_Position().x < -0.25f && m_pShape->Get_Position().x >= -0.75f)
				m_pShape->Move(vec3(0.003f, -0.003f * 4, 0.f));
			else if (m_pShape->Get_Position().x < 0.25f && m_pShape->Get_Position().x >= -0.25f)
				m_pShape->Move(vec3(0.003f, 0.003f * 4, 0.f));
			else if (m_pShape->Get_Position().x < 0.75f && m_pShape->Get_Position().x >= 0.25f)
				m_pShape->Move(vec3(0.003f, -0.003f * 4, 0.f));
			else
				m_pShape->Move(vec3(0.003f, 0.003f * 4, 0.f));

			if (m_pMesh->Get_Position().x < -0.75f && m_pMesh->Get_Position().x >= -1.f)
				m_pMesh->Move(vec3(0.0015f, 0.0015f * 4, 0.f));
			else if (m_pMesh->Get_Position().x < -0.25f && m_pMesh->Get_Position().x >= -0.75f)
				m_pMesh->Move(vec3(0.0015f, -0.0015f * 4, 0.f));
			else if (m_pMesh->Get_Position().x < 0.25f && m_pMesh->Get_Position().x >= -0.25f)
				m_pMesh->Move(vec3(0.0015f, 0.0015f * 4, 0.f));
			else if (m_pMesh->Get_Position().x < 0.75f && m_pMesh->Get_Position().x >= 0.25f)
				m_pMesh->Move(vec3(0.0015f, -0.0015f * 4, 0.f));
			else
				m_pMesh->Move(vec3(0.0015f, 0.0015f * 4, 0.f));
		}

		m_fMeshSize += m_fMeshSizeAdd;
		m_fTriSize += m_fTriSizeAdd;
		if (m_fTriSize > 2.f)
			m_fTriSizeAdd *= -1.f;
		if (m_fTriSize < 0.1f)
			m_fTriSizeAdd *= -1.f;
		if (m_fMeshSize > 0.03f)
			m_fMeshSizeAdd *= -1.f;
		if (m_fMeshSize < 0.005)
			m_fMeshSizeAdd *= -1.f;
		m_pShape->Get_Scale() = vec3(m_fTriSize);
		m_pMesh->Get_Scale() = vec3(m_fMeshSize);
	}
	if (m_iAct == 3)
	{
		m_pShape->Revolate(vec3(0.f, 1.f, 0.f), ToRadian(100.f));
		m_pMesh->Revolate(vec3(0.f, 1.f, 0.f), ToRadian(100.f));
		switch (m_iCurr)
		{
		case 1:
			m_pSin->RotateY(ToRadian(100.f));
			break;
		case 2:
			m_pSpring->RotateY(ToRadian(100.f));
			break;
		case 3:
			m_pZigZag->RotateY(ToRadian(100.f));
			break;
		default:
			break;
		}
	}

	return GLuint();
}

GLvoid CScene13::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	m_pLine->Render();

	switch (m_iCurr)
	{
	case 1:
		m_pSin->Render();
		break;
	case 2:
		m_pSpring->Render();
		break;
	case 3:
		m_pZigZag->Render();
		break;
	default:
		break;
	}

	m_pShape->Render();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_pMesh->Render();

	return GLvoid();
}

GLvoid CScene13::Input_Mouse(int button, int state, int x, int y)
{
	return GLvoid();
}

GLvoid CScene13::Input_KeyBoard(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		m_iCurr = 1;
		Reset();
	}
	if (key == '2')
	{
		m_iCurr = 2;
		Reset();
		m_pShape->Get_Position() = SpringSpline(0.f, m_fShapeAdd);
		m_pMesh->Get_Position() = SpringSpline(0.f, m_fMeshAdd);
	}
	if (key == '3')
	{
		m_iCurr = 3;
		Reset();
	}

	if (key == 't')
		m_iAct = 1;
	if (key == 's')
		m_iAct = 2;
	if (key == 'r')
		m_iAct = 3;
	if (key == 'c')
		Reset();

	return GLvoid();
}

GLvoid CScene13::Input_KeyBoardDir(int key, int x, int y)
{
	return GLvoid();
}

HRESULT CScene13::Create_SinSpline()
{
	vector<vec3> vSpline, vCol;

	for (GLint i = 0; i < 720; ++i)
	{
		vSpline.emplace_back(vec3(((i) - 360.f) / 360.f, sinf(ToRadian((float)i)), 0.f));
		vCol.emplace_back(vec3(1.f, 1.f, 1.f));
	}

	m_pSin = CShape::Create(vSpline, vCol, vSpline.size(), GL_LINE_STRIP);

	return NOERROR;
}

HRESULT CScene13::Create_SpringSpline()
{
	vector<vec3> vSpline, vCol;

	float fAdd = -0.8f;

	for (GLint i = 0; i < 540; ++i)
	{
		float fSin = sin(radians(i * 3.f));
		float fCos = cos(radians(i * 3.f));
		vSpline.emplace_back(vec3(fCos * 0.5f + fAdd, fSin * 0.5f, 0.f));
		vCol.emplace_back(vec3(1.f, 1.f, 1.f));
		fAdd += 0.005f;
	}

	m_pSpring = CShape::Create(vSpline, vCol, vSpline.size(), GL_LINE_STRIP);

	return NOERROR;
}

HRESULT CScene13::Create_ZigZagSpline()
{
	vector<vec3> vSpline, vCol;

	vSpline.emplace_back(vec3(-1.f, 0.f, 0.f));
	vCol.emplace_back(vec3(1.f, 1.f, 1.f));
	vSpline.emplace_back(vec3(-0.75f, 1.f, 0.f));
	vCol.emplace_back(vec3(1.f, 1.f, 1.f));
	vSpline.emplace_back(vec3(-0.5f, 0.f, 0.f));
	vCol.emplace_back(vec3(1.f, 1.f, 1.f));
	vSpline.emplace_back(vec3(-0.25f, -1.f, 0.f));
	vCol.emplace_back(vec3(1.f, 1.f, 1.f));
	vSpline.emplace_back(vec3(0.25f, 1.f, 0.f));
	vCol.emplace_back(vec3(1.f, 1.f, 1.f));
	vSpline.emplace_back(vec3(0.75f, -1.f, 0.f));
	vCol.emplace_back(vec3(1.f, 1.f, 1.f));
	vSpline.emplace_back(vec3(1.f, 0.f, 0.f));
	vCol.emplace_back(vec3(1.f, 1.f, 1.f));

	m_pZigZag = CShape::Create(vSpline, vCol, vSpline.size(), GL_LINE_STRIP);

	return NOERROR;
}

vec3 CScene13::SpringSpline(float fAngle, float fAdd)
{
	float fSin = sin(radians(fAngle * 3.f));
	float fCos = cos(radians(fAngle * 3.f));
	vec3 Output = vec3(fCos * 0.5f + fAdd, fSin * 0.5f, 0.f);

	return Output;
}

GLvoid CScene13::Reset()
{
	m_iAct = -1;
	m_fShapeAngle = 0.f;
	m_fMeshAngle = 0.f;
	m_fMeshRot = 0.f;
	m_fShapeRot = 0.f;

	m_fMeshAdd = -0.8f;
	m_fShapeAdd = -0.8f;

	Create_SinSpline();
	Create_SpringSpline();
	Create_ZigZagSpline();

	vector<vec3> vert2 = { vec3(-0.1f, -0.1f, 0.1f), vec3(0.f, 0.1f, 0.1f), vec3(0.1f, -0.1f, 0.1f) };
	vector<vec3> col2 = { vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f) };
	m_pShape = CShape::Create(vert2, col2, vert2.size());
	m_pShape->Get_Position() = vec3(-1.f, 0.f, 0.f);

	m_pMesh = CMesh::Create("../Mesh/Cube.obj");
	m_pMesh->Scale(vec3(0.015f, 0.015f, 0.015f));
	m_pMesh->RotateX(-30.f);
	m_pMesh->RotateY(45.f);
	m_pMesh->Get_Position() = vec3(-1.f, 0.f, 0.f);
}

GLvoid CScene13::Release()
{
	return GLvoid();
}

CScene13* CScene13::Create()
{
	CScene13* pInstance = new CScene13();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
