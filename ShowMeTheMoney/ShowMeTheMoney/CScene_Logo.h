#pragma once
#include "CScene.h"

class CScene_Logo : public CScene
{
public:
	CScene_Logo();
	~CScene_Logo();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLvoid Release();

public:
	static CScene_Logo* Create();
};

