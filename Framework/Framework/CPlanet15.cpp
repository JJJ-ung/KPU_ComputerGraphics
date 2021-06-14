#include "stdafx.h"
#include "CPlanet15.h"
#include "CShape.h"
#include "CMesh.h"

CPlanet15::CPlanet15()
{
}

CPlanet15::~CPlanet15()
{
}

HRESULT CPlanet15::Initialize(float fRot, float fSpeed)
{
	m_fSpeed = fSpeed;

	m_pLine[PARENT] = Create_Circle(1.3f);
	m_pLine[PARENT]->Revolate(vec3(0.f, 0.f, 1.f), fRot);

	m_pMesh[PARENT] = CMesh::Create("../Mesh/LowSphere.obj", true, YELLOW);
	m_pMesh[PARENT]->Get_Position() = Circle_Position(1.3f, 0.f);
	m_pMesh[PARENT]->Get_Scale() = vec3(0.01f, 0.01f, 0.01f);
	m_pMesh[PARENT]->Revolate(vec3(0.f, 0.f, 1.f), fRot);

	m_pLine[CHILD] = Create_Circle(0.3f);
	m_pLine[CHILD]->Get_Scale() = vec3(100.f, 100.f, 100.f);
	m_pLine[CHILD]->Get_MatParent() = m_pMesh[PARENT]->Get_World();

	m_pMesh[CHILD] = CMesh::Create("../Mesh/LowSphere.obj", true, BLUE);
	m_pMesh[CHILD]->Get_Position() = Circle_Position(0.3f * 100.f, 0.f);
	m_pMesh[CHILD]->Get_Scale() = vec3(0.5f, 0.5f, 0.5f);
	m_pMesh[CHILD]->Get_MatParent() = m_pMesh[PARENT]->Get_World();

	return NOERROR;
}

GLuint CPlanet15::Update()
{
	m_pMesh[PARENT]->Revolate(vec3(0.f, 1.f, 0.f), -0.1f * m_fSpeed);
	m_pMesh[CHILD]->Revolate(vec3(0.f, 1.f, 0.f), -0.1f * m_fSpeed * 2);

	return GLuint();
}

GLvoid CPlanet15::Render()
{
	if(m_bWire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m_pLine[CHILD]->Get_MatParent() = m_pMesh[PARENT]->Get_World();
	m_pMesh[CHILD]->Get_MatParent() = m_pMesh[PARENT]->Get_World();

	for (int i = 0; i < END; ++i)
	{
		m_pLine[i]->Render();
		m_pMesh[i]->Render();
	}

	return GLvoid();
}

GLvoid CPlanet15::WireFrame()
{
	m_bWire = !m_bWire;

	return GLvoid();
}

GLvoid CPlanet15::Move(vec3 vDir)
{
	mat4 matMove = translate(mat4(1.f), vDir);
	m_pLine[PARENT]->Get_MatParent() *= matMove;
	m_pMesh[PARENT]->Get_MatParent() *= matMove;

	return GLvoid();
}

GLvoid CPlanet15::Rot(float fAngle)
{
	mat4 matRot = rotate(mat4(1.f), ToRadian(fAngle), vec3(0.f, 1.f, 0.f));
	m_pLine[PARENT]->Get_MatParent() *= matRot;
	m_pMesh[PARENT]->Get_MatParent() *= matRot;

	return GLvoid();
}

CShape* CPlanet15::Create_Circle(float fRadius)
{
	vector<vec3> vVert, vCol;

	for (GLint i = 0; i <= 360; ++i)
	{
		vVert.emplace_back(vec3(cosf(radians((float)i)) * fRadius, 0.f, sinf(radians((float)i)) * fRadius));
		vCol.emplace_back(vec3(1.f, 1.f, 1.f));
	}

	return CShape::Create(vVert, vCol, vVert.size(), GL_LINE_STRIP);
}

vec3 CPlanet15::Circle_Position(float fRadius, float fAngle)
{
	return vec3(cosf(radians(fAngle)) * fRadius, 0.f, sinf(radians(fAngle)) * fRadius);
}

CPlanet15* CPlanet15::Create(float fRot, float fSpeed)
{
	CPlanet15* pInstance = new CPlanet15;

	if (FAILED(pInstance->Initialize(fRot, fSpeed)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
