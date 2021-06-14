#pragma once
#include "CShaderLoader.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

public:
	HRESULT Initialize(vec3 vEye, vec3 vAt, vec3 vUp);
	GLuint Update();
	GLvoid Render();
	GLvoid Render_Ortho();

public:
	GLvoid Move(vec3 vDir, float fSpeed);
	GLvoid Follow(vec3 vTarget);

public:
	vec3& Get_At() { return m_vAt; }
	vec3& Get_Eye() { return m_vEye; }

public:
	GLfloat& Get_FovY()		{ return m_fFovY; }
	GLfloat& Get_Aspect()	{ return m_fAspect; }
	GLfloat& Get_Near()		{ return m_fNear; }
	GLfloat& Get_Far()			{ return m_fFar; }

public:
	GLfloat& Get_Left() { return m_fLeft; }
	GLfloat& Get_Right() { return m_fRight; }
	GLfloat& Get_Bottom() { return m_fBottom; }
	GLfloat& Get_Top() { return m_fTop; }
	GLfloat& Get_OrthoNear() { return m_fOrthoNear; }
	GLfloat& Get_OrthoFar() { return m_fOrthoFar; }

public:
	mat4& Get_View() { return m_matView; }

public:
	GLvoid Rotate(vec3 vAxis, float fAngle);

private:
	vec3 m_vEye = vec3(0.f, 0.f, 0.f);
	vec3 m_vAt = vec3(0.f, 1.f, -1.f);
	vec3 m_vUp = vec3(0.f, 1.f, 0.f);
	vec3 m_vDir = vec3(0.f, 0.f, 0.f);

private:
	GLfloat m_fFovY = 45.f;
	GLfloat m_fAspect = 800.f / 800.f;
	GLfloat m_fNear = 0.1f;
	GLfloat m_fFar = 200.0f;

private:
	GLfloat m_fLeft = -1.f;
	GLfloat m_fRight = 1.f;
	GLfloat m_fBottom = -1.f;
	GLfloat m_fTop = 1.f;
	GLfloat m_fOrthoNear = -1.f;
	GLfloat m_fOrthoFar = 10.f;

private:
	mat4 m_matView = mat4(1.f);
	mat4 m_matProj = mat4(1.f);

private:
	CShaderLoader* m_pShaderLoader;

public:
	static CCamera* Create(vec3 vEye, vec3 vAt, vec3 vUp);
};

