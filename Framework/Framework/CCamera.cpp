#include "stdafx.h"
#include "CCamera.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Initialize(vec3 vEye, vec3 vAt, vec3 vUp)
{
	m_vEye = vEye;
	m_vAt = vAt;
	m_vUp = vUp;
	m_vDir = m_vAt - m_vEye;

	m_pShaderLoader = CShaderLoader::GetInstance();

	return NOERROR;
}

GLuint CCamera::Update()
{
	return GLuint();
}

GLvoid CCamera::Render()
{
	m_matView = lookAt(m_vEye, m_vAt, m_vUp);
	int viewLoc = glGetUniformLocation(m_pShaderLoader->s_program, "matView");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));

	m_matProj = perspective(radians(m_fFovY), m_fAspect, m_fNear, m_fFar);
	int ProjLoc = glGetUniformLocation(m_pShaderLoader->s_program, "matProj");
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

	return GLvoid();
}

GLvoid CCamera::Render_Ortho()
{
	vec3 vDir = m_vAt - m_vEye;
	m_matView = lookAt(m_vEye, normalize(vDir), m_vUp);
	int viewLoc = glGetUniformLocation(m_pShaderLoader->s_program, "matView");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));

	m_matProj = ortho(m_fLeft, m_fRight, m_fBottom, m_fTop, m_fOrthoNear, m_fOrthoFar);
	int ProjLoc = glGetUniformLocation(m_pShaderLoader->s_program, "matProj");
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

	return GLvoid();
}

GLvoid CCamera::Move(vec3 vDir, float fSpeed)
{
	m_vEye += normalize(vDir) * fSpeed;
	m_vAt += normalize(vDir) * fSpeed;

	return GLvoid();
}

GLvoid CCamera::Follow(vec3 vTarget)
{
	vec3 vMove = vTarget - m_vAt;
	m_vAt = vTarget;
	m_vEye += vMove;
	
	return GLvoid();
}

GLvoid CCamera::Rotate(vec3 vAxis, float fAngle)
{
	vec3 originAt = m_vAt;
	vec3 originEye = m_vEye;

	vec3 At = m_vAt;
	vec3 Eye = m_vEye;

	vec3 Dir = vec3(0.f, 0.f, 0.f) - m_vEye;
	Eye += Dir;
	At += Dir;

	vec4 temp = vec4(At, 1.f);
	mat4 temp1 = rotate(mat4(1.f), radians(fAngle), vAxis);
	temp = rotate(mat4(1.f), radians(fAngle), vAxis) * temp;
	At = vec3(temp);

	m_vEye = Eye - Dir;
	m_vAt = At - Dir;

	return GLvoid();
}

CCamera* CCamera::Create(vec3 vEye, vec3 vAt, vec3 vUp)
{
	CCamera* pInstance = new CCamera;

	if (FAILED(pInstance->Initialize(vEye, vAt, vUp)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
