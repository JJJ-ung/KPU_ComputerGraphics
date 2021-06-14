#include "stdafx.h"
#include "CScene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

HRESULT CScene::Initialize()
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

GLint CScene::Update(const GLfloat fTimeDelta)
{
	return GLint();
}

GLvoid CScene::Render()
{
	return GLvoid();
}

GLvoid CScene::Release()
{
	return GLvoid();
}
