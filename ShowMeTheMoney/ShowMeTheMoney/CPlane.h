#pragma once
#include "CComponent.h"

class CTexture;
class CPlane : public CComponent
{
public:
	CPlane();
	~CPlane();

public:
	virtual HRESULT Initialize();
	virtual GLvoid Render();

private:
	GLuint m_Vao, m_Vbo[2];
	vector<vec3> m_vecVertices;
	vector<vec2> m_vecTexcoord;

private:
	GLvoid Release();

public:
	static CPlane* Create();
};

