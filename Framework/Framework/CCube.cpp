#include "stdafx.h"
#include "CCube.h"

CCube::CCube()
{
}

CCube::~CCube()
{
	Release();
}

HRESULT CCube::Initialize()
{
	vector<vec3> vertices = { vec3(-1.0f,-1.0f,-1.0f),		vec3(-1.0f,-1.0f, 1.0f),	vec3(-1.0f, 1.0f, 1.0f),
													 vec3(1.0f, 1.0f,-1.0f),			vec3(-1.0f,-1.0f,-1.0f),	vec3(-1.0f, 1.0f,-1.0f),
													 vec3(1.0f,-1.0f, 1.0f),			vec3(-1.0f,-1.0f,-1.0f),	vec3(1.0f,-1.0f,-1.0f),
													 vec3(1.0f, 1.0f,-1.0f),			vec3(1.0f,-1.0f,-1.0f),		vec3(-1.0f,-1.0f,-1.0f),
													 vec3(-1.0f,-1.0f,-1.0f),		vec3(-1.0f, 1.0f, 1.0f),		vec3(-1.0f, 1.0f,-1.0f),
													 vec3(1.0f,-1.0f, 1.0f),			vec3(-1.0f,-1.0f, 1.0f),	vec3(-1.0f,-1.0f,-1.0f),
													 vec3(-1.0f, 1.0f, 1.0f),		vec3(-1.0f,-1.0f, 1.0f),	vec3(1.0f,-1.0f, 1.0f),
													 vec3(1.0f, 1.0f, 1.0f),			vec3(1.0f,-1.0f,-1.0f),		vec3(1.0f, 1.0f,-1.0f),
													 vec3(1.0f,-1.0f,-1.0f),		vec3(1.0f, 1.0f, 1.0f),		vec3(1.0f,-1.0f, 1.0f),
													 vec3(1.0f, 1.0f, 1.0f),			vec3(1.0f, 1.0f,-1.0f),		vec3(-1.0f, 1.0f,-1.0f),
													 vec3(1.0f, 1.0f, 1.0f),			vec3(-1.0f, 1.0f,-1.0f),	vec3(-1.0f, 1.0f, 1.0f),
													 vec3(1.0f, 1.0f, 1.0f),			vec3(-1.0f, 1.0f, 1.0f),		vec3(1.0f,-1.0f, 1.0f) };

	vector<vec3> colors = { vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
									vec3(1.f, 0.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f) };

	CShape::Initialize(vertices, colors, 36, GL_TRIANGLES);

	return NOERROR;
}

GLuint CCube::Update()
{
	return GLuint();
}

GLvoid CCube::Render()
{
	m_matTrans = translate(mat4(1.f), m_vPos);
	m_matScale = scale(mat4(1.f), m_vScale);
	m_matWorld = m_matTrans * m_matScale * m_matRot;

	glUseProgram(m_pShaderLoader->s_program);
	GLuint iLocation = glGetUniformLocation(m_pShaderLoader->s_program, "matWorld");
	glUniformMatrix4fv(iLocation, 1, GL_FALSE, value_ptr(m_matWorld));

	glBindVertexArray(m_Vao);
	glDrawArrays(m_eMode, 0, m_iCnt);

	return GLvoid();
}

GLvoid CCube::Release()
{
	return GLvoid();
}

CCube* CCube::Create()
{
	CCube* pInstance = new CCube;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

