#pragma once
#include "CScene.h"

class CScene_Select : public CScene
{
public:
	CScene_Select();
	~CScene_Select();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLvoid Release();

public:
	static CScene_Select* Create();
};

