#pragma once
#include "CScene.h"

class CMesh;
class CShape;
class CScene13 : public CScene
{
public:
	CScene13();
	~CScene13();

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

public:
	GLvoid Input_Mouse(int button, int state, int x, int y);
	GLvoid Input_KeyBoard(unsigned char key, int x, int y);
	GLvoid Input_KeyBoardDir(int key, int x, int y);

private:
	HRESULT Create_SinSpline();
	HRESULT Create_SpringSpline();
	HRESULT Create_ZigZagSpline();

	vec3 SpringSpline(float fAngle, float fAdd);

public:
	GLvoid Reset();

private:
	GLint m_iAct = -1;
	GLuint m_iCurr = 1;

	CShape* m_pLine = nullptr;
	CShape* m_pSin = nullptr;
	CShape* m_pSpring = nullptr;
	CShape* m_pZigZag = nullptr;

	CShape* m_pShape = nullptr;
	CMesh* m_pMesh = nullptr;

	float m_fMeshAngle = 0.f;
	float m_fShapeAngle = 0.f;

	float m_fMeshRot = 0.f;
	float m_fShapeRot = 0.f;

	float m_fMeshSize = 0.015f;
	float m_fMeshSizeAdd = 0.0005f;
	float m_fTriSize = 1.f;
	float m_fTriSizeAdd = 0.01f;

	float m_fMeshAdd = 0.f;
	float m_fShapeAdd = 0.f;

public:
	GLvoid Release();
	static CScene13* Create();
};

