#include "stdafx.h"
#include "CObject17.h"
#include "CMesh.h"

CObject17::CObject17()
{
}

CObject17::~CObject17()
{
}

HRESULT CObject17::Initialize()
{
	m_pBase = CMesh::Create("../Mesh/Cube0.obj", true, vec3(1.f, 0.f, 0.f));
	m_pBase->Get_Scale() = vec3(0.5f, 0.25f, 0.5f);

	m_pBody = CMesh::Create("../Mesh/Cube0.obj", true, vec3(1.f, 1.f, 0.f));
	m_pBody->Get_Scale() = vec3(0.7f, 0.7f, 0.7f);
	m_pBody->Get_Position() = vec3(0.f, 1.f, 0.f);
	m_pBody->Get_MatParent() = m_pBase->Get_World();

	m_pArmL = CMesh::Create("../Mesh/Cube0.obj", true, vec3(0.f, 1.f, 1.f));
	m_pArmL->Get_Scale() = vec3(0.1f, 1.f, 0.1f);
	m_pArmL->Get_Position() = vec3(-0.1f, 1.f, 0.f);
	m_pArmL->Get_MatParent() = m_pBase->Get_World();

	m_pArmR = CMesh::Create("../Mesh/Cube0.obj", true, vec3(0.f, 1.f, 1.f));
	m_pArmR->Get_Scale() = vec3(0.1f, 1.f, 0.1f);
	m_pArmR->Get_Position() = vec3(0.1f, 1.f, 0.f);
	m_pArmR->Get_MatParent() = m_pBase->Get_World();

	return NOERROR;
}

GLuint CObject17::Update()
{
	return GLuint();
}

GLvoid CObject17::Render()
{
	m_pBase->Move_Position(m_vPos);
	m_pBody->Get_MatParent() = m_pBase->Get_World();
	m_pArmL->Get_MatParent() = m_pBody->Get_World();
	m_pArmR->Get_MatParent() = m_pBody->Get_World();

	m_pBase->Render();
	m_pBody->Render();
	m_pArmL->Render();
	m_pArmR->Render();

	return GLvoid();
}

GLvoid CObject17::Move(vec3 vDir, float fSpeed)
{
	if (m_vPos.x <= 0.75f && m_vPos.x >= -0.75f && m_vPos.z <= 0.75f && m_vPos.z >= -0.75f)
		m_vPos += vDir * fSpeed;

	if (m_vPos.x <= -0.75f)
		m_vPos.x = -0.75f;
	if (m_vPos.x >= 0.75f)
		m_vPos.x = 0.75f;
	if (m_vPos.z <= -0.75f)
		m_vPos.z = -0.75f;
	if (m_vPos.z >= 0.75f)
		m_vPos.z = 0.75f;


	return GLvoid();
}

GLvoid CObject17::Rotate(float fAngle)
{
	m_fAngle += fAngle;
	if (m_fAngle > 180.f)
		m_fAngle = 180.f;

	m_pBody->Get_MatRot() = rotate(mat4(1.f), ToRadian(m_fAngle), vec3(0.f, 1.f, 0.f));
	
	return GLvoid();
}

GLvoid CObject17::Arm()
{
	m_fArmAngle += m_fAdd;
	if (m_fArmAngle > 60.f)
	{
		m_fAdd *= -1.f;
		m_fArmAngle = 60.f;
	}

	if (m_fArmAngle < 0.f)
	{
		m_fAdd *= -1.f;
		m_fArmAngle = 0.f;
	}

	m_pArmL->Get_MatRot() = rotate(mat4(1.f), ToRadian(m_fArmAngle), vec3(0.f, 0.f, 1.f));
	m_pArmR->Get_MatRot() = rotate(mat4(1.f), ToRadian(-m_fArmAngle), vec3(0.f, 0.f, 1.f));

	return GLvoid();
}

CObject17* CObject17::Create()
{
	CObject17* pInstance = new CObject17();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
