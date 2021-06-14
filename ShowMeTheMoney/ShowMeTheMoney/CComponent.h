#pragma once
#include "Manager.h"

class CComponent
{
public:
	CComponent();
	virtual ~CComponent();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

protected:
	CRenderer* m_pRenderer = nullptr;
	CKeyManager* m_pKeyMgr = nullptr;
	CTimeManager* m_pTimeMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CShaderLoader* m_pShaderLoader = nullptr;

protected:
	GLvoid Release();
};

