#pragma once
#include "Manager.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	HRESULT Initialize();
	GLint Update();
	GLvoid Render();

private:
	HRESULT Initialize_Manager();
	HRESULT Initialize_Shader();

private:
	CRenderer* m_pRenderer = nullptr;
	CKeyManager* m_pKeyMgr = nullptr;
	CTimeManager* m_pTimeMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CShaderLoader* m_pShaderLoader = nullptr;
	CSoundManager* m_pSoundManager = nullptr;

private:
	GLvoid Release();

public:
	static CMainGame* Create();
};

