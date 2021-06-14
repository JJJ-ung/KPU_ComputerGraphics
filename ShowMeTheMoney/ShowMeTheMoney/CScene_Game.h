#pragma once
#include "CScene.h"

class CScene_Game : public CScene
{
public:
	CScene_Game();
	~CScene_Game();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	bool m_bSceneChange = false;
	float m_fTime = 0.f;

private:
	GLvoid Release();

public:
	static CScene_Game* Create();
};

