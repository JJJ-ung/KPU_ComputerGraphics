#include "stdafx.h"
#include "CSceneManager.h"

#include "CGameManager.h"

#include "CScene.h"
#include "CScene_Logo.h"
#include "CScene_Select.h"
#include "CScene_Game.h"
#include "CScene_Result.h"

IMPLEMENT_SINGLETON(CSceneManager)

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

HRESULT CSceneManager::SceneChange(SCENE::ID eID)
{
	m_eCurrScene = eID;

	if (m_ePreScene != m_eCurrScene)
	{
		SafeDelete(m_pScene);

		switch (m_eCurrScene)
		{
		case SCENE::LOGO:
			m_pScene = CScene_Logo::Create();
			break;
		case SCENE::SELECT:
			m_pScene = CScene_Select::Create();
			break;
		case SCENE::INGAME:
			m_pScene = CScene_Game::Create();
			break;
		case SCENE::RESULT:
			m_pScene = CScene_Result::Create();
			break;
		default:
			break;
		}

		if (!m_pScene)
			return E_FAIL;

		m_ePreScene = m_eCurrScene;
	}

	return NOERROR;
}

GLint CSceneManager::Update(const GLfloat fTimeDelta)
{
	return m_pScene->Update(fTimeDelta);
}

GLvoid CSceneManager::Render()
{
	return m_pScene->Render();
}

void CSceneManager::Release()
{
	SafeDelete(m_pScene);
}
