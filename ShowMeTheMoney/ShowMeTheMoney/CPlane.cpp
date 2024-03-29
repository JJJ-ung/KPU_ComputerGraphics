#include "stdafx.h"
#include "CPlane.h"

CPlane::CPlane()
{
}

CPlane::~CPlane()
{
}

HRESULT CPlane::Initialize()
{
	CComponent::Initialize();

	m_vecVertices.push_back(vec3(-1.f, 1.f, 0.f));
	m_vecVertices.push_back(vec3(1.f, 1.f, 0.f));
	m_vecVertices.push_back(vec3(-1.f, -1.f, 0.f));

	m_vecVertices.push_back(vec3(1.f, -1.f, 0.f));
	m_vecVertices.push_back(vec3(-1.f, -1.f, 0.f));
	m_vecVertices.push_back(vec3(1.f, 1.f, 0.f));

	m_vecTexcoord.push_back(vec2(0.f, 0.f));
	m_vecTexcoord.push_back(vec2(1.f, 0.f));
	m_vecTexcoord.push_back(vec2(0.f, 1.f));

	m_vecTexcoord.push_back(vec2(1.f, 1.f));
	m_vecTexcoord.push_back(vec2(0.f, 1.f));
	m_vecTexcoord.push_back(vec2(1.f, 0.f));

	glGenVertexArrays(1, &m_Vao); //--- VAO 를 지정하고 할당하기
	glGenBuffers(2, m_Vbo); //--- 2개의 VBO를 지정하고 할당하기

	glBindVertexArray(m_Vao); //--- VAO를 바인드하기

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_vecVertices.size(), &m_vecVertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * m_vecTexcoord.size(), &m_vecTexcoord.front(), GL_STATIC_DRAW);

	return NOERROR;
}

GLvoid CPlane::Render()
{
	for (int i = 0; i < 2; ++i)
	{
		glEnableVertexAttribArray(i);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[i]);
		glVertexAttribPointer(i, i == 1 ? 2 : 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	glDrawArrays(GL_TRIANGLES, 0, m_vecVertices.size());

	for (int i = 0; i < 2; ++i)
		glDisableVertexAttribArray(i);
}

GLvoid CPlane::Release()
{
	return GLvoid();
}

CPlane* CPlane::Create()
{
	CPlane* pInstance = new CPlane;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
