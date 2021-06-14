#include "stdafx.h"
#include "CPlatform.h"

#include "CMesh.h"
#include "CTransform.h"
#include "CPlane.h"
#include "CTexture.h"

#include "CObject.h"

CPlatform::CPlatform()
{
}

CPlatform::~CPlatform()
{
}

HRESULT CPlatform::Initialize(PLATFORM::TYPE eType)
{
	CGameObj::Initialize();

	m_pTransform = CTransform::Create();
	if (FAILED(CGameObj::Add_Component(COMPONENT::UPDATE, m_pTransform)))
		return E_FAIL;

	m_pTransform->Get_Scale() = vec3(1.5f);
	m_pTransform->Get_Rotation().y = 45.f;

	switch (eType)
	{
	case PLATFORM::TREE:
		if (FAILED(Initialize_Tree()))
			return E_FAIL;
		break;
	case PLATFORM::DIY:
		if (FAILED(Initialize_DIY()))
			return E_FAIL;
		break;
	case PLATFORM::FISH:
		if (FAILED(Initialize_Fish()))
			return E_FAIL;
		break;
	case PLATFORM::FOSSIL:
		if (FAILED(Initialize_Fossil()))
			return E_FAIL;
		break;
	case PLATFORM::GRASS:
		if (FAILED(Initialize_Grass()))
			return E_FAIL;
		break;
	case PLATFORM::INSECT:
		if (FAILED(Initialize_Insect()))
			return E_FAIL;
		break;
	case PLATFORM::STONE:
		if (FAILED(Initialize_Stone()))
			return E_FAIL;
		break;
	case PLATFORM::FRUIT:
		if (FAILED(Initialize_Fruit()))
			return E_FAIL;
		break;
	case PLATFORM::NPC:
		if (FAILED(Initialize_NPC()))
			return E_FAIL;
		break;
	default:
		break;
	}

	return NOERROR;
}

GLint CPlatform::Update(const GLfloat fTimeDelta)
{
	CGameObj::Update_Component(fTimeDelta);

	m_pRenderer->Add_RenderObj(RENDER::NONALPHA, this);

	for (auto pObj : m_lstRenderObj)
		pObj->Update(fTimeDelta);

	return GLint(OBJ_NOEVENT);
}

GLvoid CPlatform::Render()
{
	int program = m_pShaderLoader->Use_Shader("Platform");
	m_pGameMgr->Render_Camera();

	CGameObj::Render_Component();

	for (auto pObj : m_lstRenderObj)
		pObj->Render();

	return GLvoid();
}

