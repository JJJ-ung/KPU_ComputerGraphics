#pragma once
#include "CGameObj.h"

class CLogo : public CGameObj
{
public:
	CLogo();
	~CLogo();

public:
	virtual HRESULT Initialize(vec3 vPos, vec3 vScale, string strTexTag, string strTexPath, bool bAlpha);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	float m_fAngle = 8.f;

private:
	mat4 m_matView = mat4(1.f);
	mat4 m_matProj = mat4(1.f);

private:
	GLvoid Release();

public:
	static CLogo* Create(vec3 vPos, vec3 vScale, string strTexTag, string strTexPath, bool bAlpha = true);
};

