#pragma once
#include "CGameObj.h"

class CCamera : public CGameObj
{
public:
	CCamera();
	~CCamera();

public:
	mat4 Get_View() { return m_matView; }
	mat4 Get_Proj() { return m_matProj; }

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

public:
	GLvoid Update_Matrix();
	GLvoid Change_State(CAMERA::STATE eState);

private:
	vec3 m_vEye = vec3(0.f, 1.f, 1.f);
	vec3 m_vAt = vec3(0.f, 0.f, 0.f);
	vec3 m_vUp = vec3(0.f, 1.f, 0.f);
	vec3 m_vDir = vec3(0.f, 0.f, 0.f);
	vec3 m_vLightDir = vec3(0.f, 0.f, 0.f);
	float m_fDistance = 3.f;

private:
	GLfloat m_fFovY = 45.f;
	GLfloat m_fNear = 0.1f;
	GLfloat m_fFar = 200.0f;

private:
	mat4 m_matView = mat4(1.f);
	mat4 m_matProj = mat4(1.f);

private:
	GLfloat m_fAngle = 0.f;

private:
	CAMERA::STATE m_eState = CAMERA::FULL;

private:
	GLvoid Release();

public:
	static CCamera* Create();
};
