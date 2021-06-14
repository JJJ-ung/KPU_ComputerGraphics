#pragma once
#include "CShaderLoader.h"

class CMesh
{
public:
	CMesh();
	~CMesh();

public:
	vec3& Get_Position() { return m_vPos; }
	vec3& Get_Scale() { return m_vScale; }
	GLfloat& Get_Angle() { return m_fAngle; }

public:
	mat4& Get_MatTrans() { return m_matTrans; }
	mat4& Get_MatScale() { return m_matScale; }
	mat4& Get_MatRot() { return m_matRot; }
	mat4& Get_MatParent() { return m_matParent; }
	mat4& Get_World() { Update_World();  return m_matWorld; }

public:
	HRESULT Initialize(string path, bool bCol = false, vec3 vCol = vec3(1.f, 1.f, 1.f));
	GLuint Update();
	GLvoid Render();

private:
	HRESULT LoadMesh(string path);
	HRESULT SetDefaultColor();
	HRESULT SetVertexColor(vec3 vCol);

public:
	GLvoid Move(vec3 vMove) { m_vPos += vMove; }
	GLvoid Move_Position(vec3 vPos) { m_vPos = vPos; }
	GLvoid Scale(vec3 vScale) { m_vScale = vScale; }
	GLvoid Rotate(vec3 Axis, float fAngle);
	GLvoid Revolate(vec3 Axis, float fAngle);
	GLvoid RotateX(float fAngle);
	GLvoid RotateY(float fAngle);
	HRESULT ChangeVertexColor(vec3 col);
	GLvoid Update_World();

private:
	GLuint m_iCnt;
	vector<vec2> m_vecUV;
	vector<vec3> m_vecColors;
	vector<vec3> m_vecVertices;
	vector<vec3> m_vecNormals;
	GLuint m_Vao, m_Vbo[2];

private:
	mat4 m_matTrans = mat4(1.f);
	mat4 m_matScale = mat4(1.f);
	mat4 m_matRot = mat4(1.f);
	mat4 m_matRev = mat4(1.f);
	mat4 m_matParent = mat4(1.f);
	mat4 m_matWorld = mat4(1.f);

private:
	vec3 m_vPos = vec3(0.f);
	vec3 m_vScale = vec3(1.f);
	GLfloat m_fAngle = 0.f;
	vec3 m_vRotAxis = vec3(0.f, 1.f, 0.f);

private:
	CShaderLoader* m_pShaderLoader;

public:
	GLvoid Release();
	static CMesh* Create(string path, bool bCol = false, vec3 vCol = vec3(1.f, 1.f, 1.f));
};

