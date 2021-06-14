#include "stdafx.h"
#include "CComponent.h"

CComponent::CComponent()
{
}

CComponent::~CComponent()
{
}

HRESULT CComponent::Initialize()
{
	m_pGameMgr = CGameManager::GetInstance();
	m_pRenderer = CRenderer::GetInstance();
	m_pSceneMgr = CSceneManager::GetInstance();
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pTimeMgr = CTimeManager::GetInstance();
	m_pShaderLoader = CShaderLoader::GetInstance();

	return NOERROR;
}

GLint CComponent::Update(const GLfloat fTimeDelta)
{
	return GLint(OBJ_NOEVENT);
}

GLvoid CComponent::Render()
{
	return GLvoid();
}

GLvoid CComponent::Release()
{
	return GLvoid();
}
