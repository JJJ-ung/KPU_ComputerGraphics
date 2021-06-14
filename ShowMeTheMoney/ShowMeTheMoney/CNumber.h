#pragma once
#include "CGameObj.h"

class CPlane;
class CTexture;
class CTransform;
class CNumber : public CGameObj
{
public:
	typedef struct tagNumberTex
	{
		CPlane* buffer;
		CTexture* texture;
		CTransform* transform;
	}NUMTEX;

public:
	CNumber();
	~CNumber();

public:
	virtual HRESULT Initialize(GLuint iIndex);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLuint m_iMaxNumCnt = 5;
	GLuint m_iPlayerIndex = 0;
	NUMTEX m_arrNumber[5] = {};

private:
	mat4 m_matView = mat4(1.f);
	mat4 m_matProj = mat4(1.f);

private:
	vector<CTexture*> m_vecNumTexture;

private:
	GLvoid Release();

public:
	static CNumber* Create(GLuint iIndex);
};

