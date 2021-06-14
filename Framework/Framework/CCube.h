#pragma once
#include "CShape.h"

class CCube : public CShape
{
public :
	CCube();
	~CCube();

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

private:
	mat4 m_matTrans = mat4(1.f);
	mat4 m_matScale = mat4(1.f);
	mat4 m_matRot = mat4(1.f);

public:
	GLvoid Release();
	static CCube* Create();
};