HRESULT CPlatform::Initialize_Tree()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Grass/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(-2.5f, 0.f, 0.f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Map/Tree/Tree.obj", m_pTransform->Get_Position() + vec3(-0.3f, 0.f, -0.3f));
	pObj->Get_Transform()->Get_Scale() *= vec3(7.f);
	pObj->Get_Transform()->Get_Rotation().y = 45.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

HRESULT CPlatform::Initialize_DIY()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Floor/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(0.f, 0.f, -2.5f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Map/DIY/DIY.obj", m_pTransform->Get_Position() + vec3(0.f, 0.f, -0.5f));
	pObj->Get_Transform()->Get_Scale() *= vec3(1.5f);
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

HRESULT CPlatform::Initialize_Fish()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Sea/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(0.f, 0.f, 2.5f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Map/Fish/Fish.obj", m_pTransform->Get_Position() + vec3(0.3f, 0.05f, 0.4f));
	pObj->Get_Transform()->Get_Scale() *= vec3(5.f);
	pObj->Get_Transform()->Get_Rotation().y = -45.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	pObj = CObject::Create("../Bin/Resources/Map/Fish/Fish.obj", m_pTransform->Get_Position() + vec3(-0.7f, 0.05f, 0.f));
	pObj->Get_Transform()->Get_Scale() *= vec3(2.f);
	pObj->Get_Transform()->Get_Rotation().y = 60.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	pObj = CObject::Create("../Bin/Resources/Map/Fish/Fish.obj", m_pTransform->Get_Position() + vec3(-0.3f, 0.05f, -0.4f));
	pObj->Get_Transform()->Get_Scale() *= vec3(2.f);
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

HRESULT CPlatform::Initialize_Fossil()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Fossil/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(1.25f, 0.f, 1.25f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Map/Fossil/Fossil.obj", m_pTransform->Get_Position() + vec3(0.2f, 0.f, 0.5f));
	pObj->Get_Transform()->Get_Scale() *= vec3(1.5);
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	pObj = CObject::Create("../Bin/Resources/Map/Fossil/Fossil.obj", m_pTransform->Get_Position() + vec3(-0.1f, 0.f, 0.5f));
	pObj->Get_Transform()->Get_Rotation().y = 25.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

HRESULT CPlatform::Initialize_Grass()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Special/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(-1.25f, 0.f, 1.25f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Map/Grass/Grass.obj", m_pTransform->Get_Position() + vec3(-0.5f, 0.f, 0.f));
	pObj->Get_Transform()->Get_Scale() *= vec3(2);
	pObj->Get_Transform()->Get_Rotation().y = 15.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

HRESULT CPlatform::Initialize_Insect()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Insect/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(2.5f, 0.f, 0.f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Map/Tree/Tree.obj", m_pTransform->Get_Position() + vec3(0.3f, 0.f, -0.3f));
	pObj->Get_Transform()->Get_Scale() *= vec3(7.f);
	pObj->Get_Transform()->Get_Rotation().y = -45.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	pObj = CObject::Create("../Bin/Resources/Map/Insect/Insect.obj", m_pTransform->Get_Position() + vec3(0.3f, 0.7f, -0.1f));
	pObj->Get_Transform()->Get_Scale() *= vec3(2.f);
	pObj->Get_Transform()->Get_Rotation().y = -30.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

HRESULT CPlatform::Initialize_Stone()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Fossil/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(-1.25f, 0.f, -1.25f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Map/Stone/Stone.obj", m_pTransform->Get_Position() + vec3(-0.2f, 0.f, -0.25f));
	pObj->Get_Transform()->Get_Scale() *= vec3(3);
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	pObj = CObject::Create("../Bin/Resources/Map/Stone/Stone.obj", m_pTransform->Get_Position() + vec3(-0.4f, 0.f, -0.1f));
	pObj->Get_Transform()->Get_Scale() *= vec3(2);
	pObj->Get_Transform()->Get_Rotation().y = 25.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

HRESULT CPlatform::Initialize_Fruit()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Fruit/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(1.25f, 0.f, -1.25f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Map/Cherry/Cherry.obj", m_pTransform->Get_Position() + vec3(0.3f, 0.f, -0.3f));
	pObj->Get_Transform()->Get_Scale() *= vec3(0.5f);
	pObj->Get_Transform()->Get_Rotation().y = -45.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	pObj = CObject::Create("../Bin/Resources/Map/Apple/Apple.obj", m_pTransform->Get_Position() + vec3(-0.5f, 0.f, 0.f));
	pObj->Get_Transform()->Get_Scale() *= vec3(0.7f);
	pObj->Get_Transform()->Get_Rotation().y = 45.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

HRESULT CPlatform::Initialize_NPC()
{
	CMesh* pMesh = CMesh::Create("../Bin/Resources/Map/Platform/Center/platform.obj");
	if (FAILED(CGameObj::Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;

	m_pTransform->Get_Position() = vec3(0.f);

	CObject* pObj = nullptr;
	pObj = CObject::Create("../Bin/Resources/Player/NPC/NPC.obj", m_pTransform->Get_Position() + vec3(-0.6f, 0.f, 0.f));
	pObj->Get_Transform()->Get_Scale() *= vec3(1.f);
	pObj->Get_Transform()->Get_Rotation().y = 45.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	pObj = CObject::Create("../Bin/Resources/Player/NPC/NPC.obj", m_pTransform->Get_Position() + vec3(0.6f, 0.f, 0.f));
	pObj->Get_Transform()->Get_Scale() *= vec3(1.f);
	pObj->Get_Transform()->Get_Rotation().y = -45.f;
	if (!pObj)
		return E_FAIL;
	m_lstRenderObj.push_back(pObj);

	return NOERROR;
}

GLvoid CPlatform::Release()
{
	return GLvoid();
}

CPlatform* CPlatform::Create(PLATFORM::TYPE eType)
{
	CPlatform* pInstance = new CPlatform;

	if (FAILED(pInstance->Initialize(eType)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
