#pragma once
#include "CGameObj.h"

class CPlayer : public CGameObj
{
public:
	CPlayer();
	~CPlayer();

public:
	virtual HRESULT Initialize(GLint iIndex);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLvoid Select_Platform();
	bool Check_Selection(int iIndex);

private:
	GLint m_iIndex = 0;
	float m_fTime = 0.f;

private:
	GLvoid Release();

public:
	static CPlayer* Create(GLint iIndex);
};
