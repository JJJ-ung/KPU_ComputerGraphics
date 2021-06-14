#pragma once
#include "CScene.h"

class CScene_Result : public CScene
{
public:
	CScene_Result();
	~CScene_Result();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLvoid Release();

public:
	static CScene_Result* Create();
};

