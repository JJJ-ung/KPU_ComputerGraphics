#pragma once
#include "CGameObj.h"

class CTransform;
class CResultMesh : public CGameObj
{
public:
	CResultMesh();
	~CResultMesh();

public:
	virtual HRESULT Initialize(int iIndex);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	mat4 m_matProj;
	mat4 m_matView;
	vec3 m_vDir;
	vec3 m_vEye;
	vec3 m_vAt;

private:
	GLvoid Release();

public:
	static CResultMesh* Create(int iIndex);
};

