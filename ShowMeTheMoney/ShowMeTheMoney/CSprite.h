#pragma once
#include "CGameObj.h"

class CTransform;
class CSprite : public CGameObj
{
public:
	CSprite();
	~CSprite();

public:
	CTransform* Get_Transform() { return m_pTransform; }

public:
	virtual HRESULT Initialize(vec3 vPos, vec3 vScale, string strTexTag, string strTexPath, bool bAlpha);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	mat4 m_matView = mat4(1.f);
	mat4 m_matProj = mat4(1.f);

private:
	GLvoid Release();

public:
	static CSprite* Create(vec3 vPos, vec3 vScale, string strTexTag, string strTexPath, bool bAlpha = true);
};

