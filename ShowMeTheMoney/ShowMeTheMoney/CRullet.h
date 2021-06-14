#pragma once
#include "CGameObj.h"

class CRullet : public CGameObj
{
public:
	CRullet();
	~CRullet();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLvoid Release();
	HRESULT Reset();

public:
	static CRullet* Create();

private:
	float speed = 10.f;
	float speed_delta = 13.f;
	float speed_limit = 0;
	bool Get_Result = FALSE;

	float m_fTime = 0.f;

	enum Rullet_result { Success = 0, Fail, Great_Success, Great_Fail };
	enum Rullet_result result;

private:
	mat4 m_matView = mat4(1.f);
	mat4 m_matProj = mat4(1.f);
};
