#include "stdafx.h"
#include "CObject.h"

#include "CMesh.h"
#include "CTransform.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

HRESULT CObject::Initialize(string strMesh, vec3 vPos)
{
	CGameObj::Initialize();

	CMesh* pMesh = CMesh::Create(strMesh);
	if (FAILED(Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform = CTransform::Create();
	if (FAILED(Add_Component(COMPONENT::UPDATE, m_pTransform)))
		return E_FAIL;

	m_pTransform->Get_Position() = vPos;
	m_pTransform->Get_Scale() = vec3(0.05f);

	return NOERROR;
}

GLint CObject::Update(const GLfloat fTimeDelta)
{
	CGameObj::Update_Component(fTimeDelta);

	m_pRenderer->Add_RenderObj(RENDER::NONALPHA, this);

	return GLint(OBJ_NOEVENT);
}

GLvoid CObject::Render()
{
	m_pShaderLoader->Use_Shader("Platform");
	m_pGameMgr->Render_Camera();

	CGameObj::Render_Component();

	return GLvoid();
}

GLvoid CObject::Release()
{
	return GLvoid();
}

CObject* CObject::Create(string strMesh, vec3 vPos)
{
	CObject* pInstance = new CObject;

	if (FAILED(pInstance->Initialize(strMesh, vPos)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
