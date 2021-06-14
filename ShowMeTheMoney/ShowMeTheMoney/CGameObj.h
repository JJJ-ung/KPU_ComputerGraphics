#pragma once
#include "Manager.h"

class CTransform;
class CComponent;
class CGameObj
{
public:
	CGameObj();
	virtual ~CGameObj();

public:
	CTransform* Get_Transform() { return m_pTransform; }

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

protected:
	HRESULT Add_Component(COMPONENT::ID eID, CComponent* pComponent);
	GLint Update_Component(const GLfloat fTimeDelta);
	GLvoid Render_Component();

protected:
	CTransform* m_pTransform;
	list<CComponent*> m_lstComponent[COMPONENT::END];

protected:
	CRenderer* m_pRenderer = nullptr;
	CKeyManager* m_pKeyMgr = nullptr;
	CTimeManager* m_pTimeMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CShaderLoader* m_pShaderLoader = nullptr;
	CSoundManager* m_pSoundManager = nullptr;

protected:
	GLvoid Release();
};
