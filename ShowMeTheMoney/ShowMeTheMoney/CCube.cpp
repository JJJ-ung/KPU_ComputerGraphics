#include "stdafx.h"
#include "CCube.h"

CCube::CCube()
{
}

CCube::~CCube()
{
}

HRESULT CCube::Initialize()
{
	CComponent::Initialize();

	m_vecVertices.push_back(vec3(-0.5f, -1.f, 0.5f));

	m_vecTexcoord.push_back(vec2(0.f, 0.f));

	glGenVertexArrays(1, &m_Vao); //--- VAO 를 지정하고 할당하기
	glGenBuffers(2, m_Vbo); //--- 2개의 VBO를 지정하고 할당하기

	glBindVertexArray(m_Vao); //--- VAO를 바인드하기

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_vecVertices.size(), &m_vecVertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * m_vecTexcoord.size(), &m_vecTexcoord.front(), GL_STATIC_DRAW);

	return NOERROR;
}

GLvoid CCube::Render()
{
	return GLvoid();
}

GLvoid CCube::Release()
{
	return GLvoid();
}

CCube* CCube::Create()
{
	return nullptr;
}
