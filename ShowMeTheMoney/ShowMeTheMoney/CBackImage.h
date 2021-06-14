#pragma once
#include "CGameObj.h"

class CBackImage : public CGameObj
{
public:
	CBackImage();
	~CBackImage();

public:
	virtual HRESULT Initialize(string strTexTag, string strTexPath, bool bAlpha);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLvoid Release();

public:
	static CBackImage* Create(string strTexTag, string strTexPath, bool bAlpha = true);
};

