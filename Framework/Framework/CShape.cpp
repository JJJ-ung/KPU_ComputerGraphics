#include "stdafx.h"
#include "CShape.h"

CShape::CShape()
{
}

CShape::~CShape()
{
	Release();
}

HRESULT CShape::Initialize(vector<vec3> vPos, vector<vec3> vCol, GLuint iCnt, GLenum eMode)
{
	if (vPos.empty() || vCol.empty())
		return E_FAIL;

	m_pShaderLoader = CShaderLoader::GetInstance();

	m_iCnt = iCnt;
	m_eMode = eMode;

	m_vecVertices = vPos;
	m_vecColors = vCol;

	glGenVertexArrays(1, &m_Vao); //--- VAO 를 지정하고 할당하기
	glGenBuffers(2, m_Vbo); //--- 2개의 VBO를 지정하고 할당하기

	glBindVertexArray(m_Vao); //--- VAO를 바인드하기

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * iCnt, &m_vecVertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * iCnt, &m_vecColors.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	return NOERROR;
}

GLuint CShape::Update()
{
	return 0;
}

GLvoid CShape::Render()
{
	m_matWorld = mat4(1.f);
	m_matTrans = translate(mat4(1.f), m_vPos);
	m_matScale = scale(mat4(1.f), m_vScale);
	m_matWorld = m_matParent * m_matRev * m_matTrans * m_matRot * m_matScale;

	glUseProgram(m_pShaderLoader->s_program);
	GLuint iLocation = glGetUniformLocation(m_pShaderLoader->s_program, "matWorld");
	glUniformMatrix4fv(iLocation, 1, GL_FALSE, value_ptr(m_matWorld));

	glBindVertexArray(m_Vao);
	glDrawArrays(m_eMode, 0, m_iCnt);

	return GLvoid();
}

GLvoid CShape::Rotate(vec3 Axis, float fAngle)
{
	mat4 matRot = rotate(mat4(1.f), ToRadian(fAngle), Axis);
	m_matRot *= matRot;

	return GLvoid();
}

GLvoid CShape::Revolate(vec3 Axis, float fAngle)
{
	mat4 matRot = rotate(mat4(1.f), ToRadian(fAngle), Axis);
	m_matRev *= matRot;

	return GLvoid();
}

GLvoid CShape::RotateX(float fAngle)
{
	return GLvoid();
}

GLvoid CShape::RotateY(float fAngle)
{
	vec3 axis = vec3(0.f, m_vPos.y, 0.f);
	if (m_vPos.y <= 0.f)
		axis.y = 1.f;
	normalize(axis);

	mat4 matRot = rotate(mat4(1.f), ToRadian(fAngle), axis);
	m_matRot *= matRot;

	return GLvoid();
}

GLvoid CShape::Update_World()
{
	m_matWorld = mat4(1.f);
	m_matTrans = translate(mat4(1.f), m_vPos);
	m_matScale = scale(mat4(1.f), m_vScale);
	m_matWorld = m_matParent * m_matRev * m_matTrans * m_matRot * m_matScale;

	return GLvoid();
}

GLvoid CShape::Release()
{
	return GLvoid();
}

CShape* CShape::Create(vector<vec3> vPos, vector<vec3> vCol, GLuint iCnt, GLenum eMode)
{
	CShape* pInstance = new CShape;

	if (FAILED(pInstance->Initialize(vPos, vCol, iCnt, eMode)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
