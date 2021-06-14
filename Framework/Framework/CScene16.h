#pragma once
#include "CScene.h"

namespace CUBE
{
	enum FACE { TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK, END };
}

namespace PYRAMID
{
	enum FACE { FRONT, BACK, LEFT, RIGHT, BOTTOM, END };
}

class CMesh;
class CShape;
class CScene16 : public CScene
{
	enum ACT { TURN, CUBE_TOP, CUBE_FRONT_OPEN, CUBE_FRONT_CLOSE, PYRAMID_OPEN, PYRAMID_CLOSE, IDLE };

public:
	CScene16();
	~CScene16();

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

public:
	GLvoid Input_Mouse(int button, int state, int x, int y);
	GLvoid Input_KeyBoard(unsigned char key, int x, int y);

private:
	GLvoid Create_Cube();
	GLvoid Create_Pyramid();

private:
	bool m_bOrtho = false;
	CShape* m_pLine;
	CShape* m_pCube[CUBE::END];
	CShape* m_pPyramid[PYRAMID::END];
	CMesh* m_pTest[8];

private:
	ACT m_eAct = IDLE;
	bool m_bCube = true;
	float m_fCubeAngle = 0.f;
	float m_fPyramidAngle = 0.f;

public:
	GLvoid Release();
	static CScene16* Create();
};

