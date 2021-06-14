#pragma once
#include "CScene.h"

class CScene19 : public CScene
{
public:
	CScene19();
	~CScene19();

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

public:
	GLvoid Input_Mouse(int button, int state, int x, int y);
	GLvoid Input_KeyBoard(unsigned char key, int x, int y);

public:
	GLvoid Release();
	static CScene19* Create();
};

