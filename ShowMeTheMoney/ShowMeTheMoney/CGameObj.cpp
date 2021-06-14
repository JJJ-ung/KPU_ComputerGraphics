#include "stdafx.h"
#include "CGameObj.h"
#include "CComponent.h"

CGameObj::CGameObj()
{
}

CGameObj::~CGameObj()
{
}

HRESULT CGameObj::Initialize()
{
	m_pGameMgr = CGameManager::GetInstance();
	m_pRenderer = CRenderer::GetInstance();
	m_pSceneMgr = CSceneManager::GetInstance();
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pTimeMgr = CTimeManager::GetInstance();
	m_pShaderLoader = CShaderLoader::GetInstance();
	m_pSoundManager = CSoundManager::GetInstance();

	return NOERROR;
}

GLint CGameObj::Update(const GLfloat fTimeDelta)
{
	return GLint();
}

GLvoid CGameObj::Render()
{
}

HRESULT CGameObj::Add_Component(COMPONENT::ID eID, CComponent* pComponent)
{
	if (!pComponent)
		return E_FAIL;

	m_lstComponent[eID].emplace_back(pComponent);

	return NOERROR;
}

GLint CGameObj::Update_Component(const GLfloat fTimeDelta)
{
	for (int i = 0; i < COMPONENT::END; ++i)
	{
		for (auto pComponent : m_lstComponent[i])
			pComponent->Update(fTimeDelta);
	}

	return GLint();
}

GLvoid CGameObj::Render_Component()
{
	for (int i = 0; i < COMPONENT::END; ++i)
	{
		for (auto pComponent : m_lstComponent[i])
			pComponent->Render();
	}
}

GLvoid CGameObj::Release()
{
	for (int i = 0; i < COMPONENT::END; ++i)
	{
		for (auto pComponent : m_lstComponent[i])
			SafeDelete(pComponent);
	}
}
