#pragma once
#include "CScene.h"

class CCube;
class CMesh;
class CShape;
class CScene12 : public CScene
{
public:
	CScene12();
	~CScene12();

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

public:
	GLvoid Input_Mouse(int button, int state, int x, int y);
	GLvoid Input_KeyBoard(unsigned char key, int x, int y);
	GLvoid Input_KeyBoardDir(int key, int x, int y);

private:
	GLenum m_eMode = GL_FILL;
	GLboolean m_bCube = true;
	GLint m_iRot = -1;
	GLboolean m_bDepth = true;

private:
	CShape* m_pLine = nullptr;
	CMesh* m_pCube = nullptr;
	CMesh* m_pPyramid = nullptr;

public:
	GLvoid Release();
	static CScene12* Create();
};

