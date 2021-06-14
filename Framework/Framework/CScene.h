#pragma once
#include "CCamera.h"

class CCamera;
class CScene
{
public:
	CScene();
	~CScene();

public:
	virtual HRESULT Initialize();
	virtual GLuint Update();
	virtual GLvoid Render();

public:
	virtual GLvoid Input_Mouse(int button, int state, int x, int y);
	virtual GLvoid Input_KeyBoard(unsigned char key, int x, int y);
	virtual GLvoid Input_KeyBoardDir(int key, int x, int y);

protected:
	vec2 ScreenConvert(GLint x, GLint y);

protected:
	CCamera* m_pCamera = nullptr;

public:
	GLvoid Release();
};

