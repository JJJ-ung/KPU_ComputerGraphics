#pragma once
#include "CShaderLoader.h"

class CShape
{
public:
	CShape();
	~CShape();

public:
	virtual HRESULT Initialize(vector<vec3> vPos, vector<vec3> vCol, GLuint iCnt, GLenum eMode);
	virtual GLuint Update();
	virtual GLvoid Render();

public:
	vec3& Get_Position()													{ return m_vPos; }
	vec3& Get_Scale()														{ return m_vScale; }
	GLfloat& Get_Angle()													{ return m_fAngle; }

public:
	mat4& Get_MatTrans()												{ return m_matTrans; }
	mat4& Get_MatScale()												{ return m_matScale; }
	mat4& Get_MatRot()													{ return m_matRot; }
	mat4& Get_MatParent()												{ return m_matParent; }
	mat4& Get_World()														{ Update_World();  return m_matWorld; }

public:
	GLvoid Move(vec3 vMove)											{ m_vPos += vMove; }
	GLvoid Move_Position(vec3 vPos)							{ m_vPos = vPos; }
	GLvoid Scale(vec3 vScale)											{ m_vScale = vScale; }
	GLvoid Rotate(vec3 Axis, float fAngle);
	GLvoid Revolate(vec3 Axis, float fAngle);
	GLvoid RotateX(float fAngle);
	GLvoid RotateY(float fAngle);
	GLvoid Update_World();

protected:
	GLuint m_iCnt;
	GLenum m_eMode;
	GLuint m_Vao, m_Vbo[2];
	vector<vec3> m_vecColors;
	vector<vec3> m_vecVertices;

protected:
	mat4 m_matTrans = mat4(1.f);
	mat4 m_matScale = mat4(1.f);
	mat4 m_matRot = mat4(1.f);
	mat4 m_matRev = mat4(1.f);
	mat4 m_matParent = mat4(1.f);
	mat4 m_matWorld = mat4(1.f);

protected:
	vec3 m_vPos = vec3(0.f);
	vec3 m_vScale = vec3(1.f);
	GLfloat m_fAngle = 0.f;
	vec3 m_vRotAxis = vec3(0.f, 1.f, 0.f);

protected:
	CShaderLoader* m_pShaderLoader;

protected:
	GLvoid Release();

public:
	static CShape* Create(vector<vec3> vPos, vector<vec3> vCol, GLuint iCnt, GLenum eMode = GL_TRIANGLES);
};