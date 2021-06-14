#pragma once
#include "CGameObj.h"

class CTransform;
class CObject : public CGameObj
{
public:
	CObject();
	~CObject();

public:
	virtual HRESULT Initialize(string strMesh, vec3 vPos);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLvoid Release();

public:
	static CObject* Create(string strMesh, vec3 vPos);
};

