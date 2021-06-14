#include "stdafx.h"
#include "CResultMesh.h"

#include "CMesh.h"
#include "CTransform.h"

CResultMesh::CResultMesh()
{
}

CResultMesh::~CResultMesh()
{
}

HRESULT CResultMesh::Initialize(int iIndex)
{
	CGameObj::Initialize();

	CMesh* pMesh = nullptr;
	if(iIndex == 0)
		pMesh = CMesh::Create("../Bin/Resources/Player/1Ho/1Ho.obj");
	else if (iIndex == 1)
		pMesh = CMesh::Create("../Bin/Resources/Player/KK/KK.obj");
	if (FAILED(Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform = CTransform::Create();
	if (FAILED(Add_Component(COMPONENT::UPDATE, m_pTransform)))
		return E_FAIL;

	m_pTransform->Get_Scale() = vec3(0.02f);
	m_pTransform->Get_Position() = vec3(-0.4f, -0.34f, 0.f);

	m_vEye = vec3(0.f, 0.f, 1.5f);
	m_vAt = vec3(0.f, 0.f, 0.f);
	m_vDir = normalize(m_vAt - m_vEye);

	m_matProj = perspective(radians(45.f), (float)WINCX / (float)WINCY, 0.1f, 200.0f);
	m_matView = lookAt(m_vEye, m_vAt, vec3(0.f, 1.f, 0.f));

	return NOERROR;
}

GLint CResultMesh::Update(const GLfloat fTimeDelta)
{
	m_pTransform->Get_Rotation().y += fTimeDelta * 100.f;

	CGameObj::Update_Component(fTimeDelta);

	m_pRenderer->Add_RenderObj(RENDER::NONALPHA, this);

	return GLint(OBJ_NOEVENT);
}

GLvoid CResultMesh::Render()
{
	GLuint program = m_pShaderLoader->Use_Shader("Default");

	int viewLoc = glGetUniformLocation(program, "matView");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));

	int ProjLoc = glGetUniformLocation(program, "matProj");
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

	int PosLoc = glGetUniformLocation(program, "vCameraPos");
	glUniform3fv(PosLoc, 1, value_ptr(m_vEye));

	int DirLoc = glGetUniformLocation(program, "vLightDir");
	glUniform3fv(DirLoc, 1, value_ptr(vec3(0.f, -0.1f, -1.f)));

	CGameObj::Render_Component();

	return GLvoid();
}

GLvoid CResultMesh::Release()
{
	return GLvoid();
}

CResultMesh* CResultMesh::Create(int iIndex)
{
	CResultMesh* pInstance = new CResultMesh;

	if (FAILED(pInstance->Initialize(iIndex)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
