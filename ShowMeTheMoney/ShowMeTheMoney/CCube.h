#pragma once
#include "CComponent.h"

class CTexture;
class CCube : public CComponent
{
public:
	CCube();
	~CCube();

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
	static CCube* Create();
};

