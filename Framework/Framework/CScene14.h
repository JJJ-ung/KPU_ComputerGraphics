#pragma once
#include "CScene.h"

class CMesh;
class CShape;
class CScene14 : public CScene
{
	enum TYPE { CUBE, CYLINDER, SPHERE, PYRAMID, TEAPOT };

public:
	CScene14();
	~CScene14();

public:
	virtual HRESULT Initialize();
	virtual GLuint Update();
	virtual GLvoid Render();

public:
	virtual GLvoid Input_Mouse(int button, int state, int x, int y);
	virtual GLvoid Input_KeyBoard(unsigned char key, int x, int y);
	virtual GLvoid Input_KeyBoardDir(int key, int x, int y);

public:
	GLvoid Create_Mesh(int iIndex, TYPE eType);

private:
	CShape* m_pLine = nullptr;
	CMesh* m_arrMesh[2];

public:
	GLvoid Release();
	static CScene14* Create();
};

