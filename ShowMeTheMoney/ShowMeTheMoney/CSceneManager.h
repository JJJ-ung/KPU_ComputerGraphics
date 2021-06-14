#pragma once

class CScene;
class CSceneManager
{
	DECLARE_SINGLETON(CSceneManager)

private:
	CSceneManager();
	~CSceneManager();

public:
	HRESULT SceneChange(SCENE::ID eID);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	void Release();

private:
	SCENE::ID m_ePreScene = SCENE::END;
	SCENE::ID m_eCurrScene = SCENE::END;
	CScene* m_pScene = nullptr;
};

